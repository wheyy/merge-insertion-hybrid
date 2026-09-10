#include "hybrid_sort.hpp"
#include "insertion_sort.hpp"
#include <vector>

namespace {

void merge(int* arr, int left, int mid, int right, int* temp, long long& comparisons) {
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        ++comparisons;
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= right) {
        temp[k++] = arr[j++];
    }
    for (int x = left; x <= right; ++x) {
        arr[x] = temp[x];
    }
}

void hybridSortRec(int* arr, int left, int right, int S, int* temp, long long& comparisons) {
    if (right - left + 1 <= S) {
        comparisons += insertionSort(arr, left, right);
        return;
    }
    int mid = left + (right - left) / 2;
    hybridSortRec(arr, left, mid, S, temp, comparisons);
    hybridSortRec(arr, mid + 1, right, S, temp, comparisons);
    merge(arr, left, mid, right, temp, comparisons);
}

} // why does namespace end here? 

long long hybridSort(int* arr, int left, int right, int S) {
    long long comparisons = 0;
    if (left >= right) {
        return comparisons;
    }
    if (S < 1) {
        S = 1;
    }
    std::vector<int> temp(right + 1);
    hybridSortRec(arr, left, right, S, temp.data(), comparisons);
    return comparisons;
}
