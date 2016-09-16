#include <cstdlib>

template <typename T>
class DynArray {
	public:
		DynArray();

		DynArray(const DynArray& rhs);

		DynArray& operator=(const DynArray& rhs);

		virtual ~DynArray();

		void push_back(T newdata);

		void pop_back();

		void resize(size_t n);

		T operator[](size_t index) const;

		T& operator[](size_t index);

		size_t size() const;

		size_t capacity() const;
	private:
		size_t _size;

		size_t _capacity;

		bool bracketsUsed;

		T* data;
};
