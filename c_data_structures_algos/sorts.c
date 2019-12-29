/*
 * Simple implementations of common sorting algorithms.
 *
 * Each sort is written for ints and requires the following arguments:
 *      a const *int pointing to the first element of the data
 *      a size_t indicating the length of the data
 *
 * Provided sorts & their entry points:
 * selection (selection_sort_int())
 * insertion (insertion_sort_int())
 * bubble (bubble_sort_int()))
 * quick (quick_sort_int())
 * merge (merge_sort_int())
 * heap (heap_sort_int())
 *
 * @0x0fbc
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sorts.h"

void swap_int(const int *arr, size_t a, size_t b)
{
    // Convert the const int pointer passed in into a plain int ptr
    int *ptr_arr = (int *) arr;
    // Copy the dereference at arr offset by a to tmp
    int tmp = *(arr + a);
    // Copy the dereference of arr offset by b to arr offset by a
    *(ptr_arr + a) = *(arr + b);
    // Copy tmp (which contains a's old value) to arr offset by b
    *(ptr_arr + b) = tmp;
}


void selection_sort_int(const int *arr, size_t len)
{
    for (size_t i = 0; i < len; i++) {
        size_t min = i;
        for (size_t j = i; j < len; j++) {
            if (arr[i] > arr[j]) {
                min = j;
            }
        }
        // Avoid unneeded swaps
        if (min != i){
            swap_int(arr, i, min);
        }
    }
}

void insertion_sort_int(const int *arr, size_t len)
{
    for (size_t i = 1; i < len; i++) {
        int j = i;
        while ((j > 0) && (arr[j] < arr[j-1])) {
            swap_int(arr, j, j-1);
            j--;
        }
    }
}

void bubble_sort_int(const int *arr, size_t len)
{
    /*
     * This bubblesort remembers the highest swap index and restricts the
     * next iteration of the sort to an upper bound of last highest swap.
     */
    size_t max_unsort = len;
    size_t last_swap_idx;
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (size_t i = 0; i < max_unsort; i++) {
            if (arr[i] > arr[i+1]) {
                // swap arr[i] and arr[i+1]
                swap_int(arr, i, i+1);

                // Save the last index swapped and flag swap to true.
                swapped = true;
                last_swap_idx = i;
            }
        }
        // Copy the highest swap index into max_unsort so we can loop on it.
        max_unsort = last_swap_idx;
    }
}

size_t qs_partition(const int *arr, size_t len, size_t l, size_t r, int pivot)
{
    /*
     * Move left and right pointers towards the pivot value, swapping pairs
     * which are on the wrong side of the pivot.
     */
    while (l <= r && r <= len) {
        while (arr[l] < pivot) {
            l++;
        }
        while (arr[r] > pivot) {
            r--;
        }
        if (l <= r) {
            swap_int(arr, l, r);
            l++;
            r--;
        }
    }
    return l;
}

void qs_int(const int *arr, size_t len, size_t l, size_t r)
{
    if (l >= r) {
        // Nothing to do if the pointers cross.
        return;
    }
    int pivot = arr[l];
    // Partition the left and right sides of the array around the pivot.
    size_t idx = qs_partition(arr, len, l, r, pivot);
    // Recursively apply quicksort on the left and right subarrays.
    qs_int(arr, len, l, idx - 1);
    qs_int(arr, len, idx, r);
}

void quick_sort_int(const int *arr, size_t len)
{
    qs_int(arr, len, 0, len-1);
}

void merge_int(const int *lh, size_t lh_len,
               const int *rh, size_t rh_len,
               const int *arr)
{
    // de-const *arr so we can write to it
    int *arr_write = (int *) arr;

    size_t idx_lh = 0;
    size_t idx_rh = 0;
    size_t idx_arr = 0;

    /*
     * Seperately through the left and right subarrays, selecting the smaller
     * value between the current index of the iterations and copying it into
     * arr.
     */
    while (idx_lh < lh_len && idx_rh < rh_len) {
        if (lh[idx_lh] < rh[idx_rh]) {
            arr_write[idx_arr] = lh[idx_lh];
            idx_arr++;
            idx_lh++;
        } else {
            arr_write[idx_arr] = rh[idx_rh];
            idx_arr++;
            idx_rh++;
        }
    }
    // Handle edge case where a subarray has values left to copy.
    while (idx_lh < lh_len) {
        arr_write[idx_arr] = lh[idx_lh];
        idx_arr++;
        idx_lh++;
    }
    while(idx_rh < rh_len) {
        arr_write[idx_arr] = rh[idx_rh];
        idx_arr++;
        idx_rh++;
    }

}

void merge_sort_int(const int *arr, size_t len)
{
    // Base case for recursion, start returning if the array is len 1.
    if (len > 1) {
        // Construct the left half subarray and mergesort it.
        size_t lh_len = len / 2;
        int *lh = malloc(sizeof(int) * lh_len);
        memcpy(lh, arr, sizeof(int) * lh_len);
        merge_sort_int(lh, lh_len);

        // Construct the right half subarray and mergesort it
        size_t rh_len = len - (len/2);
        int *rh = malloc(sizeof(int) * rh_len);
        memcpy(rh, (arr + lh_len), sizeof(int) * rh_len);
        merge_sort_int(rh, rh_len);

        // Merge the sorted left and half subarrays
        merge_int(lh, lh_len, rh, rh_len, arr);

        // The subarrays are no longer needed, so they're freed before ret.
        free(lh);
        free(rh);
    }
}

void heapify(const int *arr, size_t heap_offset, size_t root_index)
{
    size_t max = root_index;

    size_t l = 2 * root_index + 1;
    if (l < heap_offset
        && arr[max] < arr[l]) {
        max = l;
    }

    size_t r = 2 * root_index + 2;
    if (r < heap_offset
        && arr[max] < arr[r]) {
        max = r;
    }
    if (max != root_index) {
        swap_int(arr, max, root_index);
        heapify(arr, heap_offset, max);
    }
}

void heap_sort_int(const int *arr, size_t len)
{
    // Turn arr into a max heap.
    for (size_t i = len; (i + 1) > 0; i--) {
        heapify(arr, len, i);
    }

    // Extract elements in sorted order.
    for(size_t i = len - 1; i+1 > 0; i--) {
        swap_int(arr, i, 0);
        heapify(arr, i, 0);
    }
}
