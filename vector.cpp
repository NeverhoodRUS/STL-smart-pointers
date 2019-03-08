#include <iostream>
#include <stdexcept>

template<class T>
class mvector
{
public:
	mvector() :
		marr(nullptr), size(0), capacity(2 * size) {}
	mvector(size_t);
	mvector(size_t , const T& = T());
	~mvector() { clear(); }
	
	void clear();
	void push_back(const T&);
	void pop_back();
	void resize(size_t);
	size_t capacit() const { return capacity; }
	size_t siz() const { return size; }
	T& at(size_t index);
	T& front() { return at(0); };
	T& back() { return at(size - 1); }
	
	
	T& operator [](size_t index) { return marr[index]; }
	
private:
	T* marr;
	size_t size;
	size_t capacity;
};

int main()
{
	return 0;
}

template<class T>
void mvector<T>::clear()
{
	delete[] marr;
	marr = nullptr;
	size = 0;
	capacity = 0;
}

template<class T>
mvector<T>::mvector(size_t newsize, const T& val) :
	size(newsize), capacity(2 * newsize)
{
	marr = new T[capacity];
	for(size_t i = 0; i < newsize; ++i) {
		marr[i] = val;
	}
}

template<class T>
mvector<T>::mvector(size_t newsize) :
	size(newsize), capacity(2 * newsize)
{
	marr = new T[capacity];
	for(size_t i = 0; i < newsize; ++i) {
		marr[i] = 0;
	}
}

template<class T>
void mvector<T>::push_back(const T& el)
{
	if(size == capacity)
	{
		resize(size + 1);
		--size;
	}
	marr[size] = el;
	++size;
}

template<class T>
void mvector<T>::pop_back()
{
	if(size > 0)
		--size;
}

template<class T>
void mvector<T>::resize(size_t newsize)
{
	size_t correct_size = std::min(newsize, size);
	T* buffer = new T[correct_size];
	
	for(size_t i = 0; i < correct_size; ++i) {
		buffer[i] = marr[i];
	}
	
	delete[] marr;
	size = correct_size;
	capacity = correct_size * 2;
	marr = new T[size];
	
	for(size_t i = 0; i < correct_size; ++i) {
		marr[i] = buffer[i];
	}
	delete[] buffer;
}

template<class T>
T& mvector<T>::at(size_t index)
{
	if(index > size)
		throw std::out_of_range("Vector subscript out of range.");
	else
		return marr[index];
}
