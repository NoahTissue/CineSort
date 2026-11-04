#include "RadixSort.hpp"
#include <iostream>

// ==========================================
// FAREED ZAKI: Radix Sort Implementation
// Custom LSD Radix Sort (do not use std::sort)
// ==========================================

namespace CineSort {

int RadixSort::getMaxKey(const std::vector<Movie>& arr, SortCriteria criteria) {
    // Fareed: Find and return the largest key in arr using movie.getKey(criteria).
    (void)arr; (void)criteria;
    return 0;
}

void RadixSort::countingSortByDigit(std::vector<Movie>& arr,
                                   int exp,
                                   SortCriteria criteria,
                                   std::vector<Movie>& output) {
    // Fareed: Counting sort pass for digit position exp (1, 10, 100...). Be sure to fill output backwards to keep it stable.
    (void)arr; (void)exp; (void)criteria; (void)output;
}

RadixSortMetrics RadixSort::sort(std::vector<Movie>& arr,
                                SortCriteria criteria,
                                SortOrder order) {
    RadixSortMetrics metrics;

    // Fareed: Main radix loop goes here (call countingSortByDigit for each digit power exp until maxKey is covered).
    (void)arr; (void)criteria; (void)order;

    std::cout << "   [Notice] Fareed Zaki's Radix Sort is awaiting implementation in src/RadixSort.cpp\n";
    return metrics;
}

} // namespace CineSort
