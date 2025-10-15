#include <iostream>
#include <cmath>

void output_sequences(const char* const comm_1, const char* const comm_2, const int size, int index);

int main()
{
	std::cout << "Введите количество последовательностей: ";
	int number;
	std::cin >> number;
	const int seq_size = 10;
	
	for (int i = 1; i < number + 1; i++) {
		output_sequences("Последовательность", "Среднее последовательности №", seq_size, i);
	}
	
	return 0;
}

void output_sequences(const char* const comm_1, const char* const comm_2, const int size, int index) {	
	int sequence[size];
	float average = 0;
	
	std::cout << comm_1 << ' ' << index << ':' << std::endl;
	
	for (int i = 0; i < size; i++) {
		sequence[i] = std::rand() % size;
		average += sequence[i];
		std::cout << sequence[i] << ' ';
	}
	
	average /= size;
	
	std::cout << std::endl;
	std::cout << comm_2 << ' ' << index << ": " << average << std::endl;
	std::cout << ' ' << std::endl;
	
}
