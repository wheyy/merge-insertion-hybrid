#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

// Sorts arr[left..right] (inclusive) in place using plain merge sort
// (recurses all the way down to single elements, no threshold).
// Returns the number of key comparisons performed.
long long mergeSort(int* arr, int left, int right);

#endif
