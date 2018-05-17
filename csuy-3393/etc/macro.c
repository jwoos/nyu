#include <stdio.h>


#define ADD(x, y) (x + y)


int add(int x, int y) {
	return x + y;
}


int main() {
	// expanded inline and has no address
	printf("ADD: %d\n", ADD(1, 2));
	// has an address and goes through function call
	printf("add: %d\n", add(1, 2));
}
