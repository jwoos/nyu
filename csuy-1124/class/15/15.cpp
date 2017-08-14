#include <cstdlib>

#include "princess.h"
#include "frogprince.h"

using namespace std;

class FrogPrince;

int main() {
	Princess snowy("Snow White");
	snowy.display();
	FrogPrince froggy("Froggy");
	froggy.display();
	snowy.marries(froggy);
	snowy.display();
}
