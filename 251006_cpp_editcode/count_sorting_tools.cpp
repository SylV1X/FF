#include "count_sorting_tools.hpp"

#include <ctime>
#include <random>

void iod::create_data(int* arr, const int size, const int max_value){
	std::mt19937 mt(time(nullptr));
	for (int i = 0; i < size; ++i) {
		arr[i] = (mt() % max_value);
	}
}
void iod::sort_arr(int* arr, const int* amount_arr, const int size){
	int sw = 0;
	for (int i = 0; i < size; i++){
		for (int j = 0; j < amount_arr[i]; j++, sw++){
			arr[sw] = i;
		}
	}
}
void iod::amount(const int* arr, int* amount_arr, const int size){
	for (int i = 0; i < size; i++){
		amount_arr[arr[i]]++;
	}
}