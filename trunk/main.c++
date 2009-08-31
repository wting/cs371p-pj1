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
    #include "TestCollatz.h"
#endif

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

// -------
// globals
// -------
int i; // input: don't change after reading
int j; // input: don't change after reading
int v; // output
bool lazy_cache = true;
unsigned long int lazy[1000000] = {0};

// ----------
// prototypes
// ----------
int eval();
int eval_iterative(int, unsigned long int);
int eval_recursive(int, unsigned long int);
void print(ostream &);
bool read(istream &);
void swap(int &, int &);

int main () {
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

    #ifdef TEST
        // ----------
        // unit tests
        // ----------
        CppUnit::TextTestRunner tr;
        tr.addTest(TestCollatz::suite());
        tr.run();
    #else
        // -------
        // program
        // -------
		while (read(cin)) {
			eval();
			print(cout);
		}
	#endif

	return 0;
}

int eval() {
	int x = i, y = j;
	if (x > y)
		swap (y,x);

	int max = 0, tmp = 0;
	for (int n=x; n<=y; ++n) {
		tmp = eval_iterative(0,n);

		if (tmp > max)
			max = tmp;
	}

	v = max;
	return max;
}

int eval_iterative(int cycle, unsigned long int n) {
	int cycle_path[1000] = {0};
	int path_loc = 0;

	while (n != 1) {
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
		c = cycle_path[path_loc++];
		if (c == 0 || c > 1000000)
			break;
		int cycle_count = cycle - (path_loc - 1);
		lazy[c] = cycle_count;
	}

	return cycle;
}

int eval_recursive(int cycle, unsigned long int n) {
	if (n == 1)
		return cycle;
	if (n%2 == 1)
		return eval_recursive(cycle+2,n + (n>>1) + 1);
	else
		return eval_recursive(cycle+1,n>>1);
}


void print(std::ostream &out) {
	/**
	 * prints the values of i, j, and v
	 */
    out << i << " " << j << " " << v << std::endl;
}

bool read(std::istream &in) {
	/**
	 * reads an int into i and j
	 * @return true if that succeeds, false otherwise
	 */
    if (!(in >> i))
        return false;
    in >> j;
    return true;
}

void swap (int &x, int &y) {
	x ^= y;
	y ^= x;
	x ^= y;
}
