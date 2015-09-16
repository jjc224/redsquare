
#ifndef VERSIONRECORD_H
#define VERSIONRECORD_H

#include <string>
class VersionRecord
{
public:
	
protected:
	//The version number of this version
	int VersionNumber;
	//the length of this version in bytes
	int Length;
	//the has of the entire version of the file
	int OverallHash;
private:

};

#endif