/*
 *Name: Junwoo Shin
 *Course: CS-UY 11124
 *Section:
 *ID: N10644753
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
using namespace std;

struct Complex {
	double real;
	double img;
};

class PlainOldClass {
	public:
		PlainOldClass() : x(-72) {}
		int getX() const { return x;  }
		void setX( int x  )  { this -> x = x;  }
	private:
		int x;
};

class Colour {
	public:
		Colour(const string& name, unsigned r, unsigned g, unsigned b) :name(name), r(r), g(g), b(b) {}

		void display() const {
			cout << name << " (RGB: " << r << ", " << g << ", " << b << ")" << endl;
		}

	private:
		string name;
		unsigned r, g, b;
};

class SpeakerSystem {
	public:
		void vibrateSpeakerCones(unsigned signal) const {
			cout << "Playing: " << signal << "Hz sounds..." << endl;
			cout << "Buzz. buzzy, buzzer, bzap!!" << endl;
		}
};

class Amplifier {
	public:
		void attachSpeakers(SpeakerSystem& spkrs) {
			if (attachedSpeakers) {
				cout << "already have speakers attached!\n";
			}
			else {
				attachedSpeakers = &spkrs;
			}
		}

		void detachSpeakers() {
			attachedSpeakers = nullptr;
		}

		void playMusic() const {
			if(attachedSpeakers) {
				attachedSpeakers -> vibrateSpeakerCones(440);
			} else {
				cout << "No speakers attached" << endl;
			}
		}

	private:
		SpeakerSystem* attachedSpeakers = nullptr;
};

class Person {
	public:
		Person(const string& name) :name(name) {}

		void movesInWith(Person& newRoomate) {
			roomie = &newRoomate;
			newRoomate.roomie = this;
		}

		string getName() const {
			return name;
		}

		string getRoomiesName() const {
			return roomie->getName();
		}

	private:
		Person* roomie;
		string name;
};

int main() {
	int x;
	x = 10;
	cout << "x = " << x << endl;

	int* p;
	p = &x;
	//p = 0x0012fed4;
	cout << "p = " << p << endl;

	cout << "p points to where " << *p << " is stored" << endl;
	cout << "*p contains " << *p << endl;

	*p = -2763;
	cout << "p points to where " << *p << " is stored" << endl;
	cout << "*p now contains " << *p << endl;
	cout << "x now contains " << x << endl;

	int y(13);
	cout << "y contains " << y << endl;
	p = &y;
	cout << "p now points to where  " << *p << "is stored" << endl;
	cout << "*p not contains " << *p << endl;
	*p = 980;
	cout << "p points to where " << *p << " is stored" << endl;
	cout << "*p now contains " << *p << endl;
	cout << "y now contains " << y << endl;

	int* q;
	q = p;
	cout << "q points to where " << *q << " is stored" << endl;
	cout << "*q contains " << *q << endl;

	double d(33.44);
	double* pD(&d);
	*pD = *p;
	*pD = 73.2343;
	*p  = *pD;
	*q  = *p;
	/*
	 *pD  = p;
	 *p   = pD;
	 */

	int joe(24);
	const int sal(19);
	int*  pI;
	pI = &joe;
	*pI = 234;
	//pI = &sal;
	//*pI = 7623;

	const int* pcI;
	//pcI = &joe;
	//*pcI = 234;
	pcI = &sal;
	//*pcI = 7623;

	//int* const cpI;
	//int* const cpI(&joe);
	//int* const cpI(&sal);
	//cpI = &joe;
	//*cpI = 234;
	//cpI = &sal;
	//*cpI = 7623;

	//const int* const cpcI;
	//const int* const cpcI(&joe);
	const int* const cpcI(&sal);
	//pcI = &joe;
	//*cpcI = 234;
	//cpcI = &sal;
	//*cpcI = 7623;

	Complex c = {11.23, 45.67};
	Complex* pC(&c);
	/*
	 *cout << "real: " << (*pC).real <<  <<endl;
	 *cout << "imaginary: " << (*pC).img << endl;
	 */

	cout << "real: " << pC -> real << endl;
	cout << "imaginary: " << pC -> img << endl;

	PlainOldClass poc;
	PlainOldClass* ppoc(&poc);
	cout << ppoc -> getX() << endl;
	ppoc->setX(2837);
	cout << ppoc -> getX() << endl;


	int* pDyn = new int(3);
	*pDyn = 17;

	cout << "The " << *pDyn << " is stored at address " << pDyn << " which is the heap" << endl;

	cout << pDyn << endl;
	delete pDyn;
	cout << pDyn << endl;

	cout << "The 17 might STILL be stored at address " << pDyn<< " even though we deleted pDyn" << endl;;
	cout << "But can we dereference pDyn?  We can try.  This might crash... " << *pDyn << ".  Still here?" << endl;

	pDyn = nullptr;

	double* pDouble(nullptr);

	/*
	 *cout << "Can we dereference nullptr? " << *pDyn << endl;
	 *cout << "Can we dereference nullptr? " << *pDouble << endl;
	 */

	double* pTest = new double(12);
	delete pTest;
	pTest = nullptr;
	delete pTest;

	short* pShrt = new short(5);
	delete pShrt;
	//delete PShrt;

/*
 *
 *    long jumper(12238743);
 *    delete jumper;
 *    long* ptrTolong(&jumper);
 *    delete ptrTolong;
 *    Complex cmplx;
 *    delete cmplx;
 */

	vector<Complex*> compli;
	Complex* tmpPCmplx;
	for (size_t index = 0; index < 3; index++) {
		tmpPCmplx = new Complex;
		tmpPCmplx -> real = index;
		tmpPCmplx -> img = index;
		compli.push_back(tmpPCmplx);
	}

	for (size_t index = 0; index < 3; index++) {
		cout << compli[index] -> real << endl;
		cout << compli[index] -> img << endl;
	}

	for (size_t index = 0; index < 3; index++) {
		delete compli[index];
	}
	compli.clear();


	vector<Colour*> colours;
	string inputName;
	unsigned inputR, inputG, inputB;

	while (cin >> inputName >> inputR >> inputG >> inputB) {
		colours.push_back(new Colour(inputName, inputR, inputG, inputB));
	}

	for (size_t index = 0; index < colours.size(); index++) {
		colours[index] -> display();
	}

	SpeakerSystem speakers;
	Amplifier anAmp;
	cout << "Attaching speakers to amplifer!" << endl;
	anAmp.attachSpeakers(speakers);
	anAmp.playMusic();
	cout << "Detaching speakers from amplifer!" << endl;
	anAmp.detachSpeakers();

	Person joeBob("Joe Bob"), billyJane("Billy Jane");
	joeBob.movesInWith( billyJane  );
	cout << joeBob.getName() << " lives with " << joeBob.getRoomiesName() << endl;
	cout << billyJane.getName() << " lives with " << billyJane.getRoomiesName() << endl;
}
