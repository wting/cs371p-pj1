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
		/// tests read stream function
        std::istringstream in("1 10\n");
        const bool b = read(in);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);}

    // ----
    // eval
    // ----

    void test_eval_1 () {
		/// tests eval results
        i =  1;
        j = 10;
        v =  0;
        eval();
        CPPUNIT_ASSERT(v == 20);}

    void test_eval_2 () {
		/// tests eval results
        i = 100;
        j = 200;
        v =   0;
        eval();
        CPPUNIT_ASSERT(v == 125);}

    void test_eval_3 () {
		/// tests eval results
        i = 201;
        j = 210;
        v =   0;
        eval();
        CPPUNIT_ASSERT(v == 89);}

    void test_eval_4 () {
		/// tests eval results
        i =  900;
        j = 1000;
        v =    0;
        eval();
        CPPUNIT_ASSERT(v == 174);}

    // -------------------------
    // Added by Ting and Raleigh
    // -------------------------

    void test_eval_5 () {
		/// tests eval results
        i = 33333;
        j = 44444;
        v =     0;
        eval();
        CPPUNIT_ASSERT(v == 324);}

    void test_eval_6 () {
		/// tests eval results
        i = 11111;
        j = 22222;
        v =     0;
        eval();
        CPPUNIT_ASSERT(v == 279);}

    void test_eval_7 () {
		/// tests eval results
        i = 67899;
        j = 60656;
        v =     0;
        eval();
        CPPUNIT_ASSERT(v == 335);}

    void test_eval_8 () {
		/// tests eval results
        i = 45;
        j = 43;
        v =  0;
        eval();
        CPPUNIT_ASSERT(v == 30);}

    void test_eval_9 () {
		/// tests eval results
        i = 3130;
        j =  193;
        v =    0;
        eval();
        CPPUNIT_ASSERT(v == 217);}

    // -----
    // print
    // -----

    void test_print () {
		/// tests print output
        i =  1;
        j = 10;
        v = 20;
        std::ostringstream out;
        print(out);
        CPPUNIT_ASSERT(out.str() == "1 10 20\n");}

    void test_swap() {
		/// tests swap
		i = 4;
		j = 5;
		swap(i, j);
		CPPUNIT_ASSERT(i == 5);
		CPPUNIT_ASSERT(j == 4);
	}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_eval_5);
    CPPUNIT_TEST(test_eval_6);
    CPPUNIT_TEST(test_eval_7);
    CPPUNIT_TEST(test_eval_8);
    CPPUNIT_TEST(test_eval_9);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_swap);
    CPPUNIT_TEST_SUITE_END();};

#endif // TestCollatz_h
