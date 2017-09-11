#include <stdio.h>


void printNameAge() {
	int age;
	int heightFt;
	int heightIn;

	printf("My age is %d, and I am %d feet %d inches tall.\n", age, heightFt, heightIn);
}

void fizzBuzz() {
	for (int i = 1; i <= 100; i++) {
		int divisbleBy3 = (i % 3 == 0);
		int divisbleBy5 = (i % 5 == 0);

		if (divisbleBy3 && divisbleBy5) {
			printf("FizzBuzz\n");
		} else if (divisbleBy3) {
			printf("Fizz\n");
		} else if (divisbleBy5) {
			printf("Buzz\n");
		} else {
			printf("%d\n", i);
		}
	}
}

int main(int argc, char** argv) {
	printNameAge();
	fizzBuzz();
}
