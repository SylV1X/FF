#include <iostream>
#include <string>
#include <bubble_sort.cpp>

using namespace std;

int main() {
    vector<int> v = {5, 1, 4, 2, 8};

    bubbleSort(v);

    for (auto i : v)
        cout << i << " ";
    return 0;
}