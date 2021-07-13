#pragma once

template <class T>
class myVector
{
public:
	myVector();
	myVector(const int);
	myVector(const T&, const int);
	~myVector();

	void reserve(const int);
	void push_back(const T&);
	void pop_back();
	void insert(const T&, const int);
	void clear();
	int getSize();
	int getCapacity();
	T* getVector();
	T& at(int);
	T& operator[] (const int);
	T& operator[] (const int) const;

private:
	T *vector;
	int size;
	int capacity;

	void free();
	void realloc();
};


template <class T>
myVector<T>::myVector()
{
	this->capacity = 1;
	this->size = 0;
	this->vector = new T;
}

template <class T>
myVector<T>::myVector(const int startCapacity)
{
	int temp = startCapacity;
	if (temp <= 0)
		temp = 1;
	this->capacity = temp;
	this->size = 0;
	this->vector = new T[this->capacity];
}

template <class T>
myVector<T>::myVector(const T& pattern, const int startCapacity)
{
	int temp = startCapacity;
	if (temp <= 0)
		temp = 1;
	this->capacity = temp;
	this->size = 0;
	this->vector = new T[this->capacity];
	for (int i = 0; i < this->capacity; i++)
		this->vector[i] = pattern;
}

template <class T>
myVector<T>::~myVector()
{
	this->free();
}

template <class T>
void myVector<T>::reserve(const int newSize)
{
	if (newSize > size)
	{
		this->capacity = newSize;
		T *newVector = new T[this->capacity];
		for (int i = 0; i < size; i++)
			newVector[i] = this->vector[i];
		this->free();
		this->vector = newVector;
	}
}

template <class T>
void myVector<T>::pop_back()
{
	if (this->size > 0)
	{
		this->vector[this->size - 1] = 0;
		this->size--;
	}
}

template <class T>
void myVector<T>::clear()
{
	for (int i = 0; i < this->size; i++)
		this->vector[i] = 0;
	this->size = 0;
}

template <class T>
void myVector<T>::push_back(const T& newElement)
{
	if (this->size == this->capacity)
		this->realloc();
	this->vector[size] = newElement;
	this->size++;
}

template <class T>
int myVector<T>::getSize()
{
	return this->size;
}

template <class T>
int myVector<T>::getCapacity()
{
	return this->capacity;
}

template <class T>
T* myVector<T>::getVector()
{
	return this->vector;
}

template <class T>
T& myVector<T>::at(int index)
{
	if (index < this->size)
		return this->vector[index];
	else;
}

template <class T>
T& myVector<T>::operator[](const int index)
{
	return this->vector[index];
}

template <class T>
T& myVector<T>::operator[](const int index) const
{
	return this->vector[index];
}

template <class T>
void myVector<T>::insert(const T& newElement, const int index)
{
	if (this->size == this->capacity)
	{
		this->realloc();
	}
	for (int i = this->size - 1; i >= index; i--)
	{
		this->vector[i + 1] = this->vector[i];
	}
	this->vector[index] = newElement;
	this->size++;
}

template <class T>
void myVector<T>::free()
{
	if (this->vector != 0)
	{
		delete[] this->vector;
		this->vector = 0;
	}
}

template <class T>
void myVector<T>::realloc()
{
	if (capacity == size)
	{
		this->capacity = 2 * this->size;
		T *newVector = new T[this->capacity];
		for (int i = 0; i < size; i++)
			newVector[i] = this->vector[i];
		this->free();
		this->vector = newVector;
	}
}