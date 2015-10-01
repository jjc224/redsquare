/*
 * File:   FileLibTester.cpp
 * Author: jjc224
 *
 * Created on 23/09/2015, 4:24:17 PM
 */

#include "FileLibTester.h"
#include "FileLib.h"
#include <climits>

CPPUNIT_TEST_SUITE_REGISTRATION(FileLibTester);

void FileLibTester::testAppendPath()
{
    const std::size_t NUM_PATH_ELEMENTS_1 = 2;
    const std::size_t NUM_PATH_ELEMENTS_2 = 3;
    
    std::string pathElements1[NUM_PATH_ELEMENTS_1] = {"/test", "path1"};
    std::string pathElements2[NUM_PATH_ELEMENTS_2] = {"another", "path2", "test"};
    
    std::string path1          = generateUnormalizedPath(pathElements1, NUM_PATH_ELEMENTS_1);
    std::string path2          = generateUnormalizedPath(pathElements2, NUM_PATH_ELEMENTS_2);
    std::string expectedResult = "/test/path1/another/path2/test/";
    FileLib fileLib;
    std::string result = fileLib.AppendPath(path1, path2);

    CPPUNIT_ASSERT(result == expectedResult);
}

void FileLibTester::testGetFilename()
{
    const std::size_t NUM_PATH_ELEMENTS = 2;
    std::string pathElements[NUM_PATH_ELEMENTS] = {"/some", "path"};
    
    std::string file = "file.ext";
    std::string path = generateUnormalizedPath(pathElements, NUM_PATH_ELEMENTS) + file;
    FileLib fileLib;
    std::string result = fileLib.GetFilename(path);
    std::string expectedResult = file;
    
    CPPUNIT_ASSERT(result == expectedResult);
}

void FileLibTester::testGetPath()
{
    const std::size_t NUM_PATH_ELEMENTS = 5;
    std::string pathElements[NUM_PATH_ELEMENTS] = {"/path", "to", "file.ext"};
    
    std::string path = generateUnormalizedPath(pathElements, NUM_PATH_ELEMENTS);
    FileLib fileLib;
    std::string result = fileLib.GetPath(path);
    std::string expectedResult;
    
        // This produces a string of the form "/some/path/to/a/file".
    for(std::size_t i = 0; i < NUM_PATH_ELEMENTS - 1; ++i)    // The -1 is so that we don't include the filename.
        expectedResult += pathElements[i] + "/";
    
    CPPUNIT_ASSERT(result == expectedResult);
}

void FileLibTester::testNormalize()
{
    const std::size_t NUM_PATH_ELEMENTS = 5;
    std::string pathElements[NUM_PATH_ELEMENTS] = {"/some", "path", "to", "a", "file"};
    
    std::string path = generateUnormalizedPath(pathElements, NUM_PATH_ELEMENTS);
    FileLib fileLib;
    std::string result = fileLib.Normalize(path);
    
    std::string expectedResult;
    
    // This produces a string of the form "/some/path/to/a/file".
    for(std::size_t i = 0; i < NUM_PATH_ELEMENTS; ++i)
        expectedResult += pathElements[i] + "/";
    
    CPPUNIT_ASSERT(result == expectedResult);
}

void FileLibTester::testSplitPath()
{
    const std::size_t NUM_PATH_ELEMENTS = 5;
    std::string pathElements[NUM_PATH_ELEMENTS] = {"C:", "some", "test", "path", "file.ext"};
    std::vector<std::string> expectedResult;
    std::string path = generateUnormalizedPath(pathElements, NUM_PATH_ELEMENTS);
    
    for(std::size_t i = 0; i < NUM_PATH_ELEMENTS; ++i)
        expectedResult.push_back(pathElements[i]);
    
    FileLib fileLib;
    std::vector<std::string> result = fileLib.SplitPath(path);
    
    CPPUNIT_ASSERT(result == expectedResult);
}

// Helper functions (not in FileLib).
// To be tweaked (this is just a quick test).
std::string FileLibTester::generateUnormalizedPath(const std::string elements[], const std::size_t SIZE)
{
    std::string path, currPath;
    std::string delimiters[2] = {"/", "\\"};
    const int MAX_DELIMETER_SIZE = 2;
    
    // This produces a non-normalized path of the form:
    // elements[0]\elements[1]//elements[2]\\\elements[3]////...
    for(std::size_t i = 0; i < SIZE; ++i)
    {
        currPath = elements[i] + std::string(delimiters[(i + 1) % 2]);
        path.append(currPath);
    }

    return path;
}
