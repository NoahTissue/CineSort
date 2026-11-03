#pragma once

#include <vector>
#include "Movie.hpp"
#include "Common.hpp"
#include "HeapSort.hpp"
#include "RadixSort.hpp"

/**
 * @file Benchmark.hpp
 * @brief Benchmark analytics, sortedness verification, and metrics reporting.
 * 
 course: COP3530 Project 2b (Group 99)
 */

namespace CineSort {

class Benchmark {
public:
    /**
     * @brief Programmatically verifies that a vector is strictly in non-decreasing
     * (or non-increasing) order according to the given criteria.
     * 
     * @param arr The vector to verify.
     * @param criteria The attribute key.
     * @param order Ascending or Descending.
     * @return true if validly sorted across all elements, false if any inversion exists.
     */
    static bool verifySorted(const std::vector<Movie>& arr,
                            SortCriteria criteria,
                            SortOrder order = SortOrder::Ascending);

    /**
     * @brief Formats and prints a side-by-side terminal comparison table
     * between Heap Sort and Radix Sort metrics.
     */
    static void printComparison(const HeapSortMetrics& heapM,
                                const RadixSortMetrics& radixM,
                                size_t datasetSize,
                                SortCriteria criteria);
};

} // namespace CineSort
