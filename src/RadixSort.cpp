#include "RadixSort.hpp"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <vector>
#include <cstddef>
#include "Movie.hpp"
#include "Common.hpp"

/**
 * @file RadixSort.cpp
 * @brief From-scratch LSD Radix Sort implementation.
 * 
 * ASSIGNED TO: Fareed Zaki (Group 99)
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
        int count[10] = { 0 };

        // 1 tally frequencies of (key/exp) % 10 into count[10].
        for (size_t i = 0; i < n; ++i) {
            int key = arr[i].getKey(criteria);
            int digit = (key / exp) % 10;
            count[digit]++;
        }

        //2 Prefix sum count[i] += count[i - 1].
        for (int i = 1; i < 10; ++i) {
            count[i] += count[i - 1];
        }

        // 3 makes sure that if movies have same key (year) their order in array is saved
        for (int i = static_cast<int>(n) - 1; i >= 0; --i) {
            int key = arr[i].getKey(criteria);
            int digit = (key / exp) % 10;
            output[count[digit] - 1] = arr[i];
            count[digit]--;
        }

        // 4 copy output back to arr.
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

        //1 start timing
        auto startTime = std::chrono::high_resolution_clock::now();

        // 2 find maxVal
        int maxVal = getMaxKey(arr, criteria);

        // 3 allocate helper vector
        std::vector<Movie> output(n);
        metrics.auxiliaryMemoryBytes = n * sizeof(Movie);

        // 4 for loop execution across digit places
        for (long long exp = 1; maxVal / exp > 0; exp *= 10) {
            countingSortByDigit(arr, static_cast<int>(exp), criteria, output);
            metrics.digitPasses++;
        }

        // 5 if order == SortOrder::Descending, reverse arr in-place.
        if (order == SortOrder::Descending) {
            size_t left = 0;
            size_t right = n - 1;
            while (left < right) {
                std::swap(arr[left], arr[right]);
                left++;
                right--;
            }
        }

        // 6 Record milliseconds that passed into metrics.elapsedMilliseconds
        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = endTime - startTime;
        metrics.elapsedMilliseconds = duration.count();

        return metrics;
    }

} // namespace CineSort
