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

    // Erik's heap sort
    std::cout << "\nRunning Heap Sort (Erik)...\n";
    HeapSortMetrics heapMetrics = HeapSort::sort(heapDataset, criteria, order);
    if (heapMetrics.elapsedMilliseconds > 0.0) {
        std::cout << "Completed in " << heapMetrics.elapsedMilliseconds << " ms\n";
    }

    // Fareed's radix sort
    std::cout << "\nRunning Radix Sort (Fareed)...\n";
    RadixSortMetrics radixMetrics = RadixSort::sort(radixDataset, criteria, order);
    if (radixMetrics.elapsedMilliseconds > 0.0) {
        std::cout << "Completed in " << radixMetrics.elapsedMilliseconds << " ms\n";
    }

    // Show top 10 movies from the sorted results
    if (radixMetrics.elapsedMilliseconds > 0.0) {
        UI::displayTopMovies(radixDataset, 10, criteria);
    } else if (heapMetrics.elapsedMilliseconds > 0.0) {
        UI::displayTopMovies(heapDataset, 10, criteria);
    } else {
        UI::displayTopMovies(masterDataset, 10, criteria);
    }

    return 0;
}
