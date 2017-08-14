#include <iostream>
#include <vector>

using namespace std;

int main(){
	vector<int> v;
	for (int i = 0; i < 100; i++)
		v.push_back(i * 2);

	for (int i : v) //for (int i=0; i<v.size(); i++) cout<<v[i]<<endl;
		cout << i << endl;
/*	double f;
	cout << "What \"F\" temp? ";
	cin >> f;
	double c = 5. / 9 * (f - 32);
	cout << "That temperature is: " << c << "C"<<endl;
	*/
}