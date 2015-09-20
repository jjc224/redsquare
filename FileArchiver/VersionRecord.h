#ifndef VERSIONRECORD_H
#define VERSIONRECORD_H

#include <string>
class VersionRecord
{
public:
	
	// Constructor
	VersionRecord();
	
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
	
	//public members for transfer of record to/from persistent storage - the function signatures will depend on the persistance mechanism that is chosen
	bool CreateVersion(std::string pathFilename);
	
	// Returns the comment on the version
	std::string GetComment();
	
	// Returns true if the data in Version is usable
	bool IsValid();
        
	bool GetFileData(std::string fileOutPath);
	 
protected:
	//The version identifier - generated primary key
	unsigned int VersionId;
	//The version number of this version
	unsigned int VersionNumber;
	//the length of this version in bytes
	unsigned int Size;
	//the has of the entire version of the file
	unsigned int OverallHash;
	//database connection
	sql::Connection* dbcon;
	
	// Returns 
	unsigned int GetBlockHash();
	
private:

};

#endif