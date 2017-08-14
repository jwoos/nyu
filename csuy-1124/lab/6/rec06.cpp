/*
 * Name: Junwoo Shin
 * Recitation: 6
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class PrintedMaterial {
	public:
		PrintedMaterial(unsigned pages) : numberOfPages(pages) {}

		/*
		 *virtual void displayNumPages() const {
		 *    cout << "Pages:" << endl;
		 *    cout << numberOfPages << endl;
		 *}
		 */
		virtual void displayNumPages() const = 0;

	protected:
	private:
		unsigned numberOfPages;
};

void PrintedMaterial::displayNumPages() const {
	cout << numberOfPages << endl;
}

class Magazine : public PrintedMaterial {
	public:
		Magazine(unsigned pages) : PrintedMaterial(pages) {}

		void displayNumPages() const{
			cout << "Magazine" << endl;
			PrintedMaterial::displayNumPages();
		}
	protected:
	private:
};

class Book : public PrintedMaterial {
	public:
		Book(unsigned pages) : PrintedMaterial(pages) {}
	protected:
	private:
};

class TextBook : public Book {
	public:
		TextBook(unsigned pages, unsigned indexPage) : Book(pages), numOfIndexPage(indexPage) {}

		void displayNumPages() const {
			cout << "TextBook" << endl;
			PrintedMaterial::displayNumPages();
			cout << "index pages: " << endl;
			cout << numOfIndexPage << endl;
		}
	protected:
	private:
		unsigned numOfIndexPage;
};

class Novel : public Book {
	public:
		Novel(unsigned pages) : Book(pages) {}

		void displayNumPages() const {
			cout << "Novel" << endl;
			PrintedMaterial::displayNumPages();
		}
	protected:
	private:
};

void newLine() {
	cout << endl;
}

void displayNumberOfPages(const PrintedMaterial& pm) {
	pm.displayNumPages();
}

int main() {
	TextBook t(100, 5);
	Novel n(200);
	Magazine m(200);

	vector<PrintedMaterial*> printedMaterialPointers;
	printedMaterialPointers.push_back(&t);
	printedMaterialPointers.push_back(&n);
	printedMaterialPointers.push_back(&m);

	for (size_t i = 0; i < printedMaterialPointers.size(); i++) {
		printedMaterialPointers[i] -> displayNumPages();
	}
}
