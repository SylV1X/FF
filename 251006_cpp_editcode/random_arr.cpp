#include "count_sorting_tools.hpp"

#include <ctime>
#include <random>

void iod::create_data(int* arr, const int size, const int max_value){
	
	std::mt19937 mt(time(nullptr));
	for (int i = 0; i < size; ++i) {
		arr[i] = (mt() % max_value);
	}
	
}