// File: FileArchiver.h
// Author: Thomas Nixon


#include "mysql_connection.h"
#include "mysql_driver.h"
#include <string>


class VersionRec;


class FileArchiver
{

	protected:
		sql::Connection *dbcon;
		sql::Driver *driver;

	public:
		FileArchiver();
		~FileArchiver();
		bool Exists(std::string filename);
		bool Compare(std::string filename);
		bool Insert(std::string filename, std::string comment);
		VersionRec GetVersionInfo(std::string filename);
		bool Update(std::string filename);
		VersionRec GetLastVersionInfo(std::string filename);
		bool RetrieveVersion(int versionnum, std::string filebname, std::string retrievedname);
		string decrypt(string s);
		void Close();
};
