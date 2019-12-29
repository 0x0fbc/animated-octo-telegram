#include <stdlib.h>

#ifndef SORTS_H_
#define SORTS_H_

// Swaps the values at offset a and b of arr.
void swap_int(const int *arr, size_t a, size_t b);

// Executes a selection sort on arr.
void selection_sort_int(const int *arr, size_t len);

// Executes an insertion sort on arr.
void insertion_sort_int(const int *arr, size_t len);

// Executes a bubble sort on arr.
void bubble_sort_int(const int *arr, size_t len);

// Executes a quicksort on arr.
void quick_sort_int(const int *arr, size_t len);
// Recursively apply quicksort on subarray of arr between l and r.
void qs_int(const int *arr, size_t len, size_t l, size_t r);
// Partitions an array for quicksort, returns the index of the pivot point.
size_t qs_partition(const int *arr, size_t len, size_t l, size_t r, int pivot);

// Execute a merge sort on arr.
void merge_sort_int(const int *arr, size_t len);
// Merges lh and rh's elements into arr, sorted.
void merge_int(const int *lh, size_t lh_len,
               const int *rh, size_t rh_len,
               const int *arr);

// Execute a heap sort on arr.
void heap_sort_int(const int *arr, size_t len);
// Sifts root_index down in arr via its largest child.
void heapify(const int *arr, size_t heap_offset, size_t root_index);

#endif
