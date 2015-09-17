// File: FileArchiver.h
// Author: Thomas Nixon


#ifndef FILEARCHIVER_H
#define FILEARCHIVER_H

#include "mysql_connection.h"
#include "mysql_driver.h"
#include <string>


#include "VersionRecord.h"

class FileArchiver
{

	protected:
		sql::Connection* dbcon;
		//sql::Driver* driver;

	public:
		FileArchiver();
		~FileArchiver();
		bool Exists(std::string filename);
		bool Compare(std::string filename);
		bool Insert(std::string filename, std::string comment);
		VersionRecord GetVersionInfo(std::string filename);
		bool Update(std::string filename);
		VersionRecord GetLastVersionInfo(std::string filename);
		bool RetrieveVersion(int versionnum, std::string filebname, std::string retrievedname);
                char* GetDataFromFile(std::string filename, int &length);
		void Close();
};

#endif
