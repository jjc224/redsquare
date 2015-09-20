
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
	FileRecord(std::string filename);

	//Creates the file record on the data 
	bool CreateFile(std::string filename);
	
	VersionRecord GetVersion(unsigned int versionID);
	
	void PurgeOldVersions(int numberOfVersionsToKeep);

	// Returns the number of versions this file has
	int GetNumberOfVersions();


	int GetCurrentVersionID();

	//Ensures there is a valid corresponding record in the database
	bool IsValid();

	bool GetVersionFileContents(int requestedVersionNumber, std::string fileOutPath);

	// Gets the full file path
	std::string GetFilename();

	// Gets the length of a specific version of the file
	int GetVersionLength(int requestedVersionNumber);

	// Gets the primary id of the file
	int GetFileID();
	
	// Friendly function for adding a new file version
	// Returns false if the version has not changed
	bool AddNewVersion(std::string NewFileVersionPath);
	bool AddNewVersion(int FileLength, const char* FileBuffer, int LastModifiedTime);

	//returns true if the file on disk has been modified
	//returns false if the file is the same
	//returns false if the file does not exist on disk
	bool IsChanged();

protected:
	bool RetrieveFileRecordFromDB(std::string inFilename);
	void Init();

	// The full path name of the file
	std::string Filename;

	// The hash of the current version of the file
	unsigned int CurrentVersionHash;

	// The current revision number
	unsigned int CurrentVersion;
        
        // the number of versions this file has had
        unsigned int NumberOfVersions;

	// The last modified time of the file
	int ModifiedTime;

	// The primary ID of the file in the datastore
	unsigned int FileID;

	// Adds a new version of the file
	// Will fail if the hash of the filebuffer data is the same as the current version hash
	

	//uses murmur3 to get a 32 bit hash of the full file
	unsigned int GetHashOfFileBuffer(int FileLength, const char* FileBuffer);

	sql::Connection* dbcon;

	bool bIsValid;
};

#endif
