
#include "FileRecord.h"
#include "MurmurHash3.h"
#include <stdint.h>

#include <fstream>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <boost/filesystem.hpp>

#include "DBConnector.h"
#include "ProjectConstants.h"

#include <boost/lexical_cast.hpp>

using namespace std;

FileRecord::FileRecord()
{
	Init();
}

void FileRecord::Init()
{
	dbcon = DBConnector::GetConnection();

	// Initialise protected members for return in case for some reason they weren't later on (see member functions).
	Filename            = "";
	CurrentVersionHash  = 0;
	CurrentVersion = 0;
	NumberOfVersions    = 0;
	ModifiedTime        = 0;

	bIsValid = false;
}

FileRecord::~FileRecord()
{
	dbcon->close();
}

FileRecord::FileRecord(std::string filename)
{
	Init();
	RetrieveFileRecordFromDB(filename);
}

bool FileRecord::CreateFile(string filename, string newComment)
{
	sql::Statement *stmt = dbcon->createStatement();
	bool bSuccess = true;
	
	if(stmt == NULL)
	{
		//failed to get a connection to the database
		bSuccess = false;
	}

	bIsValid = false;
	try
	{   
		//create file record
		if(bSuccess)
		{
			//beginning of statement
			string sqlstatement = "insert into File(filename, curhash, curversion, numversions) values(";
			//filename
			sqlstatement += "\"" + filename + "\"" + ", ";
			//curhash
			sqlstatement += boost::lexical_cast<string>(CurrentVersionHash) + ", ";
			//curversion
			sqlstatement += boost::lexical_cast<string>(CurrentVersion) + ", ";
			//numversions
			sqlstatement += boost::lexical_cast<string>(NumberOfVersions);
			//end of statement
			sqlstatement += ");";
			
			log(sqlstatement);
			
			bSuccess = stmt->executeUpdate(sqlstatement);
			dbcon->commit();
		}
		
		
		
		//retrieve record from DB
		if(bSuccess)
		{
			log("Retrieving record from db");
			RetrieveFileRecordFromDB(filename);
			bSuccess = IsValid();
		}
		
		if(bSuccess)
		{
			log("Adding new version");
			bSuccess = AddNewVersion(Filename, newComment);
		}
	}
	catch (sql::SQLException &e)
	{
		log("ERROR: ");
		log(e.what());
		log(e.getErrorCode());
		log(e.getSQLState());
		bSuccess = false;
	}
	
	delete stmt;
	return bSuccess;
}

bool FileRecord::UpdateRecordInDB()
{
	sql::Statement *stmt = dbcon->createStatement();
	bool bSuccess = true;
	
	if(stmt == NULL)
	{
		//failed to get a connection to the database
		bSuccess = false;
	}

	if(IsValid() == false)
	{
		bSuccess = false;
	}
		
	try
	{   
		//create file record
		if(bSuccess)
		{
			//beginning of statement
			string sqlstatement = "update File set ";
			//curhash
			sqlstatement += "curhash = " + boost::lexical_cast<string>(CurrentVersionHash) + ", ";
			//curversion
			sqlstatement += "curversion = " + boost::lexical_cast<string>(CurrentVersion) + ", ";
			//numversions
			sqlstatement += "numversions = " + boost::lexical_cast<string>(NumberOfVersions);
			//end of statement
			sqlstatement += " where filename = \"" + Filename + "\";";
			
			log(sqlstatement);
			
			bSuccess = stmt->executeUpdate(sqlstatement);
		}
	}
	catch (sql::SQLException &e)
	{
		log("ERROR: ");
		log(e.what());
		log(e.getErrorCode());
		log(e.getSQLState());
		bSuccess = false;
	}
	
	delete stmt;
	return bSuccess;
}

VersionRecord FileRecord::GetVersion(unsigned int versionNum)
{
	//TODO: add logic
	return VersionRecord();
}

vector<VersionRecord> FileRecord::GetAllVersions()
{
	return vector<VersionRecord>();
}

void FileRecord::PurgeOldVersions(int numberOfVersionsToKeep)
{
	//TODO: add logic
}

int FileRecord::GetNumberOfVersions()
{
	return NumberOfVersions;
}

//Ensures there is a valid corresponding record in the database
bool FileRecord::IsValid()
{
	return bIsValid;
}

bool FileRecord::GetVersionFileContents(int requestedVersionNumber, string fileOutPath)
{
	VersionRecord requestedVersion = GetVersion(requestedVersionNumber);
	if(requestedVersion.IsValid())
	{
		return requestedVersion.GetFileData(fileOutPath);
	}
	return false;
}

std::string FileRecord::GetFilename()
{
	return Filename;
}

unsigned int FileRecord::GetVersionSize(int versionNumber)
{
	//TODO: Add logic
	return versionNumber;
}


bool FileRecord::AddNewVersion(string NewFileVersionPath, string newComment)
{
	bool bSuccess = true;
	unsigned int newHash;
	
	if(boost::filesystem::exists(Filename) == false)
	{
		log("ERROR: File does not exist");
		bSuccess = false;
	}
	
	if(bSuccess)
	{
		MurmurHash3_x86_32_FromFile(NewFileVersionPath, MURMUR_SEED_1, &newHash);
		
		log("Hash generated for new version = " + boost::lexical_cast<string>(newHash));
	
		//fail if hash matches existing
		if(NumberOfVersions > 0 && CurrentVersionHash == newHash)
		{
			log("New version hash is no different. File is unchanged");
			bSuccess = false;
		}
	}
	
	//Add new version
	VersionRecord newVersion;
	if(bSuccess)
	{
		log("Adding new version");
		bSuccess = newVersion.CreateVersion(Filename, CurrentVersion + 1, newHash, newComment);
	}

	//Update version details
	if(bSuccess)
	{
		log("New version added");
		NumberOfVersions += 1;
		CurrentVersion = newVersion.GetVersionNumber();
		CurrentVersionHash = newVersion.GetHash();
		bSuccess = UpdateRecordInDB();
	}
	
	return bSuccess;
}

bool FileRecord::IsChanged()
{
	if(IsValid() == false)
	{
		return false;
	}
	
	if(boost::filesystem::exists(Filename) == false)
	{
		return false;
	}
	
	unsigned int fileHash;
	MurmurHash3_x86_32_FromFile(Filename, MURMUR_SEED_1, &fileHash);
	
	if(fileHash == CurrentVersionHash)
	{
		return false;
	}
	return true;
}

unsigned int FileRecord::GetHashOfFileBuffer(int FileLength, const char* FileBuffer)
{
	uint32_t out;
	MurmurHash3_x86_32(FileBuffer, FileLength, 10000, &out);
	return out;
}

bool FileRecord::RetrieveFileRecordFromDB(string inFilename)
{
	bIsValid = false;
	try
	{
		// Run Query
		sql::Statement *stmt = dbcon->createStatement();
		sql::ResultSet *rs = stmt->executeQuery("select * from File where filename = '" + inFilename + "'");

		// Output Results
		while(rs->next())
		{
			//count = rs->getUInt(1);
			Filename = rs->getString("filename");
			CurrentVersionHash = rs->getUInt("curhash");
			CurrentVersion = rs->getUInt("curversion");
			NumberOfVersions = rs->getUInt("numversions");
			bIsValid = true;
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
		log(e.getErrorCode());
		log(e.getSQLState());
	}
	return bIsValid;
}
