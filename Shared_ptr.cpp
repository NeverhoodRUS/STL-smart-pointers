#include <iostream>

template<class T>
class Shared_ptr
{
public:
	Shared_ptr() :
		m_ptr(nullptr), counter(nullptr) {}
		
	Shared_ptr(T* ptr) :
		m_ptr(ptr), counter(size_t(1)) {}
		
	Shared_ptr(Shared_ptr<T>& other) :
		m_ptr(other.m_ptr), counter(other.counter) 
	{ 
		++counter; 
		++other.counter;
	}
	
	~Shared_ptr()
	{
		reset();
	}
		
	Shared_ptr& operator =(Shared_ptr& other)
	{
		if(this != &other) 
		{
			reset();
			m_ptr = other.m_ptr;
			counter = other.counter;
			++counter;
			++other.counter;
		}
		return* this;
	}
	
	size_t use_count() const { return counter; }
	
	bool unique() const 
	{ 
		if(*counter == 1) return false;
		else return true; 
	}
	
	void reset()
	{
		if(counter > 0)
			--counter;
		else if(counter == 0)
			delete m_ptr;
	}
	
private:
	T* m_ptr;
	size_t* counter;	
};

int main()
{


	return 0;
}
