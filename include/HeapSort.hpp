#pragma once

#include <vector>
#include <cstddef>
#include "Movie.hpp"
#include "Common.hpp"

/**
 * @file HeapSort.hpp
 * @brief From-scratch Heap Sort module declaration.
 * 
 * Assigned to: Erik Woods (Group 99)
 * 
 * Algorithmic Specifications:
 * - Strictly from-scratch: NO std::sort, NO std::priority_queue.
 * - In-place comparison sort: auxiliary space O(1).
 * - Time complexity: O(n log n) best, worst, and average.
 * - Array-based complete binary tree:
 *     Left Child  = 2 * i + 1
 *     Right Child = 2 * i + 2
 *     Parent      = (i - 1) / 2
 */

namespace CineSort {

struct HeapSortMetrics {
    double elapsedMilliseconds = 0.0;   ///< Total sorting duration in ms
    unsigned long long comparisons = 0;  ///< Key comparison count
    unsigned long long swaps = 0;        ///< Element swap count
};

class HeapSort {
public:
    /**
     * @brief Executes the complete Heap Sort algorithm on the given vector.
     * 
     * @param arr The vector of movies to sort in-place.
     * @param criteria The sorting attribute (Year, Runtime, Votes).
     * @param order Ascending or Descending.
     * @return HeapSortMetrics Populated metrics including timing and operations.
     */
    static HeapSortMetrics sort(std::vector<Movie>& arr,
                               SortCriteria criteria,
                               SortOrder order = SortOrder::Ascending);

private:
    /**
     * @brief Restores the heap invariant for a subtree rooted at index i.
     * 
     * @param arr Vector containing elements.
     * @param n Size of the active heap partition.
     * @param i Root index of the current subtree.
     * @param criteria Sorting key attribute.
     * @param order Ascending (requires Max-Heap) or Descending (requires Min-Heap).
     * @param metrics Metrics tracker for comparisons and swaps.
     */
    static void siftDown(std::vector<Movie>& arr,
                         size_t n,
                         size_t i,
                         SortCriteria criteria,
                         SortOrder order,
                         HeapSortMetrics& metrics);

    /**
     * @brief Converts an arbitrary array into a valid heap in O(n) time.
     * Begins at the last non-leaf node: index (n / 2) - 1 down to 0.
     */
    static void buildHeap(std::vector<Movie>& arr,
                          SortCriteria criteria,
                          SortOrder order,
                          HeapSortMetrics& metrics);
};

} // namespace CineSort
