
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
	OriginalVersionHash = 0;
	CurrentRevision     = 0;
	OriginalLength      = 0;
	CurrentLength       = 0;
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

char* FileRecord::GetVersionData(unsigned int versionID)
{
	//TODO: add logic
	return NULL;
}

int FileRecord::GetNumberOfVersions()
{
	return 0;
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

bool FileRecord::GetVersionFileContents(int RequestedVersionNumber, char* OutFileBuffer, int BufferLength)
{
	return false;
}

bool FileRecord::GetVersionFileContents(int RequestedVersionNumber, char* OutFileBuffer, int BufferLength, int& OutVersionLength)
{
	return false;
}

std::string FileRecord::GetFilename()
{
	return Filename;
}

int FileRecord::GetCurrentLength()
{
	return CurrentLength;
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
	//TODO: add logic here
	return true;
}

unsigned int FileRecord::GetHashOfFileBuffer(int FileLength, const char* FileBuffer)
{
	uint32_t out;
	MurmurHash3_x86_32(FileBuffer, FileLength, 10000, &out);
	return out;
}

bool FileRecord::RetrieveFileRecordFromDB(string filename)
{
	//TODO: Add code to retrieve record from DB
	return bIsValid;
}
