// Author: Joshua Coleman (jjc224).

#include <vector>
#include <string>

class FileLib
{
	public:
		static std::vector<string> SplitPath(std::string path);
		static std::string Normalize(std::string path);
		static std::string GetPath(std::string path);
		static std::string GetFilename(std::string path);
		static time_t GetModifiedDate(std::string path);                  // Returns modification date in seconds.
		static void AppendPath(std::string &path1, std::string path2);    // Appends path2 onto path1.
		static unsigned int GetHash(std::string path);
};

