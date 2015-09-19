
#include <iostream>
#include "VersionRecord.h"

using namespace std;

VersionRecord::VersionRecord()
{

}
VersionRecord::~VersionRecord()
{

}

unsigned int VersionRecord::GetVersionId()
{

}

unsigned int VersionRecord::GetVersionNumber()
{

}

unsigned int VersionRecord::GetSize()
{

} 

unsigned int VersionRecord::GetHash()
{

} 

bool VersionRecord::CreateVersion(string pathFilename)
{
    // Generate hash on disk
    
    // If hash exists
    
        // don't create and return false
    
    // Else
    
        // Create Version record in db
    
        // Open File

        // Get Block

        // Hash 1

        // Hash 2

        // Query DB Hash 1 in table Blocks

        // If hash 1 already exists

            // Query DB Hash 2 in table Blocks

            // If hash 2 already exists

                // Use existing block

            // Else

                // Create a new block

        // Else

            // Create new block
    
    
    
    
}

unsigned int VersionRecord::GetBlockHash()
{
    
}
std::string VersionRecord::GetComment()
{

}

bool VersionRecord::IsValid()
{
    
}
