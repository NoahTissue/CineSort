#include "MovieDataLoader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>

namespace CineSort {

bool MovieDataLoader::loadFromTSV(const std::string& filepath,
                                 std::vector<Movie>& outMovies,
                                 size_t maxRows) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "[Error] Unable to open TSV file: " << filepath << std::endl;
        return false;
    }

    std::string line;
    // Inspect first row: if it contains "tconst", it's a header and we skip it.
    // If not, rewind to byte 0 so the while-loop can process movie #1.
    if (std::getline(file, line)) {
        if (line.find("tconst") == std::string::npos) {
            file.clear();
            file.seekg(0, std::ios::beg);
        }
    }

    outMovies.clear();
    // Reserve capacity to prevent repeated re-allocations for large datasets (100k+)
    outMovies.reserve(125000);

    size_t rowsRead = 0;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string tconst, title, yearStr, runtimeStr, votesStr;

        // IMDb TSV columns: tconst, primaryTitle, startYear, runtimeMinutes, numVotes
        if (!std::getline(ss, tconst, '\t')) continue;
        if (!std::getline(ss, title, '\t')) continue;
        if (!std::getline(ss, yearStr, '\t')) continue;
        if (!std::getline(ss, runtimeStr, '\t')) continue;
        if (!std::getline(ss, votesStr, '\t')) continue;

        // Skip rows with missing values ("\N" is IMDb's null indicator)
        if (yearStr == "\\N" || runtimeStr == "\\N" || votesStr == "\\N") {
            continue;
        }

        try {
            int year = std::stoi(yearStr);
            int runtime = std::stoi(runtimeStr);
            int votes = std::stoi(votesStr);

            // Domain sanity check: valid movie era, realistic runtimes, non-negative votes
            if (year < 1888 || year > 2030 || runtime <= 0 || runtime > 1440 || votes < 0) {
                continue;
            }

            outMovies.emplace_back(std::move(tconst), std::move(title), year, runtime, votes);
            rowsRead++;

            if (maxRows > 0 && rowsRead >= maxRows) {
                break;
            }
        } catch (const std::exception&) {
            // Skip corrupted rows
            continue;
        }
    }

    file.close();
    std::cout << "[DataLoader] Loaded " << outMovies.size() << " valid movie records from " 
              << filepath << std::endl;

    if (outMovies.size() < 100000 && maxRows == 0) {
        std::cout << "[DataLoader Warning] Dataset row count (" << outMovies.size()
                  << ") is under the COP3530 requirement of 100,000 rows." << std::endl;
    }

    return !outMovies.empty();
}

void MovieDataLoader::generateMockDataset(std::vector<Movie>& outMovies, size_t count) {
    outMovies.clear();
    outMovies.reserve(count);

    std::mt19937 rng(42); // Deterministic seed for reproducible testing
    std::uniform_int_distribution<int> yearDist(1920, 2026);
    std::uniform_int_distribution<int> runtimeDist(60, 240);
    std::uniform_int_distribution<int> votesDist(100, 2500000);

    for (size_t i = 1; i <= count; ++i) {
        std::string id = "tt" + std::to_string(1000000 + i);
        std::string title = "Movie Record #" + std::to_string(i);
        outMovies.emplace_back(id, title, yearDist(rng), runtimeDist(rng), votesDist(rng));
    }

    std::cout << "[DataLoader] Generated " << count << " mock movie records for testing." << std::endl;
}

} // namespace CineSort
