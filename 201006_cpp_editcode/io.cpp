#include "io.hpp"

#include <iostream>

void iod::print(const char* const comment, int* arr, const int size) {
	std::cout << comment;
	for (int i = 0; i < size; ++i) {
		std::cout << arr[i] << ' ';
	}
	std::cout << std::endl;
}