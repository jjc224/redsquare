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

void backendtests::testMethod()
{
	CPPUNIT_ASSERT(true);
}

void backendtests::testFailedMethod()
{
	CPPUNIT_ASSERT(false);
}

void backendtests::hashFileTest()
{
	string file1 = "testData/hashFile2.dat";
	string file2 = "testData/hashFile2.dat";
	
	//hash files of different lengths
	
	createFile(24000, file1, 14000);
	createFile(2888000, file2, 24000);
	
	unsigned int hash1;
	unsigned int hash2;
	
	MurmurHash3_x86_32_FromFile(file1, MURMUR_SEED_1, hash1);
	MurmurHash3_x86_32_FromFile(file2, MURMUR_SEED_1, hash2);
	
	if(hash1 == hash2)
	{
		//hashes are the same, this isn't right
		CPPUNIT_ASSERT(false);
	}
	
	//hash files of the same length
	
	//hash the same file with different seeds
}

void backendtests::commitRetrieveTest()
{

}

void backendtests::purgeTest()
{

}
