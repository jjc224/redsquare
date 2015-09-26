#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;


// 	VersionRecord::CreateVersion
// 	VersionRecord::GetFileData


// Compresses a file given a path to a file
void zipCompress(string path)
{
	string command = "zip ";
	command.append(ZIP_WORK_PATH);
	command.append("temp.zip ");
	command.append(path);
	system(command.c_str());
}

// Compresses a file to 
void zipTempCompress()
{
	string command = "zip ";
	command.append(ZIP_WORK_PATH);
	command.append("temp.zip ");
	command.append(ZIP_WORK_PATH);
	command.append("* -j");
	system(command.c_str());
}

// Uncompresses a zip where it is
void zipUncompress()
{
	string command = "unzip -o ";
	command.append(ZIP_WORK_PATH);
	command.append("temp.zip -d ");
	command.append(ZIP_WORK_PATH);
	system(command.c_str());	
}

// Removes all files from temp folder
void zipRemoveContents()
{
	string command = "rm ";
	command.append(ZIP_WORK_PATH);
	command.append("*");
	system(command.c_str());
}

// Creates a copy of a file to the temp folder
void zipCopyContents(string path)
{
	string command = "cp ";
	command.append(path);
	command.append(" ");
	command.append(ZIP_WORK_PATH);
	system(command.c_str());
	cout << command << endl;
}

// Removes all zips from the temp folder
void zipRemoveZips()
{
	string command = "rm ";
	command.append(ZIP_WORK_PATH);
	command.append("*.zip");
}
