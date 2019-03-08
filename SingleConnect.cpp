#include <iostream>

template<class T>
class List
{
public:
	List() :
		_head(nullptr), _size(0) {}
	~List () { clear(); }
	
	void clear();
	void push_back(const T&);
	void push_front(const T&);
	void pop_front();
	void pop_back();
	void show();
	void remove_at(const size_t);
	void insert(const T&, const size_t);
	size_t size() { return this->_size; }
	
	T& operator[](const size_t);
	
private:
	
	template<class T2>
	class Node
	{
	public:
		Node* _pnext;
		T2 _data;
		
		Node(T2 data = T(), Node* pnext = nullptr) :
			_data(data), _pnext(pnext) {}
	};
	
	Node<T>* _head;
	size_t _size;
};

int main()
{
	List<int> a;
	a.push_back(0);
	std::cout << a[0] << std::endl;
	a.push_back(1);
	a.push_back(2);
	a.pop_back();
	a.show();
	
    return 0;
}

template<class T>
T& List<T>::operator[](const size_t index)
{
	if(index >= 0 && index < _size)
	{
		size_t counter = 0;
		Node<T>*current = _head;
		
		while(current != nullptr)
		{
			if(counter == index)
				return current->_data;
			current = current->_pnext;
			++counter;
		}
	}
}

template<class T>
void List<T>::push_front(const T& el)
{
	_head = new Node<T>(el, _head);
	++_size;
}

template<class T>
void List<T>::insert(const T& el, const size_t index)
{
	if(index > 0 && index < _size)
	{
		Node<T>* current = _head;
		for(size_t i = 0; i < index - 1; ++i)
			current = current->_pnext;
		current->_pnext = new Node<T>(el, current->_pnext);
		++_size;
	}
	else if(index == 0) {
		push_front(el);
	}
}

template<class T>
void List<T>::clear()
{
	while(_size)
		pop_front();
}

template<class T>
void List<T>::pop_back()
{
	remove_at(_size - 1);
}

template<class T>
void List<T>::remove_at(const size_t _index)
{
	if(_index > 0 && _index < _size)
	{
		Node<T>* previous = _head;
		for(size_t i = 0; i < _index - 1; ++i)
			previous = previous->_pnext;
		Node<T>* toDelete = previous->_pnext;
		previous->_pnext = toDelete->_pnext;
		delete toDelete;
		--_size;
	}
	else if(_index == 0)
		pop_front();
}

template<class T>
void List<T>::show()
{
	if(_size > 0)
	{
		size_t counter = 0;
		Node<T>* current = _head;
		do
		{
			std::cout << current->_data << " ";
			current = current->_pnext;
			++counter;
		} while(current != nullptr);
	}	
}

template<class T>
void List<T>::pop_front()
{
	if(_size > 0)
	{
		Node<T>* temp;
		temp = _head;
		_head = _head->_pnext;
		delete temp;
		--_size;
	}
}

template<class T>
void List<T>::push_back(const T& el)
{
	if(_head != nullptr)
	{
		Node<T>* current = this->_head;
		while(current->_pnext != nullptr)
			current = current->_pnext;
		current->_pnext = new Node<T>(el);
	}
	else {
		_head = new Node<T>(el);
	}
	++_size;
}
























