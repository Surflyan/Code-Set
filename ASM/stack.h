#pragma once
#include <algorithm>
#include "myTools.h"

template <typename T>
class stack
{
public:
	stack(int initialCapacity = 8);
	stack(const stack & s)
	{
		capacity = s.capacity;
		arr = new T[capacity];
		_top = s._top;
		copy(s.begin(), s.end(), begin());
	}
	stack(stack && s)
	{
		arr = s.arr;
		capacity = s.capacity;
		_top = s._top;
		s.arr = nullptr;
	}
	~stack();

	bool empty() const { return _top == 0; }
	bool full() const { return _top == capacity; }
	int size() const { return _top; }

	T & top() { return arr[_top - 1]; }
	void pop(T & theElement) { theElement = arr[--_top]; arr[_top].~T(); }
	void pop() { arr[--_top].~T(); }
	void push(const T& theElement) 
	{ 
		if (full())
		{
			arr = change_length_of_1Darray(arr, capacity, 2 * capacity);
			capacity *= 2;
		}
		arr[_top++] = theElement;
	}
	
	T * begin() { return arr; }
	T * end() { return arr + _top; }

	stack & operator=(stack && s)
	{
		if (this == &s)
			return *this;
		delete[] arr;
		arr = s.arr;
		capacity = s.capacity;
		_top = s._top;
		s.arr = nullptr;
		return *this;
	}
	stack & operator=(const stack & s)
	{
		if (this == &s)
			return *this;
		delete[] arr;
		arr = new T[s.capacity];
		_top = s._top;
		capacity = s.capacity;
		for (int i = 0; i != s._top; i++)
			arr[i] = s.arr[i];
		return *this;
	}
private:
	T * arr;
	int _top;
	int capacity;
};

template<typename T>
inline stack<T>::stack(int initialCapacity)
{
	capacity = initialCapacity;
	_top = 0;
	arr = new T[capacity];
}

template<typename T>
inline stack<T>::~stack()
{
	delete[] arr;
}
