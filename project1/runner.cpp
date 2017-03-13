/* Test runner
 * Runs against samples of text that is either given or dynamically generated.
 */

#include "utils.hpp"
#include "encryption.hpp"

int main(int argc, char** argv) {
	if (argc == 1) {
		cout << "Usage: main <ACTION> <FILENAME>" << endl;
		cout << "\tACTION: encrypt | decrypt" << endl;
		cout << "\tFILENAME: name of the file without the descriptors or extension" << endl;

		return 1;
	}
}
