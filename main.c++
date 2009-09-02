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
/// second input number
int j;
/// max cycle count between i and j ranges
int v;
/// lazy cache
unsigned long int lazy[1000000] = {0};

// ----------
// prototypes
// ----------
void eval();
int eval_iterative(int, unsigned long int);
int eval_recursive(int, unsigned long int);
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
	assert(x <= y);

	int max = 0, tmp = 0;
	for (int n=x; n<=y; ++n) {
		if (n % 1000 == 1 && y - n >= 1000) {
			tmp = meta[n/1000];
			n += 1000;
		} else {
			tmp = eval_iterative(0,n);
			assert(tmp == eval_recursive(1,n));
		}

	  if (tmp > max)
                max = tmp;
	}

	v = max;
}

int eval_iterative(int cycle, unsigned long int n) {
	/**
	calculates the 3n+1 cycle count of a number iteratively
	@param[cycle] cycle counter, should be passed in as 0 for 1st number
	@param[n] current value
	@return cycle count
	*/
	int cycle_path[1000] = {0};
	int path_loc = 0;

	while (n != 1) {
		///checks if n is present in lazy cache
		if (n < 1000000 && lazy[n] != 0) {
			cycle += lazy[n] - 1;
			break;
		}

		cycle_path[path_loc++] = n;
		if (n%2 == 1) {
			n = 3 * n + 1;
			cycle_path[path_loc] = n;
		}
		else
			n /= 2;
		++cycle;
	}
	++cycle;

	path_loc = 0;
	int c = 0;
	while (path_loc <= 1000) {
		///populates lazy cache
		c = cycle_path[path_loc++];
		if (c == 0 || c > 1000000)
			break;
		int cycle_count = cycle - (path_loc - 1);
		lazy[c] = cycle_count;
	}

	return cycle;
}

int eval_recursive(int cycle, unsigned long int n) {
	/**
	calculates the 3n+1 cycle count of a number recursively, included as a test function for iteration + lazy cache
	@param[cycle] cycle counter, should be passed in as 0 for 1st number
	@param[n] current value
	@return cycle count
	*/
	if (n == 1)
		return cycle;
	if (n%2 == 1)
		return eval_recursive(cycle+2,n + (n>>1) + 1);
	else
		return eval_recursive(cycle+1,n>>1);
}

void print(std::ostream &out) {
	/**
	prints the values of i, j, and v
	@param[in] out ostream to display results to
	*/
    out << i << " " << j << " " << v << std::endl;
}

bool read(std::istream &in) {
	/**
	reads an int into i and j
	@param[in] in istream to read in range values
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
	@param[in] x integer to swap
	@param[in] y integer to swap
	*/
	x ^= y;
	y ^= x;
	x ^= y;
}
