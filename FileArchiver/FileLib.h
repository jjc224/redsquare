#include <vector>
#include <string>
#include <ctime>    // For tm struct.

class FileLib
{
	public:
		static std::vector<string> SplitPath(std::string path);
		static std::string Normalize(std::string path);
		static std::string GetPath();
		static std::string GetFilename();
		static struct tm GetModifiedDate(std::string path);
		static void AppendPath(std::string path1, std::string path2);
		static unsigned int GetHash(std::string path);
};
