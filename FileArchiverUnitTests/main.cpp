/*
 * File:   main.cpp
 * Author: philipedwards
 *
 * Created on 16 September 2015, 11:53 AM
 */

#include "ProjectConstants.h"
#include "FileRecord.h"

#include <string>

#include "TestUtilities.h"
#include "FileArchiver.h"
#include "boost/lexical_cast.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	// initialize resources, if needed
	// Q_INIT_RESOURCE(resfile);
	
	DropTables();
	CreateTables();
	GenerateFilesAndCommitVersionsAndVerifyRetrieval("testData/testDataagain.dat", 20000,100);
	
        /*
	
	
	RunTestCommitFileOneVersionRetrieve();
	//RunTestCommitFileWithTwoVersionsRetrieveBoth();
	
	FileArchiver test;
	vector<FileRecord> files = test.GetFiles();
	
	for(unsigned int i = 0; i < files.size(); i++)
	{
		log("File found in database: " + files[i].GetFilename() + " " + boost::lexical_cast<string>(files[i].GetCurrentVersionNumber()));
	}
        */
    //RunTestPurge();
      
	return 0;
	
	//return 0;
}

