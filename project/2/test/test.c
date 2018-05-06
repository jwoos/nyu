int b; /* parameter b is instead a global variable */
int euclid(int);
float euclid(int);

int main(int dummy) {
	int i, j;

	write "I am going to try and compute GCD using euclid's algorithm. Gimme two integers";
	read i, j;

	if (0>=i) {
		write "I wanted a positive number and you gave me ", i, "!!!!";
		return 17; /* there is no exit(...) or abort(...) */
	}

	if (0>=j) {
		write "I wanted a positive number and you gave me ", j, "!!!!";
		return 17; /* there is no exit(...) or abort(...) */
	}

	write "Will attempt to compute GCD(", i, ",", j, ")";
	b = j; /* horrible hack to pass the second parameter through a global.  does it work? */
	write euclid(i);
	return 0;
}

int euclid(int a) { /* both positive, just in case */
	int temp;

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
