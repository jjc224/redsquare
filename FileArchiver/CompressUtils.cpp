#include <iostream>
#include <cstdlib>
#include <string>
#include "CompressUtils.h"
#include "ProjectConstants.h"

using namespace std;


// 	VersionRecord::CreateVersion
// 	VersionRecord::GetFileData


// Compresses a file given a path to a file
void zipCompress()
{
	string command = "gzip -9 ";
	command.append(COMPRESSION_WORK_PATH);
	command.append("data");
	system(command.c_str());
}

// Uncompresses a zip to the specified location path
void zipUncompressTo(string path)
{
	string command = "gunzip -c ";
	command.append(COMPRESSION_WORK_PATH);
	command.append("data.gz > ");
	command.append(path);
	system(command.c_str());
	zipRemoveZip();
}

// Creates a copy of a file to the temp folder
void zipCopyContents(string path)
{
	string command = "cp ";
	command.append(path);
	command.append(" ");
	command.append(COMPRESSION_WORK_PATH);
	command.append("/data");
	system(command.c_str());
}

// Removes all files from temp folder
void zipRemoveZip()
{
	string command = "rm ";
	command.append(COMPRESSION_WORK_PATH);
	command.append("data.gz -f");
	system(command.c_str());
}
