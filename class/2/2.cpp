#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void openInputFile(ifstream& inFile) {
	string file;
	cout << "What is the file?" << endl;
	cin >> file;
	inFile.open(file);
	while (!inFile) {
		cout << "BAD FILENAME" << endl;
		cout << "What is the file?" << endl;
		cin >> file;
		inFile.clear();
		inFile.open(file);
	}
}

class Student {
	public:
		Student(int id) :id(id) {}
		string name;
		int getId() const {
			return id;
		}
	private:
		int id;
};

class School {
	private:
		vector<Student> students;
	public:
		void addStudent(string name);
};

class BigInt {
	private:
		unsigned int data;
	public:
		BigInt(int newData = 0) : data(newData) {}

		int getData() const {
			return data;
		}

		BigInt& operator+=(const BigInt& rhs) {
			data += rhs.data;
			return *this;
		}

		BigInt& operator++() {
			data++;
			return *this;
		}

		BigInt operator++(int dummy) {
			BigInt temp(*this);
			data++;
			return temp;
		}

		BigInt& operator--() {
			data--;
			return *this;
		}

		BigInt operator--(int dummy) {
			BigInt temp(*this);
			data--;
			return temp;
		}

		bool operator[](int pos) const {
			return ((int)(data / pow(2, pos)) % 2) == 1;
		}
}

BigInt operator+(const BigInt& rhs, const BigInt& lhs) {
	BigInt temp(lhs);
	temp += rhs;
	return temp;
}

void Student::addStudent(string name)i {
	int nextId = 1;
	if (students.size() != 0) {
		nextId = students[students.size() - 1].getId() + 1;
	}
	students.push_back(Student(nextId));
	students[students.size() - 1].name = name;
};

void filVec(vector<Student>& vec, ifstream& inFile) {
	Student temp;
	while (inFile >> temp.id) {
		getline(inFile, temp.name);
		vec.push_back(temp);
	}
}

int main() {
	int* ptr = new int();
	int* arr = new int[100];
}
