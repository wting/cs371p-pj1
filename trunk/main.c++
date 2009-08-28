#include <iostream>

using namespace std;

int eval(int,int);
int eval_recursive(int, int);
//int eval_iterative(int, int);
void swap(int &, int &);

int main () {
	int x,y;

	while (true) {
		//printf("input x y: ");
		cin >> x >> y;
		if (cin.eof())
			break;
		printf("%d %d %d\n",x,y,eval(x,y));
	}

	return 0;
}

int eval(int x, int y) {
	if (x > y)
		swap (x,y);

	int max = 0;
	int tmp;
	for (int i=x; i<=y; ++i) {
		tmp = eval_recursive(1,i);
		//tmp = eval_iterative(1,i);
		if (tmp > max)
			max = tmp;
	}

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

/*int eval_iterative(int cycle,int n) {
	while (n != 1) {
		if (n%2 == 1)
			n = 3*n+1;
		else
			n /= 2;
		++cycle;
	}
	return cycle;
}
*/

void swap (int &x, int &y) {
	x ^= y;
	y ^= x;
	x ^= y;
}
