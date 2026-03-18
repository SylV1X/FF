#include "doubly_linked_list.hpp"

#include <iostream>

using ssY::DoublyLinkedList;

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	Node* now = begin;

	while (now != nullptr)
	{
		Node* next = now->next;
		delete now;
		now = next;
	}

	begin = nullptr;
	end = nullptr;
}

template<typename T>
std::size_t DoublyLinkedList<T>::get_size() const noexcept {
	std::size_t size = 0;
	Node* now = begin;

	while (now != nullptr)
	{
		size++;
		now = now->next;
	}

	return size;
}

template<typename T>
bool DoublyLinkedList<T>::has_item(const T& value) const noexcept {
	Node* now = begin;

	while (now != nullptr)
	{
		if (now->value == value)
			return true;
		now = now->next;
	}

	return false;
}

template<typename T>
void DoublyLinkedList<T>::print() const noexcept {
	Node* now = begin;

	while (now != nullptr)
	{
		std::cout << now->value;
		if (now->next != nullptr)
			std::cout << ' ';
		now = now->next;
	}
	std::cout << std::endl;
}

template<typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
	Node* exp_Node = new Node(value);

	if (begin == nullptr)
	{
		begin = exp_Node;
		end = exp_Node;
	}
	else
	{
		exp_Node->prev = end;
		end->next = exp_Node;
		end = exp_Node;
	}
}

template<typename T>
bool DoublyLinkedList<T>::remove_first(const T& value) noexcept {
	Node* now = begin;

	while (now != nullptr)
	{
		if (now->value == value)
		{
			if (now->prev != nullptr)
				now->prev->next = now->next;
			else
				begin = now->next;

			if (now->next != nullptr)
				now->next->prev = now->prev;
			else
				end = now->prev;

			delete now;

			return true;
		}

		now = now->next;
	}
	
	return false;
}
