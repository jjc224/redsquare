#include "FileLib.h"
#include <algorithm>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

using namespace std;

static vector<string> FileLib::SplitPath(string path)
{
	vector<string> splittedPath;
	boost::split(splittedPath, path, boost::is_any_of("/"), boost::token_compress_on);    // Split path by forward slash ("/") into vector.

	return splittedPath;
}

// Replaces backslash, double backslash, and double forward slashes in a path with a single forward slash.
static string FileLib::Normalize(string path)
{
	size_t index = 0;

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
			path.replace(index, 1, "/");
			++index;    // Skip over inserted forward slash for the next iteration.
		}

		index = path.find("//", index);

		if(index != string::npos)
		{
			path.replace(index, 1, "/");
			++index;    // Skip over inserted forward slash for the next iteration.
		}
	}
}

static string FileLib::GetPath()
{
}

static string FileLib::GetFilename()
{
}

static struct tm FileLib::GetModifiedDate(string path)
{
}

static void FileLib::AppendPath(string path1, string path2)
{
}

static unsigned int FileLib::GetHash(string path)
{
}
