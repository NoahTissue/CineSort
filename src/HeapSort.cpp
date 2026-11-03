#include "HeapSort.hpp"
#include <chrono>
#include <utility>

/**
 * @file HeapSort.cpp
 * @brief From-scratch Heap Sort implementation.
 * 
 * Assigned to: Erik Woods (Group 99)
 * 
 * ============================================================================
 * ARCHITECTURAL GUIDANCE FOR ERIK:
 * ============================================================================
 * 1. HEAP PROPERTY:
 *    - To sort in ASCENDING order, we build a MAX-HEAP. The maximum element
 *      repeatedly bubbles to the root (index 0) and is swapped to the back (index n-1).
 *    - To sort in DESCENDING order, we build a MIN-HEAP.
 * 
 * 2. TREE ARITHMETIC (Zero-Indexed):
 *    - Left child of index i  = 2 * i + 1
 *    - Right child of index i = 2 * i + 2
 *    - Parent of index i      = (i - 1) / 2
 * 
 * 3. EXECUTION PHASES:
 *    - Phase 1 (Build Heap): Bottom-up heapify starting from the last non-leaf
 *      node: (n / 2) - 1 down to index 0. Time Complexity: O(n).
 *    - Phase 2 (Extraction): Loop i from n-1 down to 1:
 *        a) Swap root arr[0] with arr[i].
 *        b) Call siftDown on the reduced heap of size i rooted at 0.
 *      Time Complexity: O(n log n).
 * 
 * 4. METRICS TRACKING:
 *    - Increment `metrics.comparisons` whenever you compare two Movie keys.
 *    - Increment `metrics.swaps` whenever two Movie instances are swapped.
 * ============================================================================
 */

namespace CineSort {

void HeapSort::siftDown(std::vector<Movie>& arr,
                        size_t n,
                        size_t i,
                        SortCriteria criteria,
                        SortOrder order,
                        HeapSortMetrics& metrics) {
    size_t targetIndex = i;
    size_t leftChild = 2 * i + 1;
    size_t rightChild = 2 * i + 2;

    // Helper lambda to compare elements based on sort order
    auto shouldSwap = [&](int childKey, int parentKey) -> bool {
        metrics.comparisons++;
        if (order == SortOrder::Ascending) {
            // Max-Heap: child should replace parent if child > parent
            return childKey > parentKey;
        } else {
            // Min-Heap: child should replace parent if child < parent
            return childKey < parentKey;
        }
    };

    // Check if left child violates heap invariant
    if (leftChild < n) {
        int leftKey = arr[leftChild].getKey(criteria);
        int targetKey = arr[targetIndex].getKey(criteria);
        if (shouldSwap(leftKey, targetKey)) {
            targetIndex = leftChild;
        }
    }

    // Check if right child violates heap invariant
    if (rightChild < n) {
        int rightKey = arr[rightChild].getKey(criteria);
        int targetKey = arr[targetIndex].getKey(criteria);
        if (shouldSwap(rightKey, targetKey)) {
            targetIndex = rightChild;
        }
    }

    // If targetIndex changed, swap and continue sifting down recursively or iteratively
    if (targetIndex != i) {
        std::swap(arr[i], arr[targetIndex]);
        metrics.swaps++;
        siftDown(arr, n, targetIndex, criteria, order, metrics);
    }
}

void HeapSort::buildHeap(std::vector<Movie>& arr,
                         SortCriteria criteria,
                         SortOrder order,
                         HeapSortMetrics& metrics) {
    size_t n = arr.size();
    if (n <= 1) return;

    // Start from the last internal node and sift down to root
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

    // Phase 1: Build the heap
    buildHeap(arr, criteria, order, metrics);

    // Phase 2: Successively extract the root and sift down
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
