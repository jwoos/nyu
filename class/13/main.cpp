#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <set>

using namespace std;

template <typename T>
class Stack {
	private:
		list<T> data;

	public:
		void push(const T& item) {
			data.push_front(item);
		}

		T pop() {
			T ret = top();
			data.pop_front();
			return ret;
		}

		T top() const {
			return *data.begin();
		}

		bool isEmpty() const {
			return data.size() == 0;
		}

		int size() const {
			return data.size();
		}

		void clear() {
			data.clear();
		}
};

int main() {
	Stack<char> s;

	for (int i = 0; i < 10; i++) {
		s.push('A' + i);
	}

	while(!s.isEmpty()) {
		cout << s.top() << endl;
		s.pop();
	}

	Stack<char> item;
	ifstream inFile("main.cpp");
	char temp;
	while (inFile >> temp) {
		if (temp == '(' || temp == '[' || temp == '{') {
			item.push(temp);
		} else if (temp == '}') {
			if (item.top() == '{') {
				cout << "Matched {}" << endl;
				item.pop();
			} else {
				cout << "SYNTAX ERROR, mismatched {}" << endl;
				return 0;
			}
		} else if (temp == ')') {
			if (item.top() == '(') {
				cout << "Matched ()" << endl;
				item.pop();
			} else {
				cout << "SYNTAX ERROR, mismatched ()" << endl;
				return 0;
			}
		} else if (temp == ']') {
			if (item.top() == '[') {
				cout << "Matched []" << endl;
				item.pop();
			} else {
				cout << "SYNTAX ERROR, mismatched []" << endl;
				return 0;
			}
		}
	}
}
