int testControlFlow(int a) {
	int b;
	int temp;

	write "Give me two positive numbers";
	read a, b;

	if (b > a) {
		temp = a;
		a = b;
		b = temp;
	}

	/* a<=b from this point on */

	while (b>0) {
		temp = a - b * (a/b); /* integer division; so get remainder */
		a = b;
		b = temp;
	}

	return a;
}

int testReadWrite(int y) {
	int x;
	write "testReadWrite";

	read x;

	write x+x, x*10, (x+y)*(-x-10*y);

	return x;
}

int main(int x) {
	x = testReadWrite(2);
	write testControlFlow(0);
}
