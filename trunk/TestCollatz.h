// ----------------------------------
// projects/c++/collatz/TestCollatz.h
// Copyright (C) 2009
// Glenn P. Downing
// ----------------------------------

#ifndef TestCollatz_h
#define TestCollatz_h

// --------
// includes
// --------

#include <sstream> // istringtstream, ostringstream
#include <string>  // ==

#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END

// -----------
// TestCollatz
// -----------

struct TestCollatz : CppUnit::TestFixture {
    // ----
    // read
    // ----

    void test_read () {
        std::istringstream in("1 10\n");
        const bool b = read(in);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);}

    // ----
    // eval
    // ----

    void test_eval_1 () {
        i =  1;
        j = 10;
        v =  0;
        eval();
        CPPUNIT_ASSERT(v == 20);}

    void test_eval_2 () {
        i = 100;
        j = 200;
        v =   0;
        eval();
        CPPUNIT_ASSERT(v == 125);}

    void test_eval_3 () {
        i = 201;
        j = 210;
        v =   0;
        eval();
        CPPUNIT_ASSERT(v == 89);}

    void test_eval_4 () {
        i =  900;
        j = 1000;
        v =    0;
        eval();
        CPPUNIT_ASSERT(v == 174);}

    // -----
    // print
    // -----

    void test_print () {
        i =  1;
        j = 10;
        v = 20;
        std::ostringstream out;
        print(out);
        CPPUNIT_ASSERT(out.str() == "1 10 20\n");}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST_SUITE_END();};

#endif // TestCollatz_h
