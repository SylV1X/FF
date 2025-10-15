#ifndef COUNT_SORTING_TOOLS_HPP
#define COUNT_SORTING_TOOLS_HPP

namespace iod{
	void amount(const int* arr, int* amount_arr, const int size);
	void create_data(int* arr, const int size, const int max_value);
	void sort_arr(int* data_arr, const int* amount_arr, const int size);
}

#endif