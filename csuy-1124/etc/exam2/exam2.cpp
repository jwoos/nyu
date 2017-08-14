#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Cookie {
	public:
		Cookie(double diameter) : diameter(diameter) {}
	private:
		double diameter;
};

class CookieJar {
	public:
		CookieJar () = default;
	
		~CookieJar() {
			for (size_t i = 0; i < cookies.size(); i++) {
				delete cookies[i];
			}
			cookies.clear();
		}
		
		CookieJar(const CookieJar& rhs) {
			for (size_t i = 0; i < rhs.cookies.size(); i++) {
				cookies.push_back(nullptr);
				cookies[i] = new Cookie(*rhs.cookies[i]);
			}
		}
		
		CookieJar& operator=(const CookieJar& rhs) {
			if (&rhs != this) {
				for (size_t i = 0; i < rhs.cookies.size(); i++) {
					delete cookies[i];
				}
				cookies.clear();
				
				for (size_t i = 0; i < rhs.cookies.size(); i++) {
					cookies.push_back(nullptr);
					cookies[i] = new Cookie(*rhs.cookies[i]);
				}
			}
			return *this;
		}
	
		void addCookie(double diameter) {
			Cookie* aCookie = new Cookie(diameter);
			cookies.push_back(aCookie);
		}
	private:
		vector<Cookie*> cookies;
};

class Computer {
	public:
		virtual void work() const = 0;
};

class PC : public Computer {
	public:
		void work() const {
			cout << "*BLUE SCREEN OF DEATH*" << endl;
		}
};

class MAC : public Computer {
	public:
		void work() const {
			cout << "*WAITING FOR A YIELD*" << endl;
		}
};

class User {
	public:
		User(const string& name) : name(name) {}

		void buy(Computer& aComputer) {
			computers.push_back(&aComputer);
		}
		
		void work() {
			cout << "User: " << name <<  endl;
			for (int i = 0; i < computers.size(); i++) {
				cout << '\t';
				computers[i] -> work();
			}
			cout << "Press any key to continue..." << endl;
		}
	private:
		string name;
		vector<Computer*> computers;
};

int main() {
	PC pc1;
	PC pc2;
	MAC mac1;
	
	User tom("Tom");
	//User and("And");
	User jerry("Jerry");
	
	tom.buy(pc1);
	jerry.buy(pc2);
	jerry.buy(mac1);
	
	tom.work();
	//and.work();
	jerry.work();
}