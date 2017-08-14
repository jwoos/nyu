// Name: Junwoo Shin
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
using namespace std;

struct Hydrocarbon {
	string formula;
	vector<string> names;
};

void addMolecule(vector<Hydrocarbon>& hydrocarbons, const string& name, const string& formula);
vector<string> parseLine(string& line);
void printHydrocarbons(vector<Hydrocarbon>& hydrocarbons);

int main() {
	vector<Hydrocarbon> hydrocarbons;

	ifstream hydrocarbonFile("hydrocarbons.txt");

	if (!hydrocarbonFile) {
		cerr << "File not found" << endl;
		exit(1);
	}

	string line;
	// for each line parse the line to get the name and the formula
	// make a Hydrocarbon and push it to hydrocarbons vector
	while (getline(hydrocarbonFile, line)) {
		vector<string> wordsInLine = parseLine(line);
		string name = wordsInLine[0];
		string formula = wordsInLine[1];
		addMolecule(hydrocarbons, name, formula);
	}

	// print
	printHydrocarbons(hydrocarbons);
}

void addMolecule(vector<Hydrocarbon>& hydrocarbons, const string& name, const string& formula) {
	// check if it exists first to avoid unnecessary creation
	for (size_t index = 0; index < hydrocarbons.size(); index++) {
		if (hydrocarbons[index].formula == formula) {
			hydrocarbons[index].names.push_back(name);
			return;
		}
	}

	// if it doesn't exist
	Hydrocarbon aHydrocarbon;
	aHydrocarbon.formula = formula;
	aHydrocarbon.names.push_back(name);
	hydrocarbons.push_back(aHydrocarbon);
}

vector<string> parseLine(string& line) {
	// get name and formula and push it into words vector
	vector<string> words;
	string word = "";
	for (size_t index = 0; index <= line.size(); index++) {
		if (iswspace(line[index]) || index == line.size()) {
			words.push_back(word);
			word = "";
		} else {
			word += line[index];
		}
	}

	return words;
}

void printHydrocarbons(vector<Hydrocarbon>& hydrocarbons) {
	for (size_t index = 0; index < hydrocarbons.size(); index ++) {
		cout << hydrocarbons[index].formula << endl;
		for (size_t x = 0; x < hydrocarbons[index].names.size(); x++) {
			cout << hydrocarbons[index].names[x] << endl;
		}
		cout << endl;
	}
}
