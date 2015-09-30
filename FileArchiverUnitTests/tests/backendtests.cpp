/*
 * File:   backendtests.cpp
 * Author: philipedwards
 *
 * Created on 30/09/2015, 6:40:09 PM
 */

#include "backendtests.h"
#include "MurmurHash3.h"
#include "ProjectConstants.h"
#include "TestUtilities.h"
#include "FileArchiver.h"
#include "FileRecord.h"
#include "VersionRecord.h"
#include "boost/lexical_cast.hpp"

#include <string>
using namespace std;


CPPUNIT_TEST_SUITE_REGISTRATION(backendtests);

backendtests::backendtests()
{
}

backendtests::~backendtests()
{
}

void backendtests::setUp()
{
	DropTables();
	CreateTables();
}

void backendtests::tearDown()
{
}

bool backendtests::GenerateFilesAndCommitVersionsAndVerifyRetrieval(std::string path, unsigned int size, unsigned int numVersions)
{	
	FileRecord myRecord;
	bool bSuccess = true;
	
	for(unsigned int i = 0; i < numVersions; i++)
	{
		if(bSuccess == false)
		{
			break;
		}
		string currentpath = path + "." + boost::lexical_cast<string>(i);
		createFile(i * 200, currentpath, size);
		if(i == 0)
		{
			bSuccess = myRecord.CreateFile(currentpath, "initial version");
			if(bSuccess == false)
			{
				log("ERROR: Failed to create new file: " + currentpath);
				CPPUNIT_ASSERT_MESSAGE("ERROR: Failed to create new file: " + currentpath,false);
			}
		}
		else
		{
			log("Trying to add new version");
			if(myRecord.IsValid())
			{
				bSuccess = myRecord.AddNewVersion(currentpath, "Version: " + boost::lexical_cast<string>(i) );
				if(bSuccess == false)
				{
					log("ERROR: Failed to create new version: " + currentpath);
					CPPUNIT_ASSERT_MESSAGE("ERROR: Failed to create new version: " + currentpath,false);
				}
			}
		}
		
	}
	
	if(bSuccess)
	{
		string originalName = path + ".0";
		for(unsigned int i = 0; i < numVersions; i++)
		{
			string currentpath = path + "." + boost::lexical_cast<string>(i) + ".ret";
			VersionRecord currentRecord(originalName, i + 1);
			unsigned int retrievedHash = 0;
			
			if(currentRecord.IsValid())
			{
				currentRecord.GetFileData(currentpath);
				MurmurHash3_x86_32_FromFile(currentpath, MURMUR_SEED_1, &retrievedHash);
				if(retrievedHash != currentRecord.GetHash())
				{
					log("HASHES DID NOT MATCH! " + currentpath);
					CPPUNIT_ASSERT_MESSAGE("HASHES DID NOT MATCH! " + currentpath,false);
					bSuccess = false;
					break;
				}
				else
				{
					log("Hashes matched. Retrieval worked correctly");
				}
			}
			else
			{
				bSuccess = false;
				CPPUNIT_ASSERT_MESSAGE("Invalid version record retrieved",false);
				break;
			}
		}
	}
	
	return bSuccess;
}

void backendtests::hashFileTest()
{
	string file1 = "testData/hashFile1.dat";
	string file2 = "testData/hashFile2.dat";
	
	//hash files of different lengths
	
	createFile(24000, file1, 14000);
	createFile(2888000, file2, 24000);
	
	unsigned int hash1 = 0;
	unsigned int hash2 = 0;
	
	MurmurHash3_x86_32_FromFile(file1, MURMUR_SEED_1, &hash1);
	MurmurHash3_x86_32_FromFile(file2, MURMUR_SEED_1, &hash2);
	
	//if the hashes match this is an error
	if(hash1 == hash2)
	{
		CPPUNIT_ASSERT_MESSAGE("Files of different lengths", false);
	}
	
	//hash files of the same length
	createFile(24000, file1, 14000);
	createFile(28000, file2, 14000);
	
	MurmurHash3_x86_32_FromFile(file1, MURMUR_SEED_1, &hash1);
	MurmurHash3_x86_32_FromFile(file2, MURMUR_SEED_1, &hash2);
	
	if(hash1 == hash2)
	{
		CPPUNIT_ASSERT_MESSAGE("Files of the same length", false);
	}
	
	
	//hash the same file with different seeds
	MurmurHash3_x86_32_FromFile(file1, MURMUR_SEED_1, &hash1);
	MurmurHash3_x86_32_FromFile(file1, MURMUR_SEED_2, &hash2);
	if(hash1 == hash2)
	{
		CPPUNIT_ASSERT_MESSAGE("Same file with different seeds", false);
	}
}

void backendtests::commitRetrieveTest()
{
	bool bSuccess;
	bSuccess = GenerateFilesAndCommitVersionsAndVerifyRetrieval("testData/20VersionFile.dat", 30000, 20);
	CPPUNIT_ASSERT_MESSAGE("20 version file had an unknown error", bSuccess);
	
	bSuccess = GenerateFilesAndCommitVersionsAndVerifyRetrieval("testData/30VersionFile.dat", 100000, 30);
	CPPUNIT_ASSERT_MESSAGE("30 version file had an unknown error", bSuccess);
	
	bSuccess = GenerateFilesAndCommitVersionsAndVerifyRetrieval("testData/40VersionFile.dat", 80000, 40);
	CPPUNIT_ASSERT_MESSAGE("40 version file had an unknown error", bSuccess);
}

void backendtests::purgeTest()
{
    std::string path  = "testData/purgeFile.dat";
    unsigned int size = 24000;
    unsigned int numVersions = 5, numVersionsToKeep = 2;
    bool bSuccess = GenerateFilesAndCommitVersionsAndVerifyRetrieval(path, size, numVersions);
    
    // GenerateFilesAndCommitVersionsAndVerifyRetrieval() will check equality of hashes on generation.
    CPPUNIT_ASSERT(bSuccess);
    
    log("Before purge.");
    
    FileRecord fileRec(path + ".0");
    
    CPPUNIT_ASSERT(fileRec.IsValid());
    fileRec.PurgeOldVersions(numVersionsToKeep);
    
    vector<VersionRecord> versionRecs = fileRec.GetAllVersions();
    
    // Check that the expected number of versions are the actual number of versions (post-purge).
    CPPUNIT_ASSERT(numVersionsToKeep == versionRecs.size());

    unsigned int hash;
    std::string testPath = path + ".ret";
    
    for(vector<VersionRecord>::iterator it = versionRecs.begin(); it != versionRecs.end(); ++it)
    {
        it->GetFileData(testPath);
        MurmurHash3_x86_32_FromFile(testPath, MURMUR_SEED_1, &hash);
        
        CPPUNIT_ASSERT(hash == it->GetHash());
    }
    
    log("End of test.");
}
