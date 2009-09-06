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
	#undef DEBUG
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
/// cache
int cache[1000000] = {0};

// ----------
// prototypes
// ----------
void eval();
int gen_iter(unsigned long int);
int gen_recurs(int, unsigned long int);
void gen_cache();
void print(std::ostream &);
bool read(std::istream &);
void swap(int &, int &);

// -----
// tests
// -----

#ifdef TEST
    #include "TestCollatz.h"
#endif // TEST

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
		if (n < 1000000 && cache[n] != 0) {
			tmp = cache[n];
			#ifdef DEBUG
				printf("early find, cache[%d] = %d\n",n,cache[n]);
			#endif
		} else {
			tmp = gen_iter(n);
			///implements naive lazy cache
			cache[n] = tmp;
			#ifdef DEBUG
				printf("not found in cache[%d], generated result = %d\n",n,tmp);
			#endif
		}
		#ifndef ONLINE_JUDGE
			if (tmp != gen_recurs(1,n))
				printf("MISMATCH: n = %d\t\titer = %d\trec = %d\n",n,tmp,gen_recurs(1,n));
			assert(tmp == gen_recurs(1,n));
		#endif

		if (tmp > max)
			max = tmp;
		}
	v = max;
}

void gen_cache() {
	/// generates an eager cache
	int i = 1;
	while (i < 100000) {
		cache[i] = gen_iter(i);
		++i;
	}
}

int gen_iter(int unsigned long n) {
	/**
	* generates 3n+1 cycle cout iteratively
	* @param [n] input number
	* @return cycle count
	*/
	printf(">gen_iter(%lu)\n",n);
	int cycle = 0;
	if (n == 1)
		return 1;
	else if (n == 2)
		return 2;
	while (n != 1) {
		printf("\tn = %lu\n",n);
		if ((n < 100000) && (cache[n] != 0)) {
			printf("\tfound cache[%lu] = %d\n\treturning %d\n",n,cache[n],cycle+cache[i]);
			return cycle + cache[n];
		}
		else if (n%2 == 1) {
			printf("\t>>!cache %lu ->",n);
			n = n + (n>>1) + 1;
			printf(" %lu\n\t>>cycle %d -> ",n,cycle);
			cycle += 2;
			printf("%d\n",cycle);
		}
		else {
			printf("\t>>!cache %lu ->",n);
			n /= 2;
			printf(" %lu\n\t>>cycle %d -> ",n,cycle);
			++cycle;
			printf("%d\n",cycle);
		}
	}
	return cycle;
}

int gen_recurs(int cycle, unsigned long int n) {
	/**
	* generates 3n+1 cycle count recursively, included for redundancy
	* @param [cycle] cycle counter, should be passed in as 0 for 1st number
	* @param [n] current value
	* @return cycle count
	*/
	if (n == 1)
		return cycle;
	if (n%2 == 1)
		return gen_recurs(cycle+2,n + (n>>1) + 1);
	else
		return gen_recurs(cycle+1,n>>1);
}

void print(std::ostream &out) {
	/**
	* prints the values of i, j, and v
	* @param [in] out ostream to display results to
	*/
    out << i << " " << j << " " << v << std::endl;
}

bool read(std::istream &in) {
	/**
	* reads an int into i and j
	* @param [in] in istream to read in range values
	* @return true if that succeeds, false otherwise
	*/
    if (!(in >> i))
        return false;
    in >> j;
    return true;
}

void swap (int &x, int &y) {
	/**
	* swaps two ints with each other
	* @param [in] x integer to swap
	* @param [in] y integer to swap
	*/
	x ^= y;
	y ^= x;
	x ^= y;
}

int main () {
    ios_base::sync_with_stdio(false); /// turn off synchronization with C I/O

    #ifdef TEST
        /// unit tests
        CppUnit::TextTestRunner tr;
        tr.addTest(TestCollatz::suite());
        tr.run();
    #else
        /// program execution
		gen_cache();
		while (read(cin)) {
			eval();
			print(cout);
		}
	#endif

	return 0;
}

