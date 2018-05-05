int foo(int x) {
	return x + 1;
}

int main(int dummy) {
	dummy = 0;

	write "in a loop!";

	while (dummy < 10) {
		write dummy;
		dummy = dummy + 1;
	}

	write "outside of loop!";
}
