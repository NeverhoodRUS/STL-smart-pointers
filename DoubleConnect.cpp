//Реализация двусвязного не кольцевого, не ассоциативного списка

#include <iostream>
#include <exception>

template<class T>
class DoubleList
{
public:
	DoubleList() :
		_size(0), _head(nullptr), _tail(nullptr) {}
	~DoubleList() { clear(); }
	
	void push_back(const T&);
	void push_front(const T&);
	void insert(const T&, const size_t);
	void remove_at(const size_t);
	void pop_front();
	void pop_back();
	void clear();
	void show();
	
	const size_t size();
	
	DoubleList& operator=(const DoubleList&);
	
private:
	
	template<class T2>
	class Node
	{
	public:
		Node* _pnext;	//указатель на след эл-т (в сторону _tail)
		Node* _pprev;	//указатель на предыд эл-т (в сторону _head)
		T2 _data;
		
		Node(T2 data = T2(), Node* pnext = nullptr, Node* pprev = nullptr) :
			_data(data), _pnext(pnext), _pprev(pprev) {}
	};
	
	Node<T>* _tail;		//указатель на хвост списка
	Node<T>* _head;		//указатель на голову списка
	size_t _size;		//размер списка
};

int main()
{
	DoubleList<int> a;
	
	for(int i = 0; i < 10; ++i)
		a.push_back(i);
		
	a.clear();
	a.show();
	
    return 0;
}

template<class T>
void DoubleList<T>::remove_at(const size_t index)
{
	if(index < 0 || index > _size)
		return;
	if(index < _size / 2)
	{
		if(index == 0)
			pop_front();
		else
		{
			size_t counter = 0;
			Node<T>* it = _head;
			while(counter < index)
			{
				it = it->_pnext;
				++counter;
			}
			it->_pnext->_pprev = it->_pprev;
			it->_pprev->_pnext = it->_pnext;
			delete it;
			--_size;
		}
	}
	else
	{
		if(index == _size)
			pop_back();
		else
		{
			size_t counter = _size - 1;
			Node<T>* it = _tail;
			while(counter > index)
			{
				it = it->_pprev;
				--counter;
			}
			it->_pnext->_pprev = it->_pprev;
			it->_pprev->_pnext = it->_pnext;
			delete it;
			--_size;
		}
	}
}

template<class T>
void DoubleList<T>::clear()
{
	while(_size)
		this->pop_front();
}

template<class T>
void DoubleList<T>::pop_back()
{
	if(_tail != nullptr)
	{
		Node<T>* temp = _tail;
		_tail->_pprev->_pnext = nullptr;
		_tail = _tail->_pprev;
		delete temp;
		--_size;
	}
	else
		return;
}

template<class T>
void DoubleList<T>::pop_front()
{
    if(_head != nullptr)
    {
        Node<T>* temp = _head;
        if(_head->_pnext) {
            _head->_pnext->_pprev = nullptr;
            _head = _head->_pnext;
        }
        else 
			_head = nullptr;
			
        delete temp;
        --_size;
    }
    else
        return;
}

template<class T>
void DoubleList<T>::insert(const T& el, const size_t index)
{
	if(index > _size || index < 0)
		return;
		
	else if(index == 0)
		push_front(el);
		
	else if(index == _size)
		push_back(el);
		
	else
	{
		Node<T>* temp = new Node<T>;
		temp->_data = el;
		
		if(index < _size / 2)
		{
			Node<T>* it = _head;
			size_t counter = 1;
			while(counter < index)
			{
				it = it->_pnext;
				++counter;
			}
			temp->_pprev = it->_pprev;
			temp->_pnext = it;
			it->_pprev->_pnext = temp;
			it->_pprev = temp;
		}
		else
		{
			Node<T>* it = _tail;
			size_t counter = _size;
			while(counter > index)
			{
				it = it->_pprev;
				--counter;
			}
			temp->_pnext = it->_pnext;
			temp->_pprev = it;
			it->_pnext->_pprev = temp;
			it->_pnext = temp;
		}
	}
	++_size;
}

template<class T>
void DoubleList<T>::show()
{
	Node<T>* it = _head;
	while(it != nullptr)
	{
		std::cout << it->_data << " ";
		it = it->_pnext;
	}
}

template<class T>
void DoubleList<T>::push_front(const T& el)
{
	Node<T>* temp = new Node<T>;
	temp->_data = el;
	temp->_pnext = _head;
	
	if(_head != nullptr)
	{
		_head->_pprev = temp;
		_head = temp;
	}
	else if(_size == 0)
		_head = _tail = temp;
		
	else
		_head = temp;
		
	++_size;
}

template<class T>
void DoubleList<T>::push_back(const T& el)
{
	Node<T>* temp = new Node<T>;
	temp->_data = el;
	temp->_pprev = _tail;
	
	if(_tail != nullptr)		//если уже есть последний элемент
	{
		_tail->_pnext = temp;
		_tail = temp;
	}
	else if(_size == 0)			//если элементов нет
		_head = _tail = temp;
		
	else
		_tail = temp;
		
	++_size;
}

template<class T>
const size_t DoubleList<T>::size()
{
	return this->_size;
}

template<class T>
DoubleList<T>& DoubleList<T>::operator=(const DoubleList& other)
{
	if(this != &other)
	{
		this->clear();
		Node<T>* newList = other._head;
		while(newList != nullptr)
		{
			push_back(newList->_data);
			newList = newList->_pprev;
		}
		return*this;
	}
	return*this;
}








