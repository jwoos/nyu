/*
 * name: Junwoo Shin
 * class: Section E
 * compiler: g++-6 (Ubuntu 6.2.0-3ubuntu11~16.04) 6.2.0 20160901
 * commands: g++-6 -Wall -g -std=c++14 hw2.cpp
 */

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

class Timer {
	public:
		Timer() {
			start = clock();
		}

		double elapsed() const {
			return (clock() - start) / CLOCKS_PER_SEC;
		}

		void reset() {
			start = clock();
		}
	private:
		double start;
};

bool is_prime1(int n) {
	if (n == 1 || n == 2) {
		return true;
	}

	for (int i = n / 2; i > 1; i--) {
		if (is_prime1(i) && n % i == 0) {
			return false;
		}
	}

	return true;
}

int count_primes1(int n) {
	int primeCount = 0;

	for (int i = 2; i <= n; i++) {
		if (is_prime1(i)) {
			primeCount++;
		}
	}

	return primeCount;
}

bool is_prime2(int n) {
	if (n == 1) {
		return true;
	}

	for (int i = n / 2; i > 1; i--) {
		if (n % i == 0) {
			return false;
		}
	}

	return true;
}

int count_primes2(int n) {
	int primeCount = 0;

	for (int i = 2; i <= n; i++) {
		if (is_prime2(i)) {
			primeCount++;
		}
	}

	return primeCount;
}

bool is_prime3(int n) {
	if (n == 1) {
		return true;
	}

	for (int i = floor(sqrt(n)); i > 1; i--) {
		if (n % i == 0) {
			return false;
		}
	}

	return true;
}

int count_primes3(int n) {
	int primeCount = 0;

	for (int i = 2; i <= n; i++) {
		if (is_prime3(i)) {
			primeCount++;
		}
	}

	return primeCount;
}

int main() {
	Timer t;

	int method;
	int n;

	while (true) {
		cout << "Which method (1, 2, 3 or 0 = exit): ";
		cin >> method;

		if (method == 0) {
			exit(0);
		} else if (!(1 <= method && method <= 3)) {
			cout << "Invalid method" << endl;
			exit(1);
		}

		cout << "Enter the value of n: ";
		cin >> n;

		t.reset();
		cout << "There are ";
		if (method == 1) {
			cout << count_primes1(n);
		} else if (method == 2) {
			cout << count_primes2(n);
		} else if (method == 3) {
			cout << count_primes3(n);
		}
		cout << " prime numbers between 2 and " << n << endl;
		cout << "Time to compute: approximately " << t.elapsed() << 's' << endl;
	}
}

/*

1)  n       | is_prime1 | is_prime2 | is_prime3
   ---------------------------------------------
    100     | 0.000485s | 1.1e-05s  | 1.1e-05s
	150     | 0.001854s | 1.4e-05s  | 1.3e-05s
	200     | 0.009048s | 1.8e-05s  | 1.6e-05s
	250     | 0.0323s   | 2.4e-05s  | 1.7e-05s
	300     | 0.092561s | 2.9e-05s  | 1.9e-05s
	400     | 0.498353s | 4.9e-05s  | 2.5e-05s
	500     | 2.1628s   | 6.6e-05s  | 2.9e-05s
	750     | 35.1563s  | 0.000137s | 7.1e-05s
	1000    | 270.706s  | 0.000414s | 5.9e-05s
	5000    |           | 0.00593s  | 0.000521s
	10000   |           | 0.023983s | 0.001272s
	50000   |           | 0.600036s | 0.012306s
	100000  |           | 2.37684s  | 0.033986s
	500000  |           | 61.9175s  | 0.362955s
	1000000 |           |           | 1.0612s
	5000000 |           |           | 11.8548s

2)
  is_prime2 = O(n)
    this iterates over every single number between 2 and n, regardless of any other conditions so it will be O(n).

  is_prime3 = O(log(n))
    this only iterates over a number that is less than the square root of n, so there's a lot less numbers to iterate over. The square root makes it logarithmic.

   n       | is_prime2 | is_prime3 | is_prime2 / n| is_prime2 / n^2 | is_prime3 / log(n) | is_prime3 / n*log(n)
  --------------------------------------------------------------------------------------------------------------
   100     | 1.1e-05s  | 1.1e-05s  | 1.10e-07     | 1.10e-09        | 1.00e+02           | 5.50e-08
   150     | 1.4e-05s  | 1.3e-05s  | 9.33e-08     | 6.22e-10        | 1.39e+02           | 3.98e-08
   200     | 1.8e-05s  | 1.6e-05s  | 9.00e-08     | 4.50e-10        | 1.78e+02           | 3.48e-08
   250     | 2.4e-05s  | 1.7e-05s  | 9.60e-08     | 3.84e-10        | 1.77e+02           | 2.84e-08
   300     | 2.9e-05s  | 1.9e-05s  | 9.67e-08     | 3.22e-10        | 1.97e+02           | 2.56e-08
   400     | 4.9e-05s  | 2.5e-05s  | 1.23e-07     | 3.06e-10        | 2.04e+02           | 2.40e-08
   500     | 6.6e-05s  | 2.9e-05s  | 1.32e-07     | 2.64e-10        | 2.20e+02           | 2.15e-08
   750     | 0.000137s | 7.1e-05s  | 1.83e-07     | 2.44e-10        | 3.89e+02           | 3.29e-08
   1000    | 0.000414s | 5.9e-05s  | 4.14e-07     | 4.14e-10        | 1.43e+02           | 1.97e-08
   5000    | 0.00593s  | 0.000521s | 1.19e-06     | 2.37e-10        | 4.39e+02           | 2.82e-08
   10000   | 0.023983s | 0.001272s | 2.40e-06     | 2.40e-10        | 5.30e+02           | 3.18e-08
   50000   | 0.600036s | 0.012306s | 1.20e-05     | 2.40e-10        | 1.03e+03           | 5.24e-08
   100000  | 2.37684s  | 0.033986s | 2.38e-05     | 2.38e-10        | 1.43e+03           | 6.80e-08
   500000  | 61.9175s  | 0.362955s | 1.24e-04     | 2.48e-10        | 2.93e+03           | 1.27e-07
   1000000 |           | 1.0612s   |              |                 |                    |
   5000000 |           | 11.8548s  |              |                 |                    |

  It seems as if the constant for is_prime2 is hovering while there is almost a constant increase for is_prime3.
  however, we do need to take into account that this was run against count_prime2/3 which means the total complexity will be multiplied by n.
  So count_prime2 will be O(n^2) and count_prime3 will be O(n*log(n)). It seems as if we do the latter, the constants seem to hover around the same area instead of fluctuating.


3)
  log (n^5) = O(2^n)

  300 n^2 + 20 n + n^4 = O(n^2)

  n * log (n+12) = O(n*log(n))

  100n + 4n^2 + 12 log n = O(n^2)

  log n + n/100 = O(n*log(n))

  sqrt(6n) * ( log n + 10) = O(n*log(n))

  n + (n-1) + (n-2) + ... + 1 = O(n^2)

4)
  a) O(n^2)

  b) O(n*log(n))

  c) O(log(n))
*/
