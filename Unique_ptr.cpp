#include <iostream>

using std::size_t;

template<class T>
class Unique_ptr
{
public:
	Unique_ptr(T* ptr = nullptr) :
		m_ptr(ptr) {}
	
	~Unique_ptr() { delete m_ptr; }
	
	Unique_ptr(const Unique_ptr& obj) = delete;
	Unique_ptr& operator =(const Unique_ptr& obj) = delete;
	operator bool () const { return m_ptr; }
	
	Unique_ptr(Unique_ptr&& obj) :
		m_ptr(obj.m_ptr)
	{ obj.m_ptr = nullptr; }
	
	Unique_ptr& operator =(Unique_ptr&& obj)
	{
		if(&obj != this)
		{
			delete m_ptr;
			m_ptr = obj.m_ptr;
			obj.m_ptr = nullptr;
			return* this;
		}
		return* this;
	}
	
	void swap(Unique_ptr& obj)
	{
		T* temp { std::move(obj) };
		obj = std::move(obj.m_ptr);
		obj.m_ptr = temp;
	}
	
	T release()
	{
		T* ans = m_ptr;
		m_ptr = nullptr;
		return ans;
	}
	
	void reset(T ptr = T())
	{
		T* old = m_ptr;
		m_ptr = ptr;
		if(old != nullptr) delete old;
	}
	
	T* operator ->() const { return m_ptr; }
	T& operator *() const { return *m_ptr; }
	
private:
	T* m_ptr;	
};

int main()
{


	return 0;
}
