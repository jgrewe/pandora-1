// Copyright (c) 2015, German Neuroinformatics Node (G-Node)
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted under the terms of the BSD License. See
// LICENSE file in the root of the Project.

#ifndef NIX_TESTENTITYFS_HPP
#define NIX_TESTENTITYFS_HPP

#include "BaseTestEntity.hpp"

class TestEntityFS : public BaseTestEntity {

    CPPUNIT_TEST_SUITE(TestEntityFS);

    CPPUNIT_TEST(testId);
    CPPUNIT_TEST(testType);
    CPPUNIT_TEST(testName);
    CPPUNIT_TEST(testDefinition);

    CPPUNIT_TEST(testUpdatedAt);
    CPPUNIT_TEST(testCreatedAt);

    CPPUNIT_TEST_SUITE_END ();

public:
    void setUp() {
        startup_time = time(NULL);
        file = nix::File::open("test_block", nix::FileMode::Overwrite, "file");
        block = file.createBlock("block_one", "dataset");
        block_other = file.createBlock("block_other", "dataset");
        block_null = nix::none;
    }

    void tearDown() {
        file.close();
    }
};

#endif //NIX_TESTENTITYFS_HPP
