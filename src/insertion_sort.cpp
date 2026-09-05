#include "insertion_sort.hpp"

long long insertionSort(int* arr, int left, int right) {
    long long comparisons = 0;

    for (int i = left + 1; i <= right; ++i) {
        int key = arr[i];
        int j = i - 1;

        // Each loop test "j >= left && arr[j] > key" performs one key
        // comparison, except the final test that fails only on the
        // left-bound check (no key comparison happens then).
        while (j >= left) {
            ++comparisons;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                --j;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }

    return comparisons;
}
