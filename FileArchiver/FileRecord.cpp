
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
	//TODO: logic
	return false;
}

VersionRecord FileRecord::GetVersion(unsigned int versionID)
{
	//TODO: add logic
	return VersionRecord();
}

void FileRecord::PurgeOldVersions(int numberOfVersionsToKeep)
{
	//TODO: add logic
}

int FileRecord::GetNumberOfVersions()
{
    return NumberOfVersions;
}

int FileRecord::GetCurrentVersionID()
{
	return 0;
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

int FileRecord::GetVersionLength(int RequestedVersionNumber)
{
	//TODO: Add logic
	return RequestedVersionNumber;
}

int FileRecord::GetFileID()
{
	return FileID;
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
	
	//TODO: Get the last modified time of the file from the filesystem
	bool bSuccess = AddNewVersion(fileLength, fileData, 0);
	
	delete [] fileData;
	fileData = NULL;
	
	return bSuccess;
}

bool FileRecord::AddNewVersion(int FileLength, const char* FileBuffer, int LastModifiedTime)
{
	unsigned int newHash = GetHashOfFileBuffer(FileLength, FileBuffer);
	if(newHash == CurrentVersionHash)
	{
		return false;
	}
	
	//TODO:Add version logic
	
	return true;
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
