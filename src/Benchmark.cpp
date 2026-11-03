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
            std::cerr << "[Verification Error] Inversion at index " << i 
                      << ": " << k1 << " > " << k2 << std::endl;
            return false;
        } else if (order == SortOrder::Descending && k1 < k2) {
            std::cerr << "[Verification Error] Inversion at index " << i 
                      << ": " << k1 << " < " << k2 << std::endl;
            return false;
        }
    }
    return true;
}

void Benchmark::printComparison(const HeapSortMetrics& heapM,
                                const RadixSortMetrics& radixM,
                                size_t datasetSize,
                                SortCriteria criteria) {
    std::cout << "\n"
              << "========================================================================\n"
              << "               CineSort Algorithmic Performance Summary                 \n"
              << "========================================================================\n"
              << " Dataset Size:       " << datasetSize << " IMDb movie records\n"
              << " Sort Attribute:     " << criteriaToString(criteria) << "\n"
              << "------------------------------------------------------------------------\n"
              << std::left << std::setw(26) << " Metric" 
              << std::left << std::setw(24) << " Heap Sort (In-Place)" 
              << std::left << std::setw(24) << " Radix Sort (LSD)" << "\n"
              << "------------------------------------------------------------------------\n";

    std::cout << std::left << std::setw(26) << " Execution Time (ms):"
              << std::left << std::setw(24) << std::fixed << std::setprecision(2) << heapM.elapsedMilliseconds
              << std::left << std::setw(24) << std::fixed << std::setprecision(2) << radixM.elapsedMilliseconds
              << "\n";

    std::cout << std::left << std::setw(26) << " Theoretical Time:"
              << std::left << std::setw(24) << "O(n log n)"
              << std::left << std::setw(24) << "O(d * (n + k))"
              << "\n";

    std::cout << std::left << std::setw(26) << " Auxiliary Space:"
              << std::left << std::setw(24) << "O(1) [0 extra bytes]"
              << std::left << std::setw(24) << "O(n) [~" + std::to_string(radixM.auxiliaryMemoryBytes / (1024 * 1024)) + " MB]"
              << "\n";

    std::cout << std::left << std::setw(26) << " Comparisons:"
              << std::left << std::setw(24) << heapM.comparisons
              << std::left << std::setw(24) << "N/A (Non-comparison)"
              << "\n";

    std::cout << std::left << std::setw(26) << " Swaps / Passes:"
              << std::left << std::setw(24) << (std::to_string(heapM.swaps) + " swaps")
              << std::left << std::setw(24) << (std::to_string(radixM.digitPasses) + " digit passes")
              << "\n";

    std::cout << "------------------------------------------------------------------------\n";

    // Calculate speedup ratio
    if (radixM.elapsedMilliseconds > 0.0 && heapM.elapsedMilliseconds > 0.0) {
        if (heapM.elapsedMilliseconds > radixM.elapsedMilliseconds) {
            double speedup = heapM.elapsedMilliseconds / radixM.elapsedMilliseconds;
            std::cout << " Result: Radix Sort was " << std::fixed << std::setprecision(2) 
                      << speedup << "x faster than Heap Sort.\n";
        } else {
            double speedup = radixM.elapsedMilliseconds / heapM.elapsedMilliseconds;
            std::cout << " Result: Heap Sort was " << std::fixed << std::setprecision(2) 
                      << speedup << "x faster than Radix Sort.\n";
        }
    }
    std::cout << "========================================================================\n\n";
}

} // namespace CineSort
