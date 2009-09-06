// To run the tests:
//     g++ -ansi -pedantic -lcppunit -ldl -Wall -DTEST main.c++ -o main.app
//     valgrind main.app

// To run the program:
//     g++ -ansi -pedantic -Wall main.c++ -o main.app
//     valgrind main.app < Collatz.in > Collatz.out

// To configure Doxygen:
//     doxygen -g
// That creates the file Doxyfile.
// Make the following edits:
//     EXTRACT_ALL            = YES
//     EXTRACT_PRIVATE        = YES
//     EXTRACT_STATIC         = YES
//     GENERATE_LATEX         = NO

// To document the program:
//     doxygen Doxyfile

// -------
// includes
// -------
#include <cassert>
#include <iostream>

using namespace std;

// -------
// defines
// -------
#ifdef TEST
    #include "cppunit/TestSuite.h"      // TestSuite
    #include "cppunit/TextTestRunner.h" // TestRunner
    //#include "TestCollatz.h"
#endif

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

// -------
// globals
// -------
/// first input number
int i;
/// second input number
int j;
/// max cycle count between i and j ranges
int v;
/// eager cache
int eager[100000] = {0};

// ----------
// prototypes
// ----------
void eval();
int gen_iter(unsigned long int);
int gen_recurs(int, unsigned long int);
void gen_eager();
void print(std::ostream &);
bool read(std::istream &);
void swap(int &, int &);

// -----
// tests
// -----

#ifdef TEST
    #include "TestCollatz.h"
#endif // TEST

int main () {
    ios_base::sync_with_stdio(false); /// turn off synchronization with C I/O

    #ifdef TEST
        /// unit tests
        CppUnit::TextTestRunner tr;
        tr.addTest(TestCollatz::suite());
        tr.run();
    #else
        /// program execution
		gen_eager();
		while (read(cin)) {
			eval();
			print(cout);
		}
	#endif

	return 0;
}

void eval() {
	/// eval traverses from i to j, calculating cycle count, keeps track of max cycle
	int x = i, y = j;
	if (x > y)
		swap (y,x);
	#ifndef ONLINE_JUDGE
		assert(x <= y);
	#endif

	int max = 0, tmp = 0;
	for (int n=x; n<=y; ++n) {
		///check meta-cache
		if (n % 1000 == 1 && y - n >= 1000) {
			tmp = meta[n/1000];
			n += 1000;
		} else {
		///perform 3n+1 computation
			tmp = eval_iterative(0,n);
		}
			#ifndef ONLINE_JUDGE
				int r = gen_recurs(1,n);
				if (tmp == r); /// tmp != r condition fails to ever work
				else
					printf("MISMATCH: n = %d\titer = %d\trecurs = %d\n",n,tmp,r);
				assert(tmp == r);
			#endif

		if (tmp > max)
			max = tmp;
		}
	v = max;
}

int gen_iter(int unsigned long n) {
	int cycle = 1;
	while (n != 1) {
		if ((i < 100000) && (eager[i] != 0))
			return cycle + eager[i];
		else if (n%2 == 1) {
			n = n + (n>>1) + 1;
			++cycle;
		}
		else
			n /= 2;
		++cycle;
	}
	return cycle;
}

int gen_recurs(int cycle, unsigned long int n) {
	/**
	calculates the 3n+1 cycle count of a number recursively, included as a test function for iteration + lazy cache
	@param [cycle] cycle counter, should be passed in as 0 for 1st number
	@param [n] current value
	@return cycle count
	*/
	if (n == 1)
		return cycle;
	if (n%2 == 1)
		return gen_recurs(cycle+2,n + (n>>1) + 1);
	else
		return gen_recurs(cycle+1,n>>1);
}

void gen_eager() {
	int i = 1;
	while (i < 100000) {
		eager[i] = gen_iter(i);
		++i;
	}
}

void print(std::ostream &out) {
	/**
	prints the values of i, j, and v
	@param [in] out ostream to display results to
	*/
    out << i << " " << j << " " << v << std::endl;
}

bool read(std::istream &in) {
	/**
	reads an int into i and j
	@param [in] in istream to read in range values
	@return true if that succeeds, false otherwise
	*/
    if (!(in >> i))
        return false;
    in >> j;
    return true;
}

void swap (int &x, int &y) {
	/**
	swaps two ints with each other
	@param [in] x integer to swap
	@param [in] y integer to swap
	*/
	x ^= y;
	y ^= x;
	x ^= y;
}
