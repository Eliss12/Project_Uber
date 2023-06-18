#pragma once
#include <iostream>

// Credits: https://github.com/stoychoX/Object-oriented_programming_FMI_2021-2022/blob/main/Sem.%2010/Practicum/Vector.hpp

template <typename T>
class Vector
{
	T* data;
	size_t size;
	size_t capacity;

	void copyFrom(const Vector& other);
	void free();
	void moveFrom(Vector&& other);

	void resize();

public:
	Vector();

	Vector(const Vector<T>& other);
	Vector(Vector<T>&& other);

	Vector<T>& operator=(const Vector<T>& other);
	Vector<T>& operator=(Vector<T>&& other);

	void pushBack(const T& other);
	void pushBack(T&& other);
	void pushAt(const T& other, size_t index);
	void pushAt(T&& other, size_t index);
	T& popBack();
	T& popAt(size_t index);

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	bool empty() const;
	void clear();
	size_t getSize() const;
	~Vector();
};

template <typename T>
Vector<T>::Vector()
{
	capacity = 4;
	size = 0;
	data = new T[capacity];
}

template <typename T>
void Vector<T>::copyFrom(const Vector<T>& other) {
	size = other.size;
	capacity = other.capacity;
	data = new T[capacity];

	for (size_t i = 0; i < size; i++)
		data[i] = other.data[i];
}

template <typename T>
void Vector<T>::free()
{
	delete[] data;
	data = nullptr;
	capacity = size = 0;
}

template <typename T>
void Vector<T>::moveFrom(Vector&& other)
{
	data = other.data;
	other.data = nullptr;

	size = other.size;
	capacity = other.capacity;
	other.capacity = other.size = 0;
}

template <typename T>
void Vector<T>::resize()
{
	T* resizedData = new T[capacity * 2];
	for (size_t i = 0; i < size; i++)
	{
		resizedData[i] = data[i];
	}
	capacity *= 2;
	delete[] data;
	data = resizedData;
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	copyFrom(other);
}

template <typename T>
Vector<T>::Vector(Vector<T>&& other)
{
	moveFrom(std::move(other));
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template <typename T>
Vector<T>::~Vector()
{
	free();
}

template <typename T>
size_t Vector<T>::getSize() const
{
	return size;
}

template <typename T>
void Vector<T>::pushBack(const T& other)
{
	if (size == capacity)
		resize();

	data[size++] = other;
}


template <typename T>
void Vector<T>::pushBack(T&& other)
{
	if (size == capacity)
		resize();

	data[size++] = std::move(other);
}

template <typename T>
void Vector<T>::pushAt(const T& other, const size_t index)
{
	if (size == capacity)
		resize();

	for (size_t i = size; i > index; i--)
		data[i] = data[i - 1];

	data[index] = other;
	size++;
}

template <typename T>
void Vector<T>::pushAt(T&& other, const size_t index)
{
	if (size == capacity)
		resize();

	for (size_t i = size; i > index; i--)
		data[i] = data[i - 1];

	data[index] = std::move(other);
	size++;
}

template <typename T>
T& Vector<T>::popBack()
{
	if (empty())
		throw std::logic_error("Vector is empty");

	return data[--size];
}

template <typename T>
T& Vector<T>::popAt(size_t index)
{
	if (index < 0 || index >= size)
		throw std::out_of_range("Invalid index");

	T temp = data[index];
	for (size_t i = index; i < size - 1; i++)
		data[i] = data[i + 1];

	size--;
	return temp;
}

template <typename T>
T& Vector<T>::operator[](const size_t index)
{
	if (index < 0 || index >= size)
		throw std::out_of_range("Invalid index");

	return data[index];
}

template <typename T>
const T& Vector<T>::operator[](const size_t index) const
{
	if (index < 0 || index >= size)
		throw std::out_of_range("Invalid index");

	return data[index];
}

template <typename T>
bool Vector<T>::empty() const
{
	return size == 0;
}

template <typename T>
void Vector<T>::clear()
{
	delete[] data;
	capacity = 4;
	data = new T[capacity];
	size = 0;
}

