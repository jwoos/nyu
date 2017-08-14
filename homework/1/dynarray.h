#include <cstdlib>

template <typename T>
class DynArray {
	public:
		DynArray();

		DynArray(const DynArray&);

		DynArray& operator=(const DynArray&);

		virtual ~DynArray();

		void push_back(T);

		void pop_back();

		void resize(size_t);

		T operator[](size_t) const;

		T& operator[](size_t);

		size_t size() const;

		size_t capacity() const;
	private:
		size_t _size;

		size_t _capacity;

		bool bracketsUsed;

		T* data;
};

#include "dynarray.cpp"
