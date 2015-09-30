/*
 * File:   FileLibTester.h
 * Author: jjc224
 *
 * Created on 23/09/2015, 4:24:16 PM
 */

#ifndef FILELIBTESTER_H
#define	FILELIBTESTER_H

#include <cppunit/extensions/HelperMacros.h>

class FileLibTester : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(FileLibTester);

    CPPUNIT_TEST(testAppendPath);
    CPPUNIT_TEST(testGetFilename);
    CPPUNIT_TEST(testGetPath);
    CPPUNIT_TEST(testNormalize);
    CPPUNIT_TEST(testSplitPath);

    CPPUNIT_TEST_SUITE_END();

public:
    /*
    FileLibTester();
    virtual ~FileLibTester();
    void setUp();
    void tearDown();
    */

private:
    void testAppendPath();
    void testGetFilename();
    void testGetHash();
    void testGetModifiedDate();
    void testGetPath();
    void testNormalize();
    void testSplitPath();

    // Helper functions (not in FileLib).
    std::string generateUnormalizedPath(const std::string elements[], const std::size_t SIZE);
};

#endif	/* FILELIBTESTER_H */

