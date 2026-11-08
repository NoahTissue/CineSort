#include "HeapSort.hpp"
#include <chrono>
#include <utility>

// ========================================================
// Heap Sort Implementation (Noah Techoueyres & Fareed Zaki)
// Custom in-place sort (zero use of std::sort / priority_queue)
// ========================================================

namespace CineSort {

void HeapSort::siftDown(std::vector<Movie>& arr,
                        size_t n,
                        size_t i,
                        SortCriteria criteria,
                        SortOrder order,
                        HeapSortMetrics& metrics) {
    size_t current = i;

    while (true) {
        size_t target = current;
        size_t left = 2 * current + 1;
        size_t right = 2 * current + 2;

        // Lambda to compare keys based on sort order
        auto isPreferred = [&](int childKey, int parentKey) -> bool {
            metrics.comparisons++;
            if (order == SortOrder::Ascending) {
                return childKey > parentKey; // Max-heap for ascending sort
            } else {
                return childKey < parentKey; // Min-heap for descending sort
            }
        };

        if (left < n && isPreferred(arr[left].getKey(criteria), arr[target].getKey(criteria))) {
            target = left;
        }

        if (right < n && isPreferred(arr[right].getKey(criteria), arr[target].getKey(criteria))) {
            target = right;
        }

        if (target != current) {
            std::swap(arr[current], arr[target]);
            metrics.swaps++;
            current = target; // Continue sifting down iteratively
        } else {
            break;
        }
    }
}

void HeapSort::buildHeap(std::vector<Movie>& arr,
                         SortCriteria criteria,
                         SortOrder order,
                         HeapSortMetrics& metrics) {
    size_t n = arr.size();
    if (n <= 1) return;

    // Start at last internal node (n / 2 - 1) and sift down to root
    for (int i = static_cast<int>(n / 2) - 1; i >= 0; --i) {
        siftDown(arr, n, static_cast<size_t>(i), criteria, order, metrics);
    }
}

HeapSortMetrics HeapSort::sort(std::vector<Movie>& arr,
                               SortCriteria criteria,
                               SortOrder order) {
    HeapSortMetrics metrics;
    size_t n = arr.size();
    if (n <= 1) return metrics;

    auto startTime = std::chrono::high_resolution_clock::now();

    // 1. Build the binary heap in-place in O(n) time
    buildHeap(arr, criteria, order, metrics);

    // 2. Extract root element repeatedly and place at the end of unsorted partition
    for (size_t i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        metrics.swaps++;
        siftDown(arr, i, 0, criteria, order, metrics);
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = endTime - startTime;
    metrics.elapsedMilliseconds = duration.count();

    return metrics;
}

} // namespace CineSort
