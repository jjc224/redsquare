
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

bool FileRecord::CreateFile(string filename)
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
			string sqlstatement = "insert into redsquare.File(filename, curhash, curversion, numversions) values(";
			//filename
			sqlstatement += "\"" + filename + "\"" + ", ";
			//curhash
			sqlstatement += string(0) + ", ";
			//curversion
			sqlstatement += string(0) + ", ";
			//numversions
			sqlstatement += string(0);
			//end of statement
			sqlstatement += ");";
			
			log(sqlstatement);
			
			bSuccess = stmt->execute(sqlstatement);
		}
		
		//retrieve record from DB
		if(bSuccess)
		{
			RetrieveFileRecordFromDB(filename);
			bSuccess = IsValid();
		}
		
		//Add new version
		VersionRecord newVersion;
		if(bSuccess)
		{
			VersionRecord newVersion;
			bSuccess = newVersion.CreateVersion(Filename);
		}
		
		//Update version details
		if(bSuccess)
		{
			NumberOfVersions += 1;
			CurrentVersion = newVersion.GetVersionNumber();
			CurrentVersionHash = newVersion.GetHash();
			bSuccess = UpdateRecordInDB();
		}
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

bool FileRecord::UpdateRecordInDB()
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
			string sqlstatement = "update redsquare.File set ";
			//curhash
			sqlstatement += "curhash = " + boost::lexical_cast<string>(CurrentVersionHash) + ", ";
			//curversion
			sqlstatement += "curversion = " + boost::lexical_cast<string>(CurrentVersion) + ", ";
			//numversions
			sqlstatement += "numversions = " + boost::lexical_cast<string>(NumberOfVersions);
			//end of statement
			sqlstatement += " where filename = \"" + Filename + "\";";
			
			log(sqlstatement);
			
			bSuccess = stmt->execute(sqlstatement);
		}
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

VersionRecord FileRecord::GetVersion(unsigned int versionID)
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


bool FileRecord::AddNewVersion(string NewFileVersionPath)
{
	ifstream ins(NewFileVersionPath.c_str());
	
	if(ins.is_open() == false)
	{
		//could not open the file
		return false;
	}
	
	ins.seekg(0, ios::end);
	int fileLength = ins.tellg();
	
	char* fileData = new char[fileLength];
	
	bool bSuccess = false;
	//TODO: Get the last modified time of the file from the filesystem
	//bool bSuccess = AddNewVersion(fileLength, fileData, 0);
	
	delete [] fileData;
	fileData = NULL;
	
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
        sql::ResultSet *rs = stmt->executeQuery("select * from redsquare.File where filename = '" + inFilename + "'");

        // Output Results
        while(rs->next())
		{
			//count = rs->getInt(1);
			Filename = rs->getString("filename");
			CurrentVersionHash = rs->getInt("curhash");
			CurrentVersion = rs->getInt("curversion");
			NumberOfVersions = rs->getInt("numversions");
			bIsValid = true;
		}

        delete rs;
        delete stmt;
    }
    catch (sql::SQLException &e)
    {
        cout << "ERROR: " << endl;
        cout << e.what() << endl;
        cout << e.getErrorCode() << endl;
        cout << e.getSQLState() << endl;
    }
	return bIsValid;
}
