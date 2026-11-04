#include "RadixSort.hpp"
#include <iostream>

/**
 * @file RadixSort.cpp
 * @brief From-scratch LSD Radix Sort implementation.
 * 
 * ASSIGNED TO: Fareed Zaki (Group 99)
 * 
 * ============================================================================
 * FAREED'S INSTRUCTIONS & REQUIREMENTS (COP3530):
 * ============================================================================
 * 1. STRICTLY FROM SCRATCH:
 *    - Do NOT use std::sort or any built-in sorting libraries.
 *    - The rubric carries a 25% penalty if built-in sorting libraries are used.
 * 
 * 2. ALGORITHM LOGIC (Least Significant Digit Radix Sort):
 *    - Radix Sort is a non-comparison sort operating on digits.
 *    - Base: Decimal (Base-10).
 * 
 *    - Step 1: getMaxKey()
 *      Find the maximum integer key value in the array for the chosen criteria.
 * 
 *    - Step 2: countingSortByDigit() [STABLE SUBROUTINE]
 *      For exponent `exp` (1, 10, 100, 1000...):
 *        a) Create frequency array `int count[10] = {0}`.
 *        b) Count occurrences of digit `(arr[i].getKey(criteria) / exp) % 10`.
 *        c) Calculate cumulative prefix sums: `count[i] += count[i - 1]` to determine
 *           the destination positions.
 *        d) Build the auxiliary array `output` iterating backwards (from n-1 down to 0)
 *           to guarantee STABILITY!
 *        e) Copy `output` back into `arr`.
 * 
 *    - Step 3: radixSort()
 *      Loop through exp = 1; maxKey / exp > 0; exp *= 10.
 *      Track total digit passes and execution time in metrics.
 * ============================================================================
 */

namespace CineSort {

int RadixSort::getMaxKey(const std::vector<Movie>& arr, SortCriteria criteria) {
    // ========================================================================
    // TODO (Fareed Zaki): Implement getMaxKey
    // Loop through arr and find the maximum integer returned by movie.getKey(criteria).
    // ========================================================================
    (void)arr;
    (void)criteria;
    return 0;
}

void RadixSort::countingSortByDigit(std::vector<Movie>& arr,
                                   int exp,
                                   SortCriteria criteria,
                                   std::vector<Movie>& output) {
    // ========================================================================
    // TODO (Fareed Zaki): Implement stable counting sort for current digit (exp)
    // 1. Tally frequencies of (key / exp) % 10 into count[10].
    // 2. Prefix sum count[i] += count[i - 1].
    // 3. Populate output backwards (n - 1 down to 0) to preserve stability:
    //      int digit = (arr[i].getKey(criteria) / exp) % 10;
    //      output[count[digit] - 1] = arr[i];
    //      count[digit]--;
    // 4. Copy output back to arr.
    // ========================================================================
    (void)arr;
    (void)exp;
    (void)criteria;
    (void)output;
}

RadixSortMetrics RadixSort::sort(std::vector<Movie>& arr,
                                SortCriteria criteria,
                                SortOrder order) {
    RadixSortMetrics metrics;

    // ========================================================================
    // TODO (Fareed Zaki): Implement Radix Sort execution
    // 1. Start timing: auto startTime = std::chrono::high_resolution_clock::now();
    // 2. Find maxVal = getMaxKey(arr, criteria);
    // 3. Allocate auxiliary vector<Movie> output(arr.size());
    // 4. For loop: for (long long exp = 1; maxVal / exp > 0; exp *= 10) {
    //        countingSortByDigit(arr, exp, criteria, output);
    //        metrics.digitPasses++;
    //    }
    // 5. If order == SortOrder::Descending, reverse arr.
    // 6. Record elapsed milliseconds into metrics.elapsedMilliseconds.
    // ========================================================================
    (void)arr;
    (void)criteria;
    (void)order;

    std::cout << "   [Notice] Fareed Zaki's Radix Sort is awaiting implementation in src/RadixSort.cpp\n";
    return metrics;
}

} // namespace CineSort
