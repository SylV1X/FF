#include "count_sorting_tools.hpp"

void iod::amount(const int* arr, int* amount_arr, const int size){
	
	for (int i = 0; i < size; i++){
		amount_arr[arr[i]]++;
	}
	
}