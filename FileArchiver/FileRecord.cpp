
#include "FileRecord.h"
#include "MurmurHash3.h"
#include <stdint.h>

#include <fstream>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "DBConnector.h"

using namespace std;

FileRecord::FileRecord()
{
	dbcon = DBConnector::GetConnection();

	// Initialise protected members for return in case for some reason they weren't later on (see member functions).
	Filename            = "";
	CurrentVersionHash  = -1;
	OriginalVersionHash = -1;
	CurrentRevision     = -1;
	OriginalLength      = -1;
	CurrentLength       = -1;
	ModifiedTime        = -1;
}

FileRecord::~FileRecord()
{
	dbcon->close();
}

bool FileRecord::GetVersionFileContents(int RequestedVersionNumber, char* OutFileBuffer, int BufferLength)
{
	return false;
}

bool FileRecord::GetVersionFileContents(int RequestedVersionNumber, char* OutFileBuffer, int BufferLength, int& OutVersionLength)
{
	return false;
}

int GetNumberOfVersions()
{
	
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

unsigned int FileRecord::GetHashOfFileBuffer(int FileLength, const char* FileBuffer)
{
	uint32_t out;
	MurmurHash3_x86_32(FileBuffer, FileLength, 10000, &out);
	return out;
}
