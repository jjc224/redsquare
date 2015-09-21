#include <string>
#include "DBConnector.h"
#include "TestUtilities.h"
#include "ProjectConstants.h"
#include <fstream>
#include "FileRecord.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

void DropTables()
{
	ExecuteSQLFile("sql\\DropTables.sql");
}
void CreateTables()
{
	ExecuteSQLFile("sql\\CreateTables.sql");
}

void ExecuteSQLFile(string path)
{
	sql::Connection* dbcon = DBConnector::GetConnection();
	
	if(dbcon == NULL)
	{
		return;
	}
	
	ifstream inFile(path.c_str());
	if(!inFile.is_open())
	{
		delete dbcon;
		dbcon = NULL;
		return;
	}
	
	while(!inFile.eof())
	{
		string statementstring;
		getline(inFile,statementstring);
		ExecuteUpdateStatement(dbcon, statementstring);
	}
	
	inFile.close();
	delete dbcon;
	dbcon = NULL;
}

bool ExecuteUpdateStatement(sql::Connection* dbcon, std::string sqlstatement)
{
	sql::Statement* stmt = dbcon->createStatement();
	bool bSuccess = stmt->executeUpdate(sqlstatement);
	dbcon->commit();
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
