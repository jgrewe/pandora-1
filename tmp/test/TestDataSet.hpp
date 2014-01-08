// Copyright (c) 2013, German Neuroinformatics Node (G-Node)
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted under the terms of the BSD License. See
// LICENSE file in the root of the Project.

#include <iostream>
#include <sstream>
#include <iterator>
#include <stdexcept>
#include <limits>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>

#include <pandora.hpp>

using namespace pandora;

class TestDataSet:public CPPUNIT_NS::TestFixture {

public:

    void setUp();
    void testNDSize();
    void testChunkGuessing();
    void testBasic();
    void testSelection();
    void tearDown();

private:

    static unsigned int &open_mode();

    H5::H5File h5file;
    H5::Group h5group;

    CPPUNIT_TEST_SUITE(TestDataSet);
    CPPUNIT_TEST(testNDSize);
    CPPUNIT_TEST(testChunkGuessing);
    CPPUNIT_TEST(testBasic);
    CPPUNIT_TEST(testSelection);
    CPPUNIT_TEST_SUITE_END ();
};


