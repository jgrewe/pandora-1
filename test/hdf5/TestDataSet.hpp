// Copyright (c) 2013, German Neuroinformatics Node (G-Node)
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted under the terms of the BSD License. See
// LICENSE file in the root of the Project.

#include <nix/hydra/multiArray.hpp>
#include <nix.hpp>

#include "hdf5/h5x/H5Group.hpp"

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


class TestDataSet:public CPPUNIT_NS::TestFixture {

public:

    void setUp();
    void testChunkGuessing();
    void testDataType();
    void testDataTypeFromString();
    void testDataTypeIsNumeric();
    void testBasic();
    void testNDArrayIO();
    void testValArrayIO();
    void testOpaqueIO();
    void tearDown();

private:

    static unsigned int &open_mode();

    hid_t h5file;
    nix::hdf5::H5Group h5group;

    CPPUNIT_TEST_SUITE(TestDataSet);
    CPPUNIT_TEST(testChunkGuessing);
    CPPUNIT_TEST(testDataType);
    CPPUNIT_TEST(testDataTypeFromString);
    CPPUNIT_TEST(testDataTypeIsNumeric);
    CPPUNIT_TEST(testBasic);
    CPPUNIT_TEST(testNDArrayIO);
    CPPUNIT_TEST(testValArrayIO);
    CPPUNIT_TEST(testOpaqueIO);
    CPPUNIT_TEST_SUITE_END ();
};


