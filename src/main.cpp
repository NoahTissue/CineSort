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

// CineSort: Group 99 (Noah, Erik, Fareed)
int main(int argc, char* argv[]) {
    using namespace CineSort;

    UI::displayBanner();

    // Noah's data loader
    std::string datasetPath = "data/movies_cleaned.tsv";
    if (argc > 1) {
        datasetPath = argv[1];
    }

    std::vector<Movie> masterDataset;
    std::cout << "Loading dataset from " << datasetPath << "...\n";

    if (!MovieDataLoader::loadFromTSV(datasetPath, masterDataset)) {
        std::cerr << "Could not open dataset. Run 'python data/download_dataset.py' to generate it.\n";
        return 1;
    }

    // Noah's menu
    SortCriteria criteria = UI::promptSortCriteria();
    SortOrder order = UI::promptSortOrder();

    // Make two copies of the movies to test each algorithm independently
    std::vector<Movie> heapDataset = masterDataset;
    std::vector<Movie> radixDataset = masterDataset;

    // 1. Heap Sort
    std::cout << "\nRunning Heap Sort...\n";
    HeapSortMetrics heapMetrics = HeapSort::sort(heapDataset, criteria, order);
    bool heapValid = Benchmark::verifySorted(heapDataset, criteria, order);
    std::cout << "Completed in " << heapMetrics.elapsedMilliseconds << " ms "
              << "(Verification: " << (heapValid ? "PASSED" : "FAILED") << ")\n";

    // 2. Radix Sort
    std::cout << "\nRunning Radix Sort...\n";
    RadixSortMetrics radixMetrics = RadixSort::sort(radixDataset, criteria, order);
    bool radixValid = Benchmark::verifySorted(radixDataset, criteria, order);
    std::cout << "Completed in " << radixMetrics.elapsedMilliseconds << " ms "
              << "(Verification: " << (radixValid ? "PASSED" : "FAILED") << ")\n";

    // 3. Comparison Summary
    Benchmark::printComparison(heapMetrics, radixMetrics, masterDataset.size(), criteria);

    // 4. Show top 10 movies from the sorted results
    UI::displayTopMovies(heapDataset, 10, criteria);

    return 0;
}
