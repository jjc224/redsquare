#ifndef VERSIONRECORD_H
#define VERSIONRECORD_H

#include <string>
class VersionRecord
{
public:
	VersionRecord();
	~VersionRecord();
	//public accessor and mutator (get/set) functions for the most of private data members
	void SetVersionIdentifier();
	unsigned int GetVersionIdentifier(); 

	void SetVersionNumber();
	unsigned int GetVersionNumber();

	void SetLength();
	unsigned int GetLength(); 

	void SetOverallHash();
	unsigned int GetOverallHash(); 
	//public members for transfer of record to/from persistent storage - the function signatures will depend on the persistance mechanism that is chosen
	bool CreateVersion(char * datastream, unsigned int length, VersionRecord &previousVersion);
        unsigned int GetBlockHash();
        std::string GetComment();
        char * GetFileData();
        bool IsValid();
        int GetNumBlocks();
        
protected:
	//The version indentifier - generated primary key
	unsigned int VersionIdentifier;
	//The version number of this version
	unsigned int VersionNumber;
	//the length of this version in bytes
	unsigned int Length;
	//the has of the entire version of the file
	unsigned int OverallHash;
	 
private:

};

#endif