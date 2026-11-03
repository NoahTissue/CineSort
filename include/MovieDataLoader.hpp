#pragma once

#include <vector>
#include <string>
#include "Movie.hpp"

/**
 * @file MovieDataLoader.hpp
 * @brief TSV parser and dataset loader for IMDb records.
 * 
 * Assigned to: Noah Techoueyres (Group 99)
 * 
 * Responsibilities:
 * - Stream tab-separated IMDb datasets (title.basics / title.ratings).
 * - Parse and sanitize fields, safely handling missing ("\N") values.
 * - Verify that the dataset satisfies the COP3530 requirement of >= 100,000 rows.
 * - Provide a built-in mock generator for instant compilation testing.
 */

namespace CineSort {

class MovieDataLoader {
public:
    /**
     * @brief Parses a tab-delimited TSV file into a vector of Movie records.
     * 
     * Expected TSV column structure:
     * tconst \t primaryTitle \t startYear \t runtimeMinutes \t numVotes
     * 
     * @param filepath Relative or absolute path to the .tsv file.
     * @param outMovies Destination vector to populate with valid Movie entries.
     * @param maxRows Maximum rows to read (0 = unlimited).
     * @return true if successfully loaded >= 100,000 valid records (or all available), false on failure.
     */
    static bool loadFromTSV(const std::string& filepath,
                           std::vector<Movie>& outMovies,
                           size_t maxRows = 0);

    /**
     * @brief Generates synthetic movie records for offline testing and verification.
     * Useful when the large TSV is not yet downloaded or in testing pipelines.
     * 
     * @param outMovies Destination vector to populate.
     * @param count Number of mock entries to generate (defaults to 120,000 to meet 100k+ requirement).
     */
    static void generateMockDataset(std::vector<Movie>& outMovies, size_t count = 120000);
};

} // namespace CineSort
