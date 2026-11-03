#pragma once

#include <string>

/**
 * @file Common.hpp
 * @brief Common enums, constants, and utilities for CineSort.
 * 
 * Project: CineSort - Comparing Heap Sort and Radix Sort on IMDb Movies
 * Course:  COP3530 - Data Structures and Algorithms (Project 2b)
 * Team:    Group 99 (Noah Techoueyres, Erik Woods, Fareed Zaki)
 */

namespace CineSort {

/**
 * @enum SortCriteria
 * @brief Specifies which IMDb movie attribute is used as the sorting key.
 */
enum class SortCriteria {
    Year = 1,      ///< Sort by movie release year (startYear)
    Runtime = 2,   ///< Sort by movie runtime in minutes (runtimeMinutes)
    Votes = 3      ///< Sort by total user rating votes on IMDb (numVotes)
};

/**
 * @enum SortOrder
 * @brief Specifies ascending or descending order.
 */
enum class SortOrder {
    Ascending = 1,
    Descending = 2
};

/**
 * @brief Converts SortCriteria enum to human-readable string.
 */
inline std::string criteriaToString(SortCriteria criteria) {
    switch (criteria) {
        case SortCriteria::Year:    return "Release Year";
        case SortCriteria::Runtime: return "Runtime (Minutes)";
        case SortCriteria::Votes:   return "Number of Votes";
        default:                    return "Unknown";
    }
}

/**
 * @brief Converts SortOrder enum to human-readable string.
 */
inline std::string orderToString(SortOrder order) {
    switch (order) {
        case SortOrder::Ascending:  return "Ascending";
        case SortOrder::Descending: return "Descending";
        default:                    return "Unknown";
    }
}

} // namespace CineSort
