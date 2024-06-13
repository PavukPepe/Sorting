#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

class MergeSort {
public:
    void Merge(std::vector<int>& arr, int low, int mid, int high) {
        int num_1 = mid - low + 1;
        int num_2 = high - mid;

        std::vector<int> left_part(num_1), right_part(num_2);

        for (int i = 0; i < num_1; ++i)
            left_part[i] = arr[low + i];
        for (int j = 0; j < num_2; ++j)
            right_part[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = low;
        while (i < num_1 && j < num_2) {
            if (left_part[i] <= right_part[j]) {
                arr[k] = left_part[i];
                i++;
            }
            else {
                arr[k] = right_part[j];
                j++;
            }
            k++;
        }

        while (i < num_1) {
            arr[k] = left_part[i];
            i++;
            k++;
        }

        while (j < num_2) {
            arr[k] = right_part[j];
            j++;
            k++;
        }
    }

    void Sort(std::vector<int>& arr, int low, int high) {
        if (low < high) {
            int mid = low + (high - low) / 2;
            Sort(arr, low, mid);
            Sort(arr, mid + 1, high);
            Merge(arr, low, mid, high);
        }
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    std::vector<int> arr(10);

    std::cout << "Введите 10 целых чисел:\n";
    for (int i = 0; i < 10; i++) {
        std::cin >> arr[i];
    }

    MergeSort mergeSort;
    std::thread mergeSortThread([&]() {
        mergeSort.Sort(arr, 0, arr.size() - 1);
        });

    mergeSortThread.join();

    std::cout << "Отсортированный массив:\n";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}