#include "RadixSort.hpp"
#include <chrono>
#include <algorithm> // only for std::reverse if descending, or we can reverse manually

/**
 * @file RadixSort.cpp
 * @brief From-scratch LSD Radix Sort implementation.
 * 
 * Assigned to: Fareed Zaki (Group 99)
 * 
 * ============================================================================
 * ARCHITECTURAL GUIDANCE FOR FAREED:
 * ============================================================================
 * 1. LSD RADIX SORT MECHANICS:
 *    - Process digits from the Least Significant Digit (ones place, exp = 1)
 *      up to the Most Significant Digit (exp = 10^(d-1)).
 *    - For each digit position, we perform a STABLE Counting Sort subroutine.
 *    - Stability is critical: elements with identical current digits must retain
 *      the relative order established by earlier digit passes.
 * 
 * 2. COUNTING SORT SUBROUTINE (Base-10):
 *    - Step A: Frequency array `int count[10] = {0}`.
 *              For each movie, digit = (key / exp) % 10.
 *              count[digit]++;
 *    - Step B: Prefix sums to find actual ending indices in the output buffer:
 *              for i = 1 to 9: count[i] += count[i - 1];
 *    - Step C: Build output array from RIGHT to LEFT (n-1 down to 0) to ensure
 *              STABILITY:
 *              output[count[digit] - 1] = arr[i];
 *              count[digit]--;
 *    - Step D: Copy output array back to arr.
 * 
 * 3. COMPLEXITY & MEMORY ANALYSIS:
 *    - Time Complexity: O(d * (n + 10)) where d is the max number of digits.
 *      For 100k+ rows with values up to 2.5 million (votes), d <= 7 passes.
 *    - Space Complexity: Auxiliary vector `output` of size n (O(n) space).
 * ============================================================================
 */

namespace CineSort {

int RadixSort::getMaxKey(const std::vector<Movie>& arr, SortCriteria criteria) {
    int maxVal = 0;
    for (const auto& movie : arr) {
        int key = movie.getKey(criteria);
        if (key > maxVal) {
            maxVal = key;
        }
    }
    return maxVal;
}

void RadixSort::countingSortByDigit(std::vector<Movie>& arr,
                                   int exp,
                                   SortCriteria criteria,
                                   std::vector<Movie>& output) {
    size_t n = arr.size();
    int count[10] = {0};

    // Step A: Store count of occurrences of each digit
    for (size_t i = 0; i < n; ++i) {
        int key = arr[i].getKey(criteria);
        int digit = (key / exp) % 10;
        count[digit]++;
    }

    // Step B: Transform count[i] so that it contains the actual position in output
    for (int i = 1; i < 10; ++i) {
        count[i] += count[i - 1];
    }

    // Step C: Build output array in reverse order to preserve stability
    for (int i = static_cast<int>(n) - 1; i >= 0; --i) {
        int key = arr[i].getKey(criteria);
        int digit = (key / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Step D: Copy sorted output back to arr
    for (size_t i = 0; i < n; ++i) {
        arr[i] = output[i];
    }
}

RadixSortMetrics RadixSort::sort(std::vector<Movie>& arr,
                                SortCriteria criteria,
                                SortOrder order) {
    RadixSortMetrics metrics;
    size_t n = arr.size();
    if (n <= 1) return metrics;

    auto startTime = std::chrono::high_resolution_clock::now();

    int maxVal = getMaxKey(arr, criteria);

    // Pre-allocate auxiliary buffer once to avoid repeated reallocations
    std::vector<Movie> output(n);
    metrics.auxiliaryMemoryBytes = n * sizeof(Movie);

    // Run counting sort for every digit. exp is 10^i where i is current digit place
    for (long long exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSortByDigit(arr, static_cast<int>(exp), criteria, output);
        metrics.digitPasses++;
    }

    // If descending order requested, reverse the sorted vector in-place
    if (order == SortOrder::Descending) {
        size_t left = 0;
        size_t right = n - 1;
        while (left < right) {
            std::swap(arr[left], arr[right]);
            left++;
            right--;
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = endTime - startTime;
    metrics.elapsedMilliseconds = duration.count();

    return metrics;
}

} // namespace CineSort
