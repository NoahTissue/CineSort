#include "HeapSort.hpp"
#include <iostream>

// ==========================================
// ERIK WOODS: Heap Sort Implementation
// Custom in-place sort (do not use std::sort)
// ==========================================

namespace CineSort {

void HeapSort::siftDown(std::vector<Movie>& arr,
                        size_t n,
                        size_t i,
                        SortCriteria criteria,
                        SortOrder order,
                        HeapSortMetrics& metrics) {
    // Erik: Compare parent at index i with children (2*i+1 and 2*i+2), swap with the larger child, and sift down.
    (void)arr; (void)n; (void)i; (void)criteria; (void)order; (void)metrics;
}

void HeapSort::buildHeap(std::vector<Movie>& arr,
                         SortCriteria criteria,
                         SortOrder order,
                         HeapSortMetrics& metrics) {
    // Erik: Turn the array into a max-heap by calling siftDown from index (n/2 - 1) down to 0.
    (void)arr; (void)criteria; (void)order; (void)metrics;
}

HeapSortMetrics HeapSort::sort(std::vector<Movie>& arr,
                               SortCriteria criteria,
                               SortOrder order) {
    HeapSortMetrics metrics;

    // Erik: Main sort logic goes here (call buildHeap, repeatedly swap arr[0] with arr[i], and siftDown).
    (void)arr; (void)criteria; (void)order;

    std::cout << "   [Notice] Erik Woods's Heap Sort is awaiting implementation in src/HeapSort.cpp\n";
    return metrics;
}

} // namespace CineSort
