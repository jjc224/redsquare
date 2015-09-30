/*
 * File:   backendtests.h
 * Author: philipedwards
 *
 * Created on 30/09/2015, 6:40:09 PM
 */

#ifndef BACKENDTESTS_H
#define	BACKENDTESTS_H

#include <cppunit/extensions/HelperMacros.h>

class backendtests : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(backendtests);

    //CPPUNIT_TEST(testMethod);
    //CPPUNIT_TEST(testFailedMethod);
    CPPUNIT_TEST(hashFileTest);
    CPPUNIT_TEST(commitRetrieveTest);
    CPPUNIT_TEST(purgeTest);

    CPPUNIT_TEST_SUITE_END();

public:
    backendtests();
    virtual ~backendtests();
    void setUp();
    void tearDown();

private:
    //void testMethod();
    //void testFailedMethod();
    
    void hashFileTest();
    void commitRetrieveTest();
    void purgeTest();
};

#endif	/* BACKENDTESTS_H */

