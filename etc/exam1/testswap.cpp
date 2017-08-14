#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

int doubleLength(char** aStr) {
	int size = 1;
	int index = 0;
	while (*(aStr)[index] != '\0') {
		index++;
	}

	size *= 2;

	char* newArr = new char[size];
	newArr[0] = 'a';

	swap(newArr, *aStr);
	cout << newArr[0] << endl;
	newArr[size / 2 - 1] = ' ';
	newArr[size - 1] = '\0';
	delete [] *aStr;
	*aStr = newArr;
	return size;
}

int main() {
	char* aStr = new char[3];
	aStr[0] = 'c';

	doubleLength(&aStr);
}
