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

vector<string> FileLib::SplitPath(string path)
{
	vector<string> splittedPath;

	path = Normalize(path);
	boost::split(splittedPath, path, boost::is_any_of("/"), boost::token_compress_on);    // Split path by forward slash ("/") into vector.

        // There will be a null-byte in the last string if the path ends in the delimiter.
        // So, remove it.
        if(splittedPath.back().empty())
            splittedPath.pop_back();
        
	return splittedPath;
}

// Replaces one or more backslashes and two or more forward slashes with a single forward slash.
string FileLib::Normalize(string path)
{
	boost::regex re("\\\\+|//+");
	path = boost::regex_replace(path, re, "/", boost::match_default | boost::format_all);

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
	return SplitPath(path).back();
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

string FileLib::AppendPath(string &path1, string path2)
{
	path1.append(path2);
        path1 = Normalize(path1);
        
        return path1;
}

unsigned int FileLib::GetHash(string path)
{
	unsigned int hash;

	MurmurHash3_x86_32_FromFile(path, MURMUR_SEED_1, &hash);
	return hash;
}
