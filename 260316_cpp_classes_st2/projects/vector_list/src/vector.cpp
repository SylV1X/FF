#include "vector.hpp"

#include <iostream>

using ssY::Vector;

template<typename T>
const std::size_t Vector<T>::START_CAPACITY = 10;

template<typename T>
Vector<T>::Vector() {
	capacity = START_CAPACITY;
	arr = new T[capacity];
	size = 0;
}

template<typename T>
Vector<T>::~Vector() {
	delete[] arr;
}

template<typename T>
std::size_t Vector<T>::get_size() const noexcept {
	return size;
}

template<typename T>
bool Vector<T>::has_item(const T& value) const noexcept {
	for (std::size_t i = 0; i < size; i++)
	{
		if (arr[i] == value)
			return true;
	}
	
	return false;
}

template<typename T>
bool Vector<T>::insert(const std::size_t position, const T& value) {
	if (position > size)
		return false;

	if (size >= capacity)
	{
		std::size_t exp_cap = capacity * 2;
		T* exp_copy = new T[exp_cap];

		for (std::size_t i = 0; i < size; i++)
			exp_copy[i] = arr[i];
		delete[] arr;

		arr = exp_copy;
		capacity = exp_cap;
	}

	for (std::size_t i = size; i > position; i--)
	{
		arr[i] = arr[i - 1];
	}

	arr[position] = value;
	size += 1;

	return true;
}

template<typename T>
void Vector<T>::print() const noexcept {
	for (std::size_t i = 0; i < size; i++)
		std::cout << arr[i] << ' ';
	std::cout << std::endl;
}

template<typename T>
void Vector<T>::push_back(const T& value) {
	insert(size, value);
}

template<typename T>
bool Vector<T>::remove_first(const T& value) {
	for (std::size_t i = 0; i < size; i++)
	{
		if (arr[i] == value)
		{
			for (std::size_t j = i; j < size - 1; j++)
				arr[j] = arr[j + 1];
			size -= 1;
			
			if (size < (capacity / 4) and (capacity / 2) > START_CAPACITY)
			{
				std::size_t nar_cap = capacity / 2;
				T* nar_copy = new T[nar_cap];
				
				for (std::size_t i = 0; i < size; i++)
					nar_copy[i] = arr[i];
				delete[] arr;
				
				arr = nar_copy;
				capacity = nar_cap;
			}

			return true;
		}
	}

	return false;
}
