#pragma once

#include <vector>
#include "Movie.hpp"
#include "Common.hpp"
#include "HeapSort.hpp"
#include "RadixSort.hpp"

namespace CineSort {

// Helpers to verify output and display comparison stats
class Benchmark {
public:
    static bool verifySorted(const std::vector<Movie>& arr,
                            SortCriteria criteria,
                            SortOrder order = SortOrder::Ascending);

    static void printComparison(const HeapSortMetrics& heapM,
                                const RadixSortMetrics& radixM,
                                size_t datasetSize,
                                SortCriteria criteria);
};

} // namespace CineSort
