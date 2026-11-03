#pragma once

#include <string>
#include <iostream>
#include "Common.hpp"

/**
 * @file Movie.hpp
 * @brief Definition of the Movie record representation.
 * 
 * Assigned to: Noah Techoueyres (Group 99)
 * 
 * Represents an entry in the IMDb dataset containing primary identifier,
 * title, year, runtime, and vote count.
 */

namespace CineSort {

struct Movie {
    std::string tconst;         ///< Unique alphanumeric IMDb title ID (e.g. "tt0111161")
    std::string primaryTitle;   ///< Display title of the movie
    int startYear;              ///< Release year (e.g. 1994)
    int runtimeMinutes;         ///< Runtime in minutes
    int numVotes;               ///< Total user rating votes on IMDb

    /**
     * @brief Default constructor initializing numeric fields to -1 or 0.
     */
    Movie();

    /**
     * @brief Parameterized constructor for a complete Movie entry.
     */
    Movie(std::string id, std::string title, int year, int runtime, int votes);

    /**
     * @brief Extracts the integer sorting key for a specified criteria.
     * @param criteria The attribute to extract (Year, Runtime, Votes).
     * @return The integer key associated with that attribute.
     */
    int getKey(SortCriteria criteria) const;

    /**
     * @brief Formats movie details as a clean, aligned single-line string.
     */
    void printRow(int rank = -1) const;
};

} // namespace CineSort
