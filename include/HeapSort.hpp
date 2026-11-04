#pragma once

#include <vector>
#include <cstddef>
#include "Movie.hpp"
#include "Common.hpp"

namespace CineSort {

// Metrics tracked during heap sort
struct HeapSortMetrics {
    double elapsedMilliseconds = 0.0;
    unsigned long long comparisons = 0;
    unsigned long long swaps = 0;
};

// Erik Woods: In-place Heap Sort
class HeapSort {
public:
    static HeapSortMetrics sort(std::vector<Movie>& arr,
                               SortCriteria criteria,
                               SortOrder order = SortOrder::Ascending);

private:
    static void siftDown(std::vector<Movie>& arr,
                         size_t n,
                         size_t i,
                         SortCriteria criteria,
                         SortOrder order,
                         HeapSortMetrics& metrics);

    static void buildHeap(std::vector<Movie>& arr,
                          SortCriteria criteria,
                          SortOrder order,
                          HeapSortMetrics& metrics);
};

} // namespace CineSort
