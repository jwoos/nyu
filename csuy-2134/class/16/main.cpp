#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
class LList;

template <typename T>
class LListNode;

template <typename T>
class LListItr;

template <typename T>
class LList {
	private:
		LListNode<T>* head;
		LListNode<T>* tail;
		int numOfElements;
	public:
		LList() {
			numOfElements = 0;
			head = new LListNode<T>;
			head -> next = tail = new LListNode<T>(T(), head);
		}

		LList(const LList<T>& rhs) {
			numOfElements = 0;
			head = new LListNode<T>;
			head -> next = tail = new LListNode<T>(T(), head);

			*this = rhs;
		}

		~LList() {
			clear();
			delete head;
			delete tail;
		}

		LList<T>& operator=(const LList<T>& rhs) {
			if (this == &rhs) {
				return *this;
			}

			clear();

			for (LListItr<T> i = rhs.begin(); i != rhs.end(); i++) {
				push_back(*i);
			}

			return *this;
		}

		// implicit coercion via constructor
		LListItr<T> begin() const {
			return head -> next;
		}

		LListItr<T> end() const {
			return tail;
		}

		void insertAfter(LListItr<T> itr, const T& item) {
			if (itr.ptr == tail) {
				return;
			}

			insertBefore(++itr, item);
		}

		void insertBefore(LListItr<T> itr, const T& item) {
			if (itr.ptr == head) {
				return;
			}

			numOfElements++;

			/*
			 *LListNode<T>* temp = itr.ptr -> prev;
			 *temp -> next = new LListNode<T>(item);
			 *temp -> next -> next = itr.ptr;
			 *itr.ptr -> prev = temp -> next;
			 *temp -> next -> prev = temp;
			 */
			itr.ptr -> prev = itr.ptr -> prev -> next = new LListNode<T>(item, itr.ptr -> prev, itr.ptr);
		}

		T remove(LListItr<T> itr) {
			if (itr.ptr == head || itr.ptr == tail) {
				return T();
			}

			T retVal = itr.ptr -> data;
			LListNode<T>* temp = itr.ptr;

			temp -> prev -> next = temp -> next;
			temp -> next -> prev = temp -> prev;

			delete temp;
			itr.ptr = tail;

			numOfElements--;

			return retVal;
		}

		int size() const {
			return numOfElements;
		}

		void push_back(const T& item) {
			insertBefore(tail, item);
		}

		void push_front(const T& item)  {
			insertAfter(head, item);
		}

		T pop_front() {
			return remove(head -> next);
		}

		T pop_back() {
			return remove(tail -> prev);
		}

		bool isEmpty() const {
			return head -> next == tail;
		}

		void clear() {
			while (!isEmpty()) {
				pop_front();
			}
		}

		void insertSorted(const T& item) {
			LListNode<T>* temp = head -> next;

			while (temp != tail && temp -> data < item) {
				temp = temp -> next;
			}
			insertBefore(temp, item);
		}

		void removeDuplicates() {
			for (LListItr<T> i = begin(); i != end(); i++) {
				LListItr<T> j = i;

				for (j++; j != end(); j++) {
					if (*i == *j) {
						LListItr<T> temp = j;
						j--;
						remove(temp);
					}
				}
			}
		}

		void splitList(LList<T>& lhs, LList<T>& rhs) {
			if (this == &lhs || this == &rhs) {
				return;
			}

			lhs.clear();
			rhs.clear();

			LListItr<T> temp = head -> next;

			for (int i = 0; i < numOfElements; i++) {
				if (i < numOfElements / 2) {
					lhs.push_back(*temp++);
				} else {
					rhs.push_back(*temp++);
				}
			}
		}

		LList<T> cutInHalf() {
			LList<T> temp;
			LListItr<T> left = head -> next;
			LListItr<T> right = tail -> prev;

			while (left != right && right -> next != left.ptr) {
				right --;
				left++;
				temp.push_front(pop_back());
			}

			return temp;
		}

		void mergeSorted(LList<T>& rhs) {
			if (this == &rhs) {
				return;
			}

			LListItr<T> left = begin();
			LListItr<T> right = end();

			while (left != end() && right!= rhs.end()) {
				if (*left < *right) {
					left++;
				} else {
					right++;
					numOfElements++;
					LListNode<T>* temp = right.ptr -> prev -> prev;
					temp -> next = right.ptr;
					right.ptr -> prev -> prev = left.ptr -> prev;
					left.ptr -> prev -> next = left.ptr -> prev = right.ptr -> prev;
					right.ptr -> prev = temp;
					left.ptr -> prev -> next = left.ptr;
				}
			}

			if (right != rhs.end()) {
				numOfElements += rhs.numOfElements;
				right.ptr -> prev = tail -> prev;
				tail -> prev -> next = right.ptr;
				rhs.tail -> prev -> next = tail;
				tail -> prev = rhs.tail -> prev;
				rhs.head -> next = rhs.tail;
				rhs.tail -> prev = rhs.head;
			}
		}

		void mergeSort(LList<T>& ls) {
			if (ls.size() < 2) {
				return;
			}

			LList<T> right = cutInHalf();

			mergeSort(ls);
			mergeSort(right);

			ls.mergeSorted(right);
		}
};

template <typename T>
class LListItr {
	private:
		LListNode<T>* ptr;
	public:
		LListItr(LListNode<T>* newPtr = nullptr) : ptr(newPtr) {}

		bool operator==(const LListItr<T>& rhs) {
			return ptr == rhs.ptr;
		}

		bool operator!=(const LListItr<T>& rhs) {
			return ptr != rhs.ptr;
		}

		T operator*() const {
			return ptr -> data;
		}

		T& operator*() {
			return ptr -> data;
		}

		LListItr<T>& operator++() {
			if (ptr -> next != nullptr) {
				ptr = ptr -> next;
			}

			return *this;
		}

		LListItr<T>& operator--() {
			if (ptr -> prev != nullptr) {
				ptr = ptr -> prev;
			}

			return *this;
		}

		LListItr<T> operator++(int) {
			LListItr<T> temp = *this;

			if (ptr -> next != nullptr) {
				ptr = ptr -> next;
			}

			return temp;
		}

		LListItr<T> operator--(int) {
			LListItr<T> temp = *this;

			if (ptr -> prev != nullptr) {
				ptr = ptr -> prev;
			}

			return temp;
		}

		friend class LList<T>;
};

template <typename T>
class LListNode {
	private:
		LListNode<T>* prev;
		LListNode<T>* next;
		T data;

	public:
		LListNode(const T& newData = T(), LListNode<T>* newPrev = nullptr, LListNode<T>* newNext = nullptr) : data(newData), next(newNext), prev(newPrev) {}

		friend class LList<T>;
		friend class LListItr<T>;
};

int main() {
	srand(time(nullptr));

}
