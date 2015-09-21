// Author: Joshua Coleman (jjc224).

#include "FileLib.h"
#include <boost/algorithm/string/classification.hpp>    // For FileLib::SplitPath(): string searching (boost::is_any_of()) to assist splitting.
#include <boost/algorithm/string/split.hpp>		// For FileLib::SplitPath(): string splitting (boost::split()).
#include <boost/algorithm/string.hpp>			// For FileLib::Normalize(): string trimming  (boost::algorithm::trim()).
#include <boost/filesystem.hpp>                         // For FileLib::GetModificationDate(): uses boost::filesystem::last_write_time() to obtain modification date.

using namespace std;

vector<string> FileLib::SplitPath(string path)
{
	vector<string> splittedPath;

	Normalize(path);
	boost::split(splittedPath, path, boost::is_any_of("/"), boost::token_compress_on);    // Split path by forward slash ("/") into vector.

	return splittedPath;
}

// Replaces backslash, double backslash, and double forward slashes in a path with a single forward slash.
string FileLib::Normalize(string path)
{
    size_t index = 0;

    boost::algorithm::trim(path);    // Trim leading and trailing whitespace in path.

    while(index != string::npos)
    {
        index = path.find("\\", index);

        if(index != string::npos)
        {
            path.replace(index, 1, "/");
            ++index;    // Skip over inserted forward slash for the next iteration.
        }

        index = path.find("\\\\", index);

        if(index != string::npos)
        {
            path.replace(index, 2, "/");
            ++index;
        }

        index = path.find("//", index);

        if(index != string::npos)
        {
            path.replace(index, 2, "/");
            ++index;
        }
    }

    return path;
}

string FileLib::GetPath(string path)
{
	size_t lastSlashIndex = path.find_last_of("/");

	if(lastSlashIndex != string::npos)
	{
		path = Normalize(path).substr(0, lastSlashIndex);    // Whatever is up to the final slash must be the path.
	}

	return path;
}

string FileLib::GetFilename(string path)
{
	return string(SplitPath(path).back());    // vector::back() returns a reference, so have to construct a new string to return a copy.
}

time_t FileLib::GetModifiedDate(string path)
{
	time_t modificationTime;
	
	// Possibly temporary error-handling (and for illustration purposes).
	// I think error-handling should be handled by a higher-level class.
	try
	{
		modificationTime = boost::algorithm::last_write_time(path.c_str());
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

