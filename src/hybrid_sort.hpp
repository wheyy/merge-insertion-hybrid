#ifndef HYBRID_SORT_HPP
#define HYBRID_SORT_HPP

// Sorts arr[left..right] (inclusive) in place using merge sort, switching to
// insertion sort once a subarray's size drops to <= S.
// Returns the number of key comparisons performed.
long long hybridSort(int* arr, int left, int right, int S);

#endif
