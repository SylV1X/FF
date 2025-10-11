#include "count_sorting_tools.hpp"

void iod::sort_arr(int* arr, const int* amount_arr, const int size){
	
	int sw = 0;
	for (int i = 0; i < size; i++){
		for (int j = 0; j < amount_arr[i]; j++, sw++){
			arr[sw] = i;
		}
	}
	
}