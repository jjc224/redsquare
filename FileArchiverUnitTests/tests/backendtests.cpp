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
#include "FileRecord.h"
#include "VersionRecord.h"

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
}

void backendtests::tearDown()
{
}

void backendtests::hashFileTest()
{
}

void backendtests::commitRetrieveTest()
{

}

void backendtests::purgeTest()
{
    DropTables();
    CreateTables();
    
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
