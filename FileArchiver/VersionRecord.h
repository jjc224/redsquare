#ifndef VERSIONRECORD_H
#define VERSIONRECORD_H

#include <string>
class VersionRecord
{
public:
	
	// Constructor
	VersionRecord();
		
		// Constructor
	VersionRecord(std::string filename, unsigned int versionNumber);
	
	// Destructor
	~VersionRecord();
	
	// Returns the id of a version
	unsigned int GetVersionId(); 

	// Returns the version number
	unsigned int GetVersionNumber();

	// Returns the size 
	unsigned int GetSize(); 

	// Returns the hash of the 
	unsigned int GetHash();
        
        // Returns the modification time.
        unsigned int GetModificationTime();
        
        // Returns a formatted string of the modification time/date.
        std::string GetFormattedModificationTime();
	
	//public members for transfer of record to/from persistent storage - the function signatures will depend on the persistance mechanism that is chosen
	bool CreateVersion(std::string keyFilename, std::string pathFilename, unsigned int currentVersion, unsigned int newHash, std::string newComment);
	
	// Returns the comment on the version
	std::string GetComment();
	
	// Returns true if the data in Version is usable
	bool IsValid();
		
	bool GetFileData(std::string fileOutPath);
        
	void PurgeVersion();

	unsigned int RetrieveSizeFromDisk(std::string path);
	
protected:
	//retrieves the record information from the database
	bool RetrieveVersionRecordFromDB(std::string inFilename, unsigned int versionNumber);
	//updates the FileRecord in the database;
	bool UpdateRecordInDB();
	void Init();
	
	bool InsertVersionIntoDB(std::string keyFileName);

	bool InsertBlocks(std::string zipPath);
	
	//The version identifier - generated primary key
	unsigned int VersionID;
		
	std::string Filename;
		
	//The version number of this version
	unsigned int VersionNumber;
	//the length of this version in bytes
	unsigned int Size;
		
	unsigned int Time;
	unsigned int FileModificationTime;
	std::string Comment;
		
	//the has of the entire version of the file
	unsigned int Hash;
	//database connection
	sql::Connection* dbcon;
		
	bool bIsValid;
	
private:

};

#endif
