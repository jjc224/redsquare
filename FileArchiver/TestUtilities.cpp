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

#include <cstdlib>

using namespace std;

void createFile(int seed, string filename, int length)
{
	srand(seed);
	
	ofstream outFile(filename.c_str());
	
	if(outFile.is_open())
	{
		while(length > 0)
		{
			length--;
			char num = rand() % 256;
			outFile.put(num);
		}
	}
}

void appendFile(int seed, string filename, int length)
{
	srand(seed);
	
	ofstream outFile(filename.c_str(), ios::app);
	
	if(outFile.is_open())
	{
		while(length > 0)
		{
			length--;
			char num = rand() % 256;
			outFile.put(num);
		}
	}
}

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
	bool bSuccess = newFile.CreateFile(path, "initial version");
	
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

void CommitFileWithTwoVersions()
{
	FileRecord newFile;
	string path = "testData/testFile.dat";
	createFile(25, path, 200000);
	bool bSuccess = newFile.CreateFile(path, "initial version");
	
	//check that we can't add the same version
	if(bSuccess)
	{
		log("Trying to add same version");
		bSuccess = !newFile.AddNewVersion(path, "same version");
		if(bSuccess == false)
		{
			log("ERROR: was able to add the same version");
		}
	}
	
	//check that adding a new version works
	if(bSuccess)
	{
		log("Trying to commit a new version");
		appendFile(25, path, 200);
		bSuccess = newFile.AddNewVersion(path, "Version 2");
	}
	
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
	//DropTables();
	//CreateTables();
	CommitFileWithOneVersion("MurmurHash3.cpp");
}

void RunTestCommitFileWithTwoVersionsRetrieveBoth()
{
	//DropTables();
	//CreateTables();

	string path = "testData/testFile.dat";
	string original = "testData/testFile.dat.orig";
	string retrievedLatest = "testData/retrievedLatest.dat";
	string retrievedOriginal = "testData/retrievedOriginal.dat";
	
	CommitFileWithTwoVersions();

	createFile(25, path + ".orig", 200000);

	VersionRecord originalVersion(path, 1);
	originalVersion.GetFileData(retrievedOriginal);
	
	VersionRecord latestVersion(path, 2);
	latestVersion.GetFileData(retrievedLatest);


	unsigned int hash1 = 0;
	unsigned int hash2 = 0;
	unsigned int hash3 = 0;
	unsigned int hash4 = 0;
	MurmurHash3_x86_32_FromFile(path, MURMUR_SEED_1, &hash1);
	MurmurHash3_x86_32_FromFile(original, MURMUR_SEED_1, &hash2);
	MurmurHash3_x86_32_FromFile(retrievedLatest, MURMUR_SEED_1, &hash3);
	MurmurHash3_x86_32_FromFile(retrievedOriginal, MURMUR_SEED_1, &hash4);
	
	if(hash1 == hash3 && hash2 == hash4)
	{
		log("Hashes match. File successfully retrieved");
	}
	else
	{
		log("Error. Hashes do not match. File not retrieved correctly");
	}
}

void RunTestCommitFileOneVersionRetrieve()
{
	//DropTables();
	//CreateTables();
	
	//*
	string fileinpath = "MurmurHash3.cpp";
	string fileoutpath = "MurmurHash3.cpp.ret";
	/*/
	string fileinpath = "testData/nixon.jpg";
	string fileoutpath = "testData/nixonout.jpg";
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

void RunTestPurge()
{
    string path = "testData/testFile.dat";
    FileRecord existingFile(path);
    
    if (!existingFile.IsValid())
    {
        log("FileRecord is not valid.");
        return;
    }
    
    log("Purging file.");
    existingFile.PurgeOldVersions(0);
    
    return;
}