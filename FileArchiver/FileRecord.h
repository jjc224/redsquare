
#ifndef FILERECORD_H
#define FILERECORD_H

#include <string>
#include "DBConnector.h"

#include "VersionRecord.h"

class FileRecord
{
public:
	FileRecord();
	~FileRecord();

	//Creates the file record on the data 
	bool CreateFile();
	
	VersionRecord& GetVersion(unsigned int versionID);

	char* GetVersionData(unsigned int versionID);

	// Returns the number of versions this file has
	int GetNumberOfVersions();

	int GetCurrentVersionID();

	bool IsValid();

	// Gets the contents of a requested version number
	// Outputs the data into a supplied file buffer
	// Will not succeed if the buffer length is not large enough
	// Returns the success or failure of the retrieval
	bool GetVersionFileContents(int RequestedVersionNumber, char* OutFileBuffer, int BufferLength);

	// Same as previous definition, also outputs the length of the requested version in bytes to the supplied integer
	bool GetVersionFileContents(int RequestedVersionNumber, char* OutFileBuffer, int BufferLength, int& OutVersionLength);
	
	// Gets the full file path
	std::string GetFilename();

	// Returns the length in bytes of the current file version
	int GetCurrentLength();

	// Gets the length of a specific version of the file
	int GetVersionLength(int RequestedVersionNumber);

	// Gets the primary id of the file
	int GetFileID();
	
	// Friendly function for adding a new file version
	// Returns false if the version has not changed
	bool AddNewVersion(std::string NewFileVersionPath);
	bool AddNewVersion(char* filedata, unsigned int length);

protected:
	// The full path name of the file
	std::string Filename;

	// The hash of the current version of the file
	unsigned int CurrentVersionHash;

	// The hash of the original version of the file
	unsigned int OriginalVersionHash;

	// The current revision number
	int CurrentRevision;

	// The length of the original version of the file in bytes
	int OriginalLength;

	// The length of the current version of the file in bytes
	int CurrentLength;

	// The last modified time of the file
	int ModifiedTime;

	// The primary ID of the file in the datastore
	int FileID;

	// Adds a new version of the file
	// Will fail if the hash of the filebuffer data is the same as the current version hash
	bool AddNewVersion(int FileLength, const char* FileBuffer, int LastModifiedTime);
        
    //uses murmur3 to get a 32 bit hash of the full file
    unsigned int GetHashOfFileBuffer(int FileLength, const char* FileBuffer);
        
    sql::Connection* dbcon;
};

#endif
