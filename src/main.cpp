#include <iostream>
#include <vector>
#include <string>

#include "Common.hpp"
#include "Movie.hpp"
#include "MovieDataLoader.hpp"
#include "HeapSort.hpp"
#include "RadixSort.hpp"
#include "Benchmark.hpp"
#include "UI.hpp"

/**
 * @file main.cpp
 * @brief CineSort entry point & coordinator.
 * 
 * Group 99:
 * - Noah Techoueyres: Data Foundation, Loader, CLI
 * - Erik Woods: Heap Sort (src/HeapSort.cpp)
 * - Fareed Zaki: Radix Sort (src/RadixSort.cpp)
 */

int main(int argc, char* argv[]) {
    using namespace CineSort;

    UI::displayBanner();

    // 1. Load Data (Noah's module)
    std::string datasetPath = "data/movies_cleaned.tsv";
    if (argc > 1) {
        datasetPath = argv[1];
    }

    std::vector<Movie> masterDataset;
    std::cout << "[DataLoader] Reading dataset: " << datasetPath << " ...\n";

    if (!MovieDataLoader::loadFromTSV(datasetPath, masterDataset)) {
        std::cerr << "[Error] Could not load dataset from " << datasetPath << "\n";
        std::cerr << "        Please run: python data/download_dataset.py\n";
        return 1;
    }

    std::cout << "[System Ready] " << masterDataset.size() << " records loaded in memory.\n\n";

    // 2. User Menu Selection (Noah's module)
    SortCriteria criteria = UI::promptSortCriteria();
    SortOrder order = UI::promptSortOrder();

    std::cout << "\n[Running Benchmark] Preparing identical copies of " 
              << masterDataset.size() << " movie records...\n";

    std::vector<Movie> heapDataset = masterDataset;
    std::vector<Movie> radixDataset = masterDataset;

    // 3. Heap Sort (Erik's module)
    std::cout << "\n-> Running Heap Sort (Assigned to Erik Woods)...\n";
    HeapSortMetrics heapMetrics = HeapSort::sort(heapDataset, criteria, order);
    if (heapMetrics.elapsedMilliseconds > 0.0) {
        bool heapValid = Benchmark::verifySorted(heapDataset, criteria, order);
        std::cout << "   Time: " << heapMetrics.elapsedMilliseconds << " ms | Verification: "
                  << (heapValid ? "[PASSED]" : "[FAILED]") << "\n";
    }

    // 4. Radix Sort (Fareed's module)
    std::cout << "\n-> Running Radix Sort (Assigned to Fareed Zaki)...\n";
    RadixSortMetrics radixMetrics = RadixSort::sort(radixDataset, criteria, order);
    if (radixMetrics.elapsedMilliseconds > 0.0) {
        bool radixValid = Benchmark::verifySorted(radixDataset, criteria, order);
        std::cout << "   Time: " << radixMetrics.elapsedMilliseconds << " ms | Verification: "
                  << (radixValid ? "[PASSED]" : "[FAILED]") << "\n";
    }

    // 5. Performance Comparison (when algorithms are implemented)
    if (heapMetrics.elapsedMilliseconds > 0.0 && radixMetrics.elapsedMilliseconds > 0.0) {
        Benchmark::printComparison(heapMetrics, radixMetrics, masterDataset.size(), criteria);
    }

    // 6. Preview First 10 Records
    std::cout << "\nDataset Preview (First 10 records):\n";
    UI::displayTopMovies(masterDataset, 10, criteria);

    std::cout << "\n[Done] Foundation code execution completed.\n";
    return 0;
}
