/*
 * File:   FileArchiver.cpp
 * Author: Thomas Nixon
 *
 * Created on 19 September 2015, 3:59 PM
 */

#ifndef FILEARCHIVER_H
#define FILEARCHIVER_H

#include "mysql_connection.h"
#include "mysql_driver.h"
#include <string>
#include <vector>

#include "FileRecord.h"

class FileArchiver
{

protected:
		
public:
	
	// Constructor
	FileArchiver();

	// Destructor
	~FileArchiver();
	
	// Checks if a file exists already
	bool Exists(std::string filename);
	
	// Gets a file record for a filename
	FileRecord GetFile(std::string filename);
	
	// Returns the number of versions on a file
	int GetNumVersions(std::string filename);
	
	// Adds a new file to the database
	bool AddFile(std::string filename);
	
	// Adds a new version to a file in the database
	bool AddVersion(std::string filename);
	
	// Returns all the files in the database as a vector
	std::vector<FileRecord> GetFiles();
	
	// Returns all the filename stored in the database
	std::vector<std::string> GetFileNames();
	
	// Detect all file changes and return the ones that have changed
	std::vector<FileRecord> DetectChangedRecords();
	
//		void Close();		
//		bool Compare(std::string pathFilename);
//		bool Insert(std::string filename, std::string comment);
//		VersionRecord GetVersionInfo(std::string filename);
//		bool Update(std::string filename);
//		VersionRecord GetLastVersionInfo(std::string filename);
//		bool RetrieveVersion(int versionnum, std::string filebname, std::string retrievedname);
//              char* GetDataFromFile(std::string filename, int &length);
};

#endif
