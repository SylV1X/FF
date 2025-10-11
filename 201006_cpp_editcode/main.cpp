#include "count_sorting_tools.hpp"
#include "io.hpp"

int main() {
	const int sortable_arr_size = 10;
	const int max_value = 5;
	
	int *sortable_arr = new int[sortable_arr_size]{};
	int *amount_arr(new int[max_value]{});
	
	iod::create_data(sortable_arr, sortable_arr_size, max_value);
	iod::print("Массив до сортировки: ", sortable_arr, sortable_arr_size);
	
	iod::amount(sortable_arr, amount_arr, sortable_arr_size);
	iod::print("Количество элементов: ", amount_arr, max_value);
	
	iod::sort_arr(sortable_arr, amount_arr, max_value);
	iod::print("Отсортированный массив: ", sortable_arr, sortable_arr_size);
	
	delete[] sortable_arr;
	delete[] amount_arr;
}
