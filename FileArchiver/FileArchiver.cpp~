// File: FileArchiver.cpp
// Author: Thomas Nixon

#include "mysql_connection.h"
#include "mysql_driver.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <string>
#include "FileArchiver.h"
#include "DBConnector.h"
#include "VersionRecord.h"

using namespace std;

// Prepares connection
FileArchiver::FileArchiver()
{
	dbcon = DBConnector::GetConnection();
}

FileArchiver::~FileArchiver()
{
	Close();
}

bool FileArchiver::Exists(std::string filename)
{
	try
	{
		// Run Query
		sql::Statement *stmt = dbcon->createStatement();;
		sql::ResultSet *rs = stmt->executeQuery("select * from redsquare.somewhere where someID = "+ filename);
		
		// Output Results
		while(rs->next())
			cout << rs->getString(1) << endl;
	
		delete rs;
		delete stmt;
	}
	catch (sql::SQLException &	e)
	{
		cout << "ERROR: " << endl;
		cout << e.what() << endl;
		cout << e.getErrorCode() << endl;
		cout << e.getSQLState() << endl;
	}
	
	
	//TODO: return correct result
	return false;
}

bool FileArchiver::Compare(std::string filename)
{
	//TODO: add logic here
	return false;
}

bool FileArchiver::Insert(std::string filename, std::string comment)
{
	//TODO: add logic here
	return false;
}

VersionRecord FileArchiver::GetVersionInfo(std::string filename)
{
	try
	{
		// Run Query
		sql::Statement *stmt = dbcon->createStatement();;
		sql::ResultSet *rs = stmt->executeQuery("select * from redsquare.comments");
		
		// Output Results
		while(rs->next())
			cout << rs->getString(1) << endl;
	
		delete rs;
		delete stmt;
	}
	catch (sql::SQLException &	e)
	{
		cout << "ERROR: " << endl;
		cout << e.what() << endl;
		cout << e.getErrorCode() << endl;
		cout << e.getSQLState() << endl;
	}
}

bool FileArchiver::Update(std::string filename)
{
	//TODO: add logic here
	return false;
}

VersionRecord FileArchiver::GetLastVersionInfo(std::string filename)
{
	try
	{
		// Run Query
		sql::Statement *stmt = dbcon->createStatement();;
		sql::ResultSet *rs = stmt->executeQuery("select * from redsquare.comments");
		
		// Output Results
		while(rs->next())
			cout << rs->getString(1) << endl;
	
		delete rs;
		delete stmt;
	}
	catch (sql::SQLException &	e)
	{
		cout << "ERROR: " << endl;
		cout << e.what() << endl;
		cout << e.getErrorCode() << endl;
		cout << e.getSQLState() << endl;
	}
}

bool FileArchiver::RetrieveVersion(int versionnum, std::string filebname, std::string retrievedname)
{
	try
	{
		// Run Query
		sql::Statement *stmt = dbcon->createStatement();;
		sql::ResultSet *rs = stmt->executeQuery("select * from redsquare.comments");
		
		// Output Results
		while(rs->next())
			cout << rs->getString(1) << endl;
	
		delete rs;
		delete stmt;
	}
	catch (sql::SQLException &	e)
	{
		cout << "ERROR: " << endl;
		cout << e.what() << endl;
		cout << e.getErrorCode() << endl;
		cout << e.getSQLState() << endl;
	}
}

void FileArchiver::Close()
{
	dbcon->close();
	delete dbcon;
}

