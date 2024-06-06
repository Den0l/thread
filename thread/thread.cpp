#include <iostream>
#include "Windows.h"
#include <vector>
#include <thread>
#include <functional>

class MergeSort {
public:
    void Sort(std::vector<int>& array) {
        if (array.size() <= 1) return;
        std::vector<int> left(array.begin(), array.begin() + array.size() / 2);
        std::vector<int> right(array.begin() + array.size() / 2, array.end());

        Sort(left);
        Sort(right);
        Merge(array, left, right);
    }

private:
    void Merge(std::vector<int>& array, const std::vector<int>& left, const std::vector<int>& right) {
        size_t leftIndex = 0, rightIndex = 0, arrayIndex = 0;

        while (leftIndex < left.size() && rightIndex < right.size()) {
            if (left[leftIndex] < right[rightIndex]) {
                array[arrayIndex++] = left[leftIndex++];
            }
            else {
                array[arrayIndex++] = right[rightIndex++];
            }
        }

        while (leftIndex < left.size()) {
            array[arrayIndex++] = left[leftIndex++];
        }

        while (rightIndex < right.size()) {
            array[arrayIndex++] = right[rightIndex++];
        }
    }
};

int main() {

    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);


    std::vector<int> array(10);
    std::cout << "Введите 10 чисел для сортировки: " << std::endl;
    for (int& num : array) {
        std::cin >> num;
    }

    MergeSort mergeSort;


    auto sortFunction = [&mergeSort](std::vector<int>& arr) {
        mergeSort.Sort(arr);
    };

    std::thread mergeSortThread(sortFunction, std::ref(array));

    mergeSortThread.join();

    std::cout << "Отсортированный массив: ";
    for (const int& num : array) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
