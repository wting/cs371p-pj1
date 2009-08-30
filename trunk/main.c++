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
/*#ifdef TEST
    #include "cppunit/TestSuite.h"      // TestSuite
    #include "cppunit/TextTestRunner.h" // TestRunner
    #include "TestCollatz.h"
#endif

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif*/

// -------
// globals
// -------
int i; // input: don't change after reading
int j; // input: don't change after reading
int v; // output

// -------
// prototypes
// -------
void eval();
void eval_iterative(int);
//void eval_recursive(int,int);
int eval_recursive(int,int);
void print(ostream &);
bool read(istream &);

int main () {
    //ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

    /*#ifdef TEST
        // ----------
        // unit tests
        // ----------
        CppUnit::TextTestRunner tr;
        tr.addTest(TestCollatz::suite());
        tr.run();
    #else*/
        // -------
        // program
        // -------
        while (read(cin)) {
            eval();
            print(cout);
		}
    //#endif // TEST

	return 0;
}

void eval() {
	v = 0;
	int tmp;
	for (int x=i; x<=j; ++x) {
		tmp = eval_recursive(1,x);
		//eval_iterative(x);
		if (tmp > v)
			v = tmp;
	}
}

int eval_recursive(int cycle,int n) {
	if (n == 1)
		return cycle;
	if (n%2 == 1)
		return eval_recursive(cycle+2,n + (n>>1) + 1);
	else
		return eval_recursive(cycle+1,n>>1);
}

/*void eval_recursive(int cycle, int n) {
	if (n == 1) {
		if (cycle > v)
			v = cycle;
	}
	else if (n%2 == 1)
		eval_recursive(cycle+2,n+(n>>1)+1);
	else
		eval_recursive(cycle+1,n>>1);
}*/

void eval_iterative(int n) {
	int cycle = 1;
	while (n != 1) {
		if (n%2 == 1) {
			n = n+(n>>1)+1;
			++cycle;
		}
		else
			n = n>>1;
		++cycle;
	}
	if (cycle > v)
		v = cycle;
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
