#include "merge_sort.hpp"
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

void mergeSortRec(int* arr, int left, int right, int* temp, long long& comparisons) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSortRec(arr, left, mid, temp, comparisons);
    mergeSortRec(arr, mid + 1, right, temp, comparisons);
    merge(arr, left, mid, right, temp, comparisons);
}

} // namespace

long long mergeSort(int* arr, int left, int right) {
    long long comparisons = 0;
    if (left >= right) {
        return comparisons;
    }
    // temp is indexed the same way as arr (0-based from the start of the
    // array), so it needs to be sized up to `right`, not just the span
    // length, even though only [left..right] is ever touched.
    std::vector<int> temp(right + 1);
    mergeSortRec(arr, left, right, temp.data(), comparisons);
    return comparisons;
}
