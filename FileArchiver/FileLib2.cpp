// Author: Joshua Coleman (jjc224).

#include "FileLib.h"
#include "MurmurHash3.h"
#include "ProjectConstants.h"
#include <boost/algorithm/string/classification.hpp>    // For FileLib::SplitPath(): string searching (boost::is_any_of()) to assist splitting.
#include <boost/algorithm/string/split.hpp>		// For FileLib::SplitPath(): string splitting (boost::split()).
#include <boost/algorithm/string.hpp>			// For FileLib::Normalize(): string trimming  (boost::algorithm::trim()).
#include <boost/regex.hpp>                              // For FileLib::Normalize(): substring replacement through regular expressions.
#include <boost/filesystem.hpp>                         // For FileLib::GetModificationDate(): uses boost::filesystem::last_write_time() to obtain modification date.

using namespace std;

// Remember to link boost_regex.

vector<string> FileLib::SplitPath(string path)
{
	vector<string> splittedPath;

	path = Normalize(path);
	boost::split(splittedPath, path, boost::is_any_of("/"), boost::token_compress_on);    // Split path by forward slash ("/") into vector.

	return splittedPath;
}

// Replaces one or more backslashes and two or more forward slashes with a single forward slash.
string FileLib::Normalize(string path)
{
	boost::regex re("\\\\+|//+");
	path = boost::regex_replace(path, re, "/");

	return path;
}

string FileLib::GetPath(string path)
{
	path = Normalize(path);
	size_t lastSlashIndex = path.find_last_of("/");

	if(lastSlashIndex != string::npos)
	{
		path = path.substr(0, lastSlashIndex);    // Whatever is up to the final slash must be the path.
	}

	return path;
}

string FileLib::GetFilename(string path)
{
	return SplitPath(Normalize(path)).back();
}

time_t FileLib::GetModifiedDate(string path)
{
	time_t modificationTime;
	path = Normalize(path);
	
	// Possibly temporary error-handling (and for illustration purposes).
	// I think error-handling should be handled by a higher-level class.
	try
	{
		modificationTime = boost::filesystem::last_write_time(path.c_str());
	}
	catch(const boost::filesystem::filesystem_error &e)
	{
		cerr << "FileLib::GetModifiedDate(): error accessing file '" << path << "' (" << e.code().message() << ")." << endl;
	}

	return modificationTime;
}

void FileLib::AppendPath(string &path1, string path2)
{
	path1.append(path2);
}

unsigned int FileLib::GetHash(string path)
{
	unsigned int hash;

	MurmurHash3_x86_32_FromFile(path, MURMUR_SEED_1, &hash);
	return hash;
}

int main(void)
{
	//string path = "/home/\\undergrad\\\\///j/jjc224/FileLibTest/FileLib.cpp";
	string path = "/home/undergrad/j/jjc224/FileLibTest/FileLib.cpp";	
	vector<string> splitted = FileLib::SplitPath(path);

	cout << "Vector: " << endl;

	for(vector<string>::iterator it = splitted.begin(); it != splitted.end(); ++it)
		cout << "\t" << *it << endl;
	cout << endl;

	cout << "GetPath: " << FileLib::GetPath(path) << endl;
	cout << "GetFilename: " << FileLib::GetFilename(path) << endl;
	cout << "GetModifiedDate: " << FileLib::GetModifiedDate(path) << endl;
	cout << "GetHash: " << FileLib::GetHash(path) << endl;

	return 0;
}
