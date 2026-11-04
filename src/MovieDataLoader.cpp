#include "MovieDataLoader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

namespace CineSort {

bool MovieDataLoader::loadFromTSV(const std::string& filepath,
                                 std::vector<Movie>& outMovies,
                                 size_t maxRows) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filepath << std::endl;
        return false;
    }

    std::string line;
    // Skip header line if it contains "tconst"
    if (std::getline(file, line)) {
        if (line.find("tconst") == std::string::npos) {
            file.clear();
            file.seekg(0, std::ios::beg);
        }
    }

    outMovies.clear();
    outMovies.reserve(125000); // Pre-allocate to prevent slow vector resizing

    size_t rowsRead = 0;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string tconst, title, yearStr, runtimeStr, votesStr;

        // Split by tabs
        if (!std::getline(ss, tconst, '\t')) continue;
        if (!std::getline(ss, title, '\t')) continue;
        if (!std::getline(ss, yearStr, '\t')) continue;
        if (!std::getline(ss, runtimeStr, '\t')) continue;
        if (!std::getline(ss, votesStr, '\t')) continue;

        // Filter out null \N values
        if (yearStr == "\\N" || runtimeStr == "\\N" || votesStr == "\\N") {
            continue;
        }

        try {
            int year = std::stoi(yearStr);
            int runtime = std::stoi(runtimeStr);
            int votes = std::stoi(votesStr);

            // Filter out invalid records
            if (year < 1888 || year > 2030 || runtime <= 0 || votes < 0) {
                continue;
            }

            outMovies.emplace_back(std::move(tconst), std::move(title), year, runtime, votes);
            rowsRead++;

            if (maxRows > 0 && rowsRead >= maxRows) {
                break;
            }
        } catch (...) {
            continue;
        }
    }

    file.close();
    std::cout << "Loaded " << outMovies.size() << " movies from " << filepath << std::endl;
    return !outMovies.empty();
}

} // namespace CineSort
