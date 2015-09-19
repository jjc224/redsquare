
#include <iostream>
#include "VersionRecord.h"

using namespace std;

VersionRecord::VersionRecord()
{

}
VersionRecord::~VersionRecord()
{

}

void VersionRecord::SetVersionIdentifier()
{

}

unsigned int VersionRecord::GetVersionIdentifier()
{

}

void VersionRecord::SetVersionNumber()
{

}
unsigned int VersionRecord::GetVersionNumber()
{

}

void VersionRecord::SetLength()
{

}

unsigned int VersionRecord::GetLength()
{

} 

void VersionRecord::SetOverallHash()
{

}
unsigned int VersionRecord::GetOverallHash()
{

} 

bool VersionRecord::CreateVersion(char * datastream, unsigned int length, VersionRecord &previousVersion)
{
    
}

unsigned int VersionRecord::GetBlockHash()
{
    
}
std::string VersionRecord::GetComment()
{

}

char * VersionRecord::GetFileData()
{
    
}

bool VersionRecord::IsValid()
{
    
}

int VersionRecord::GetNumBlocks()
{
    
}
