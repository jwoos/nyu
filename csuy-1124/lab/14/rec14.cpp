#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <algorithm>
#include <fstream>

using namespace std;

void printTask(int n) {
	cout << "Task " << n << endl;
}

void printBreak() {
	cout << "==============================" << endl;
}

void endLine() {
	cout << endl;
}

bool isEven(int n) {
	return n % 2 == 0;
}

void taskEight(const list<int>& aList) {
	printTask(8);
	for (list<int>::const_iterator iter = aList.begin(); iter != aList.end(); iter++) {
		cout << *iter << ' ';
	}
	endLine();
	printBreak();
}

void taskNine(const list<int>& aList) {
	printTask(9);
	for (int x : aList) {
		cout << x << ' ';
	}
	endLine();
	printBreak();
}

void taskTen(const list<int>& aList) {
	printTask(10);
	for (auto iter = aList.begin(); iter != aList.end(); iter++) {
		cout << *iter << ' ';
	}
	endLine();
	printBreak();
}

list<int>::const_iterator taskEleven(const list<int>& aList, int search) {
	printTask(11);
	for (list<int>::const_iterator iter = aList.begin(); iter != aList.end(); iter++) {
		if (*iter == search) {
			return iter;
		}
	}

	return aList.end();
}

auto taskTwelve(const list<int>& aList, int search) {
	printTask(12);
	for(auto iter = aList.begin(); iter != aList.end(); iter++) {
		if (*iter == search) {
			return iter;
		}
	}

	return aList.end();
}

list<int>::iterator ourFind(list<int>::iterator start, list<int>::iterator stop, int target) {
	cout << "find" << endl;
	for (list<int>::iterator p = start; p != stop; p++) {
		if (target == *p) {
			return p;
		}
	}
	return stop;
}

template<typename Searcher, typename Searchee>
Searcher ourFind(Searcher start, Searcher stop, Searchee target) {
	cout << "template find" << endl;
	for (Searcher p = start; p != stop; p++) {
		if (target == *p) {
			return p;
		}
	}
	return stop;
}

int main() {
	// task 1
	printTask(1);
	vector<int> oneVector = {6, 7, 8, 9, 10, 2, 1, 4, 15, 30, 100, 24, 50, 60, 39, 14};
	for (int x : oneVector) {
		cout << x << ' ';
	}
	endLine();
	printBreak();

	// task 2
	printTask(2);
	list<int> twoList(oneVector.begin(), oneVector.end());
	for (int x : twoList) {
		cout << x << ' ';
	}
	endLine();
	printBreak();

	// task 3
	printTask(3);
	sort(oneVector.begin(), oneVector.end());
	for (int x : oneVector) {
		cout << x << ' ';
	}
	endLine();
	printBreak();

	// task 4
	printTask(4);
	for (size_t x = 0; x < oneVector.size(); x+=2) {
		cout << oneVector[x] << ' ';
	}
	endLine();
	printBreak();

	// task 5
	printTask(5);
	/*
	 *for (size_t x = 0; x < twoList.size(); x+=2) {
	 *    cout << twoList[x] << ' ';
	 *}
	 */
	twoList.sort();
	for (int x : twoList) {
		cout << x << ' ';
	}
	endLine();
	printBreak();

	// task 6
	printTask(6);
	for (vector<int>::iterator it = oneVector.begin(); it != oneVector.end(); it += 2) {
		cout << *it << ' ';
	}
	endLine();
	printBreak();

	// task 7
	printTask(7);
	bool taskSeven = true;
	for (list<int>::iterator it = twoList.begin(); it != twoList.end(); it++) {
		if (taskSeven) {
			cout << *it << ' ';
		}
		taskSeven = !taskSeven;
	}
	endLine();
	printBreak();

	// task 8
	taskEight(twoList);

	// task 9
	taskNine(twoList);

	// task 10
	taskTen(twoList);

	// task 11
	//taskEleven(twoList, 2000);
	taskEleven(twoList, 1);
	endLine();
	printBreak();

	// task 12
	taskTwelve(twoList, 1);
	endLine();
	printBreak();

	// task 13
	printTask(13);
	find(twoList.begin(), twoList.end(), 1);
	endLine();
	printBreak();

	// task 14
	printTask(14);
	cout << *find_if(twoList.begin(), twoList.end(), isEven) << endl;
	endLine();
	printBreak();

	// task 15
	printTask(15);
	cout << *find_if(twoList.begin(), twoList.end(), [](int x) {return x % 2 == 0;}) << endl;
	endLine();
	printBreak();

	// task 16
	printTask(16);
	int arr[oneVector.size()];
	copy(oneVector.begin(), oneVector.end(), arr);
	for (size_t x = 0; x < oneVector.size(); x++) {
		cout << arr[x] << ' ';
	}
	cout << *find(arr, arr + oneVector.size(), 1) << endl;
	cout << *find(arr, arr + oneVector.size(), 200) << endl;
	endLine();
	endLine();
	printBreak();

	// task 17
	printTask(17);
	ourFind(twoList.begin(), twoList.end(), 1);
	endLine();
	printBreak();

	// task 18
	printTask(18);
	ourFind(oneVector.begin(), oneVector.end(), 1);
	endLine();
	printBreak();

	// task 19
	printTask(19);
	ifstream ifs;
	ifs.open("lab/14/pooh-nopunc.txt");
	vector<string> taskNineteen;
	string word;
	while (ifs >> word) {
		if (find(taskNineteen.begin(), taskNineteen.end(), word) == taskNineteen.end()) {
			taskNineteen.push_back(word);
		}
	}
	for (string aWord : taskNineteen) {
		cout << aWord << ' ';
	}
	endLine();
	endLine();
	printBreak();

	// task 20
	printTask(20);
	set<string> taskTwenty;
	ifs.clear();
	ifs.seekg(0);
	while (ifs >> word) {
		taskTwenty.insert(word);
	}
	for (string aWord : taskTwenty) {
		cout << aWord << ' ';
	}
	endLine();
	endLine();
	printBreak();

	// task 21
	printTask(21);
	map<string, vector<int>> wordMap;
	ifs.clear();
	ifs.seekg(0);
	while (ifs >> word) {
		wordMap[word].push_back(ifs.tellg());
	}
	for (auto loopVar : wordMap) {
		cout << loopVar.first << ": ";
		for (int x : loopVar.second) {
			cout << x << ' ';
		}
		endLine();
	}
	printBreak();
}


