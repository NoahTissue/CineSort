#pragma once

#include <vector>
#include <cstddef>
#include "Movie.hpp"
#include "Common.hpp"

/**
 * @file RadixSort.hpp
 * @brief From-scratch Least Significant Digit (LSD) Radix Sort module declaration.
 * 
 * Assigned to: Fareed Zaki (Group 99)
 * 
 * Algorithmic Specifications:
 * - Strictly from-scratch: NO std::sort.
 * - Non-comparison sort: operates on digit values using Counting Sort as a subroutine.
 * - Time Complexity: O(d * (n + k)) where:
 *     d = number of digits in the maximum key
 *     n = number of elements (100,000+)
 *     k = radix base (10 for decimal)
 * - Auxiliary Space: O(n) auxiliary storage for stable bucket reconstruction.
 * - Stability: LSD Radix Sort MUST be stable to preserve relative order of previous digits.
 */

namespace CineSort {

struct RadixSortMetrics {
    double elapsedMilliseconds = 0.0;   ///< Total sorting duration in ms
    int digitPasses = 0;                 ///< Total counting sort passes (digits processed)
    size_t auxiliaryMemoryBytes = 0;     ///< Approximate extra memory utilized (O(n))
};

class RadixSort {
public:
    /**
     * @brief Executes the complete LSD Radix Sort algorithm on the given vector.
     * 
     * @param arr The vector of movies to sort.
     * @param criteria The sorting attribute (Year, Runtime, Votes).
     * @param order Ascending or Descending.
     * @return RadixSortMetrics Populated metrics including timing and digit passes.
     */
    static RadixSortMetrics sort(std::vector<Movie>& arr,
                                SortCriteria criteria,
                                SortOrder order = SortOrder::Ascending);

private:
    /**
     * @brief Finds the maximum key value present in the array for the given attribute.
     */
    static int getMaxKey(const std::vector<Movie>& arr, SortCriteria criteria);

    /**
     * @brief Performs a stable counting sort pass on arr based on the digit represented by exp.
     * 
     * @param arr Source vector to sort.
     * @param exp Current digit place (1 for ones, 10 for tens, 100 for hundreds, etc.).
     * @param criteria Attribute key to extract from Movie.
     * @param output Temporary auxiliary vector of size n.
     */
    static void countingSortByDigit(std::vector<Movie>& arr,
                                    int exp,
                                    SortCriteria criteria,
                                    std::vector<Movie>& output);
};

} // namespace CineSort
