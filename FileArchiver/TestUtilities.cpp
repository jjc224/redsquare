#include <string>
#include "DBConnector.h"
#include "TestUtilities.h"
#include "ProjectConstants.h"
#include <fstream>
#include "FileRecord.h"
#include "MurmurHash3.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

void DropTables()
{
	ExecuteSQLFile("sql/DropTables.sql");
}
void CreateTables()
{
	ExecuteSQLFile("sql/CreateTables.sql");
}

void ExecuteSQLFile(string path)
{
	sql::Connection* dbcon = DBConnector::GetConnection();
	dbcon->setSchema("redsquare");
	
	if(dbcon == NULL)
	{
		log("Failed to open database connection");
		return;
	}
	
	ifstream inFile(path.c_str());
	if(!inFile.is_open())
	{
		log("Failed to open sql file");
		delete dbcon;
		dbcon = NULL;
		return;
	}
	
	while(!inFile.eof())
	{
		string statementstring;
		getline(inFile,statementstring);
		if(statementstring.empty() == false)
		{
			log(statementstring);
			ExecuteUpdateStatement(dbcon, statementstring);
		}
	}
	
	inFile.close();
	delete dbcon;
	dbcon = NULL;
}

bool ExecuteUpdateStatement(sql::Connection* dbcon, std::string sqlstatement)
{
	sql::Statement* stmt = dbcon->createStatement();
	bool bSuccess = false;
	try
	{
		bSuccess = stmt->executeUpdate(sqlstatement);
		dbcon->commit();
	}
	catch (sql::SQLException &e)
	{
		cout << "ERROR: " << endl;
		cout << e.what() << endl;
		cout << e.getErrorCode() << endl;
		cout << e.getSQLState() << endl;
	}
	delete stmt;
	return bSuccess;
}

void CommitFileWithOneVersion(string path)
{
	FileRecord newFile;
	bool bSuccess = newFile.CreateFile(path);
	
	string logMessage = "The result was: ";
	if(bSuccess)
	{
		logMessage += "Success!";
	}
	else
	{
		logMessage += "The nixon snake has failed";
	}
	
	log(logMessage);
}

void RunTestCommitFileOneVersion()
{
	DropTables();
	CreateTables();
	CommitFileWithOneVersion("MurmurHash3.cpp");
}

void RunTestCommitFileOneVersionRetrieve()
{
	//DropTables();
	//CreateTables();
	
	/*
	string fileinpath = "MurmurHash3.cpp";
	string fileoutpath = "MurmurHash3.cpp.ret";
	/*/
	string fileinpath = "nixonout2.jpg";
	string fileoutpath = "nixonout3.jpg";
	//*/
	
	CommitFileWithOneVersion(fileinpath);
	VersionRecord newRec(fileinpath, 1);
	newRec.GetFileData(fileoutpath);
	
	
	unsigned int hash1 = 0;
	unsigned int hash2 = 0;
	MurmurHash3_x86_32_FromFile(fileinpath, MURMUR_SEED_1, &hash1);
	MurmurHash3_x86_32_FromFile(fileoutpath, MURMUR_SEED_1, &hash2);
	
	if(hash1 == hash2)
	{
		log("Hashes match. File successfully retrieved");
	}
	else
	{
		log("Error. Hashes do not match. File not retrieved correctly");
	}
}
