#include <iostream>

int gen_iter(int unsigned long n) {
	int cycle = 1;
	while (n != 1) {
		if (n%2 == 1) {
			n = n + (n>>1) + 1;
			++cycle;
		}
		else
			n /= 2;
		++cycle;
	}
	return cycle;
}

int main () {
	printf("int eager[50000] = {");
	for (int n = 1; n < 50000; ++n)
		//printf("%d:%d\n",n,gen_iter(n));
		printf("%d,",gen_iter(n));
	printf("};");

	return 0;
}
