
#ifndef FILERECORD_H
#define FILERECORD_H

#include <string>
class FileRecord
{
public:
	//Gets the contents of a requested version number
	//Outputs the data into a supplied file buffer
	//Will not succeed if the buffer length is not large enough
	//Returns the success or failure of the retrieval
	bool GetVersionFileContents(int RequestedVersionNumber, char* OutFileBuffer, int BufferLength);
	//Same as previous definition, also outputs the length of the requested version in bytes to the supplied integer
	bool GetVersionFileContents(int RequestedVersionNumber, char* OutFileBuffer, int BufferLength, int& OutVersionLength);
	//returns the number of versions this file has
	int GetNumberOfVersions();
	//gets the full file path
	std::string GetFilename();
	//returns the length in bytes of the current file version
	int GetCurrentLength();
	//gets the length of a specific version of the file
	int GetVersionLength(int RequestedVersionNumber);
	//gets the primary id of the file
	int GetFileID();
	
	//Friendly function for adding a new file version
	//Returns false if the version has not changed
	bool AddNewVersion(std::string NewFileVersionPath);
protected:
	//the full path name of the file
	std::string Filename;
	//the hash of the current version of the file
	int CurrentVersionHash
	//the hash of the original version of the file
	int OriginalVersionHash;
	//the current revision number
	int CurrentRevision;
	//the length of the original version of the file in bytes
	int OriginalLength;
	//the length of the current version of the file in bytes
	int CurrentLength;
	//The last modified time of the file
	int ModifiedTime;
	//the primary ID of the file in the datastore
	int FileID;


	//Adds a new version of the file
	//Will fail if the hash of the filebuffer data is the same as the current version hash
	bool AddNewVersion(int FileLength, const char* FileBuffer, int LastModifiedTime);
private:
};

#endif
