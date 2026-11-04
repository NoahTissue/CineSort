#pragma once

#include <vector>
#include <cstddef>
#include "Movie.hpp"
#include "Common.hpp"

namespace CineSort {

// Metrics tracked during radix sort
struct RadixSortMetrics {
    double elapsedMilliseconds = 0.0;
    int digitPasses = 0;
    size_t auxiliaryMemoryBytes = 0;
};

// Fareed Zaki: Least Significant Digit (LSD) Radix Sort
class RadixSort {
public:
    static RadixSortMetrics sort(std::vector<Movie>& arr,
                                SortCriteria criteria,
                                SortOrder order = SortOrder::Ascending);

private:
    static int getMaxKey(const std::vector<Movie>& arr, SortCriteria criteria);

    static void countingSortByDigit(std::vector<Movie>& arr,
                                    int exp,
                                    SortCriteria criteria,
                                    std::vector<Movie>& output);
};

} // namespace CineSort
