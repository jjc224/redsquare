// File: FileArchiver.cpp
// Author: Thomas Nixon

#include "mysql_connection.h"
#include "mysql_driver.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "FileArchiver.h"
#include "DBConnector.h"
#include "FileRecord.h"
#include "VersionRecord.h"
#include "ProjectConstants.h"
#include "boost/lexical_cast.hpp"

#include "MurmurHash3.h"

using namespace std;

// Constructor
FileArchiver::FileArchiver()
{
	dbcon = DBConnector::GetConnection();
}

// Destructor
FileArchiver::~FileArchiver()
{
	//dbcon->close();
	//delete dbcon;
	dbcon = NULL;
}

// Checks if a file exists already
bool FileArchiver::Exists(std::string filename)
{
	FileRecord myFile(filename);
	return myFile.IsValid();
}

// Gets a file record for a filename
FileRecord FileArchiver::GetFile(std::string filename)
{
	FileRecord myFile(filename);
	return myFile;
}

// Returns the number of versions on a file
int FileArchiver::GetNumVersions(std::string filename)
{
	FileRecord myFile(filename);
	return myFile.GetNumberOfVersions();
}

// Adds a new file to the database
bool FileArchiver::AddFile(string filename, string comment)
{
	FileRecord myFile;
	return myFile.CreateFile(filename, comment);
}

// Adds a new version to a file in the database
bool FileArchiver::AddVersion(string filename, string comment)
{
	FileRecord myFile(filename);
	if(myFile.IsValid())
	{
		return myFile.AddNewVersion(filename, comment);
	}
	
	return false; 
}

// Returns all the files in the database as a vector
vector<FileRecord> FileArchiver::GetFiles()
{
	vector<string> filenames = GetFileNames();
	vector<FileRecord> files;
	
	for(unsigned int i = 0; i < filenames.size(); i++)
	{
		FileRecord myRec(filenames[i]);
		if(myRec.IsValid())
		{
			files.push_back(myRec);
		}
	}
	
	return files;
}

// Returns all the filename stored in the database
vector<string> FileArchiver::GetFileNames()
{
	vector<string> filenames;
	string sqlstatement = "select filename from File";
	
	try
	{
		// Run Query
		sql::Statement *stmt = dbcon->createStatement();
		sql::ResultSet *rs = stmt->executeQuery(sqlstatement);

		// Output Results
		while(rs->next())
		{
			string filename = rs->getString("filename");
			filenames.push_back(filename);
		}

		delete rs;
		rs = NULL;
		delete stmt;
		stmt = NULL;
	}
	catch (sql::SQLException &e)
	{
		log("ERROR: ");
		log(e.what());
		log(boost::lexical_cast<string>(e.getErrorCode()));
		log(e.getSQLState());
	}
	
	return filenames;
}

// Detect all file changes and return the ones that have changed
vector<FileRecord> FileArchiver::DetectChangedRecords()
{
	vector<FileRecord> records = GetFiles();
	vector<FileRecord> changed;

	for(unsigned int i = 0; i < records.size(); i++)
	{
		FileRecord& myFile = records[i];
		if(myFile.IsValid() && myFile.IsChanged())
		{
			changed.push_back(myFile);
		}
	}

	return changed;
}

