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
 * @brief Application entry point and benchmarking coordinator for CineSort.
 * 
 * Course: COP3530 - Data Structures and Algorithms (Project 2b)
 * Group:  99 (Noah Techoueyres, Erik Woods, Fareed Zaki)
 */

int main(int argc, char* argv[]) {
    using namespace CineSort;

    UI::displayBanner();

    // 1. Dataset Loading
    std::string datasetPath = "data/movies_cleaned.tsv";
    if (argc > 1) {
        datasetPath = argv[1];
    }

    std::vector<Movie> masterDataset;
    std::cout << "[System] Checking for dataset at: " << datasetPath << " ...\n";

    if (!MovieDataLoader::loadFromTSV(datasetPath, masterDataset)) {
        std::cout << "[System Notice] Real IMDb dataset not found or unreadable.\n"
                  << "               Generating 120,000 synthetic records for instant testing...\n";
        MovieDataLoader::generateMockDataset(masterDataset, 120000);
    }

    std::cout << "[System Ready] " << masterDataset.size() << " records loaded in memory.\n\n";

    bool keepRunning = true;
    while (keepRunning) {
        // 2. Interactive Selection
        SortCriteria criteria = UI::promptSortCriteria();
        SortOrder order = UI::promptSortOrder();

        std::cout << "\n[Running Benchmark] Preparing identical copies of " 
                  << masterDataset.size() << " movie records...\n";

        // Create identical independent copies to ensure fair benchmarking
        std::vector<Movie> heapDataset = masterDataset;
        std::vector<Movie> radixDataset = masterDataset;

        // 3. Heap Sort Execution
        std::cout << "-> Executing In-Place Heap Sort (O(n log n))...\n";
        HeapSortMetrics heapMetrics = HeapSort::sort(heapDataset, criteria, order);
        bool heapValid = Benchmark::verifySorted(heapDataset, criteria, order);
        std::cout << "   Completed in " << heapMetrics.elapsedMilliseconds << " ms. "
                  << "Verification: " << (heapValid ? "[PASSED]" : "[FAILED]") << "\n";

        // 4. Radix Sort Execution
        std::cout << "-> Executing Stable LSD Radix Sort (O(d * (n + k)))...\n";
        RadixSortMetrics radixMetrics = RadixSort::sort(radixDataset, criteria, order);
        bool radixValid = Benchmark::verifySorted(radixDataset, criteria, order);
        std::cout << "   Completed in " << radixMetrics.elapsedMilliseconds << " ms. "
                  << "Verification: " << (radixValid ? "[PASSED]" : "[FAILED]") << "\n";

        // 5. Output Summary & Comparison
        Benchmark::printComparison(heapMetrics, radixMetrics, masterDataset.size(), criteria);

        // 6. Display Top 10 Movies
        UI::displayTopMovies(heapDataset, 10, criteria);

        // 7. Loop or Exit
        std::cout << "\nBenchmark another attribute? (y/n): ";
        char choice;
        if (std::cin >> choice && (choice == 'y' || choice == 'Y')) {
            std::cout << "\n" << std::string(75, '=') << "\n\n";
        } else {
            keepRunning = false;
        }
    }

    std::cout << "\nThank you for using CineSort! Exiting.\n";
    return 0;
}
