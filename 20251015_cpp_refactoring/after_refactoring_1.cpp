#include <iostream>
#include <cmath>

void output_sequences(const char* const comm_1, const char* const comm_2, const int size, int index) {
	
	float sequence[10];
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

int main()
{
	int n;
	std::cin >> n;
	const int seq_size = 10;
	
	for (int i = 1; i < n + 1; i++) {
		output_sequences("Sequense", "Average from sequence", seq_size, i);
	}
	
	return 0;
}
