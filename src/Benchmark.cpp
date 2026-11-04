#include "Benchmark.hpp"
#include <iostream>
#include <iomanip>

namespace CineSort {

bool Benchmark::verifySorted(const std::vector<Movie>& arr,
                            SortCriteria criteria,
                            SortOrder order) {
    if (arr.size() <= 1) return true;

    for (size_t i = 0; i < arr.size() - 1; ++i) {
        int k1 = arr[i].getKey(criteria);
        int k2 = arr[i + 1].getKey(criteria);

        if (order == SortOrder::Ascending && k1 > k2) {
            std::cerr << "Verification error at index " << i << ": " << k1 << " > " << k2 << std::endl;
            return false;
        } else if (order == SortOrder::Descending && k1 < k2) {
            std::cerr << "Verification error at index " << i << ": " << k1 << " < " << k2 << std::endl;
            return false;
        }
    }
    return true;
}

void Benchmark::printComparison(const HeapSortMetrics& heapM,
                                const RadixSortMetrics& radixM,
                                size_t datasetSize,
                                SortCriteria criteria) {
    std::cout << "\n--- Performance Summary ---\n"
              << "Dataset Size:   " << datasetSize << " movies\n"
              << "Sort Attribute: " << criteriaToString(criteria) << "\n"
              << "--------------------------------------------------------\n"
              << std::left << std::setw(20) << "Metric" 
              << std::left << std::setw(20) << "Heap Sort" 
              << std::left << std::setw(20) << "Radix Sort\n"
              << "--------------------------------------------------------\n"
              << std::left << std::setw(20) << "Time (ms):"
              << std::left << std::setw(20) << std::fixed << std::setprecision(2) << heapM.elapsedMilliseconds
              << std::left << std::setw(20) << std::fixed << std::setprecision(2) << radixM.elapsedMilliseconds << "\n"
              << std::left << std::setw(20) << "Space:"
              << std::left << std::setw(20) << "O(1)"
              << std::left << std::setw(20) << "O(n)\n"
              << "--------------------------------------------------------\n\n";
}

} // namespace CineSort
