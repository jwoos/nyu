/*
 *
 * Junwoo Shin
 * Rec 07
 *
 *
 *
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Instrument {
	public:
		Instrument() {}

		virtual void makeSound() const = 0;

		virtual void play() const = 0;
	private:
};

class Brass : public Instrument {
	public:
		Brass(unsigned mouthpiece) : mouthpiece(mouthpiece) {
			if (!(mouthpiece == 12) || !(mouthpiece == 9) || !(mouthpiece == 4)) {
				cout << "Invalid size" << endl;
			}
		}

		void makeSound() const {
			cout << "To make a sound... blow on a mouthpiecec of size " << mouthpiece << endl;
		}
	private:
		int mouthpiece;
};

class Strings : public Instrument {
	public:
		Strings(unsigned pitch) : pitch(pitch) {}

		void makeSound() const {
			cout << "To make a sound... bow a string with pitch " << pitch << endl;
		}
	private:
		unsigned pitch;
};

class Percussion : public Instrument {
	public:
		void makeSound() const {
			cout << "To make a sound... hit me!" << endl;
		}
	private:
};

class Trombone : public Brass {
	public:
		Trombone(unsigned mouthpiece) : Brass(mouthpiece) {}

		void play() const {
			cout << "Blat";
		}
	private:
};


class Trumpet : public Brass {
	public:
		Trumpet(unsigned mouthpiece) : Brass(mouthpiece) {}

		void play() const {
			cout << "Toot";
		}
	private:
};

class Violin : public Strings {
	public:
		Violin(unsigned pitch) : Strings(pitch) {}

		void play() const {
			cout << "Screech";
		}
	private:
};

class Cello : public Strings {
	public:
		Cello(unsigned  pitch) : Strings(pitch) {}

		void play() const {
			cout << "Squawk";
		}
	private:
};


class Drum : public Percussion {
	public:
		Drum() {}

		void play() const {
			cout << "Boom";
		}
	private:
};

class Cymbal : public Percussion {
	public:
		Cymbal() {}

		void play() const {
			cout << "Crash";
		}
	private:
};

class MILL {
	public:
		MILL() {}

		void receiveInstr(Instrument& instrument) {
			instrument.makeSound();

			for (size_t i = 0; i < instruments.size(); i++) {
				if (!instruments[i]) {
					instruments[i] = &instrument;
					return;
				}
			}

			instruments.push_back(&instrument);
		}

		void dailyTestPlay() const {
			for (Instrument* instrPtr : instruments) {
				if (instrPtr) {
					instrPtr -> makeSound();
				}
			}
		}

		Instrument* loanOut() {
			for (size_t i = 0; i < instruments.size(); i++) {
				if (instruments[i]) {
					Instrument* tmp = instruments[i];
					instruments[i] = nullptr;
					return tmp;
				}
			}

			return nullptr;
		}
	private:
		vector<Instrument*> instruments;
};

class Musician {
	public:
		Musician() : instr(nullptr) {}

		void acceptInstr(Instrument& i) {
			instr = &i;
		}

		Instrument* giveBackInstr() {
			Instrument* tmp(instr);
			instr = nullptr;
			return tmp;
		}

		void testPlay() const {
			if (instr) {
				instr -> makeSound();
			} else {
				cerr << "have no instr" << endl;
			}
		}

		void play() const {
			if (instr) {
				instr -> play();
			}
		}
	private:
		Instrument* instr;
};

class Orch {
	public:
		Orch () : musicians(25, nullptr) {}

		void addPlayer(Musician& musician) {
			for (size_t i = 0; i < musicians.size(); i++) {
				if (!musicians[i]) {
					musicians[i] = &musician;
					return;
				}
			}
		}

		void play() {
			for (Musician*& musicianPtr : musicians) {
				if (musicianPtr) {
					musicianPtr -> play();
				}
			}
			cout << endl;
		}
	private:
		vector<Musician*> musicians;
};

int main() {
/*
 *    PART ONE
 *
 *    cout << "Define some instruments ----------------------------------------" << endl;
 *    Drum drum;
 *    Cello cello(673);
 *    Cymbal cymbal;
 *    Trombone tbone(4);
 *    Trumpet trpt(12);
 *    Violin violin(567);
 *    cout << "Define the MILL ------------------------------------------------" << endl;
 *    MILL mill;
 *    cout << "Put the instruments into the MILL ------------------------------" << endl;
 *    mill.receiveInstr(trpt);
 *    mill.receiveInstr(violin);
 *    mill.receiveInstr(tbone);
 *    mill.receiveInstr(drum);
 *    mill.receiveInstr(cello);
 *    mill.receiveInstr(cymbal);
 *    cout << "Daily test -----------------------------------------------------" << endl;
 *    cout << "dailyTestPlay()" << endl;
 *    mill.dailyTestPlay();
 *    cout << "Define some Musicians-------------------------------------------" << endl;
 *    Musician j;
 *    Musician jj;
 *    Musician q;
 *    cout << "TESTING: q.acceptInstr( *mill.loanOut() );-----------------------" << endl;
 *    q.testPlay();
 *    q.acceptInstr(*mill.loanOut());
 *    q.testPlay();
 *    cout << "dailyTestPlay()" << endl;
 *    mill.dailyTestPlay();
 *    q.testPlay();
 *    cout << endl;
 *    mill.receiveInstr(*q.giveBackInstr());
 *    j.acceptInstr(*mill.loanOut());
 *    q.acceptInstr(*mill.loanOut());
 *    q.testPlay();
 *    j.testPlay();
 *    cout << "dailyTestPlay()" << endl;
 *    mill.dailyTestPlay();
 *    cout << "TESTING: mill.receiveInstr(*q.giveBackInstr()); -------------" << endl;
 *    mill.receiveInstr(*q.giveBackInstr());
 *    cout << "TESTING: mill.receiveInstr( *j.giveBackInstr() ); -------------" << endl;
 *    mill.receiveInstr(*j.giveBackInstr());
 *    cout << "dailyTestPlay()" << endl;
 *    mill.dailyTestPlay();
 */

	//PART TWO

	Drum drum;
	Cello cello(673);
	Cymbal cymbal;
	Trombone tbone( 4 );
	Trumpet trpt( 12 ) ;
	Violin violin( 567 ) ;
	MILL mill;
	mill.receiveInstr(trpt);
	mill.receiveInstr(violin);
	mill.receiveInstr(tbone);
	mill.receiveInstr(drum);
	mill.receiveInstr(cello);
	mill.receiveInstr(cymbal);
	Musician bob;
	Musician sue;
	Musician mary;
	Musician ralph;
	Musician jody;
	Musician morgan;
	Orch orch;
	orch.addPlayer(bob);
	cout << "orch performs" << endl;
	orch.play();
	sue.acceptInstr(*mill.loanOut());
	orch.addPlayer(sue);
	ralph.acceptInstr(*mill.loanOut());
	mary.acceptInstr(*mill.loanOut());
	orch.addPlayer(mary);
	mill.receiveInstr(*ralph.giveBackInstr());
	jody.acceptInstr(*mill.loanOut());
	orch.addPlayer(jody);
	morgan.acceptInstr(*mill.loanOut());
	cout << "orch performs" << endl;
	orch.play();
	orch.addPlayer(ralph);
	cout << "orch performs" << endl;
	orch.play();
	bob.acceptInstr(*mill.loanOut());
	ralph.acceptInstr(*mill.loanOut());
	cout << "orch performs" << endl;
	orch.play();
	orch.addPlayer(morgan);
	cout << "orch performs" << endl;
	orch.play();
}
