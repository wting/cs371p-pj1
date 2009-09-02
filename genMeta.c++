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

int sliceSize = 1000;
int range[1000];
int curIndex = 0;

int eval();
int eval_recursive(int, int);
int eval_iterative(int, unsigned int);
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
        i = 1;
        j = sliceSize;
        
        while (j <= 1000000) {
          //cout << i << " " << j << endl;
          eval();
          //cout << v << endl;
          range[curIndex++] = v;
          v = 0;
          i += sliceSize;
          j += sliceSize;
        }

        
        //build the array
        unsigned long n;
        cout << "int meta = {";
        for (n = 0; n < 1000; n++) {
          cout << range[n];
          if ( n != 999) {
            cout << ", ";
          }
        }
        cout << "};" << endl;


        /*
        while (true) {
          cin >> i >> j;
          if (cin.eof())
            break;
          eval();
          //printf("%d %d %d\n",x,y,eval(x,y));
          print(cout);
        }
        */
    #endif

	return 0;
}

int eval() {
	unsigned long x = i, y = j;
	if (x > y)
		swap (y,x);

	int max = 0;
	int tmp;
	for (unsigned long n=x; n<=y; ++n) {
          //tmp = eval_recursive(1,n);
          tmp = eval_iterative(1,n);
		if (tmp > max)
			max = tmp;
	}

	v = max;
	return max;
}

int eval_recursive(int cycle,int n) {

	if (n == 1)
		return cycle;
	if (n%2 == 1)
		return eval_recursive(cycle+2,n + (n>>1) + 1);
	else
		return eval_recursive(cycle+1,n>>1);
}

int eval_iterative(int cycle,unsigned int n) {

  //cout << "n: " << n << endl;
  /*
  if (n >= 113001) {
    cout << "n: " << n << endl;
  }
  */
	while (n != 1) {
          /*
          if (n < 0) {
            cout << "overflow" << endl;
          }
          */
		if (n%2 == 1)
			n = 3*n+1;
		else
			n /= 2;
		++cycle;
	}
	return cycle;
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
