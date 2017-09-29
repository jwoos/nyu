#include <stdio.h>


int g(int a) {
	return a * 3;
}

int f(int a, int b) {
	return g(a) + g(b);
}

int main(void) {
	printf("%d\n", f(1, 2));

	return 0;
}
