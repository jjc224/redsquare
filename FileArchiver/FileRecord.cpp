
#include "FileRecord.h"
#include "MurmurHash3.h"
#include <stdint.h>

unsigned int FileRecord::GetHashOfFileBuffer(int FileLength, const char* FileBuffer)
{
	uint32_t out;
	MurmurHash3_x86_32(FileBuffer, FileLength, 10000, &out);
	return out;
}
