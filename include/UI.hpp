#pragma once

#include <vector>
#include "Movie.hpp"
#include "Common.hpp"

/**
 * @file UI.hpp
 * @brief Terminal User Interface for CineSort.
 * 
 * Assigned to: Noah Techoueyres (Group 99)
 */

namespace CineSort {

class UI {
public:
    /**
     * @brief Displays ASCII banner and course information.
     */
    static void displayBanner();

    /**
     * @brief Prompts user to select an IMDb sorting attribute.
     */
    static SortCriteria promptSortCriteria();

    /**
     * @brief Prompts user to select sorting order (Ascending / Descending).
     */
    static SortOrder promptSortOrder();

    /**
     * @brief Renders a formatted tabular view of the top N movie records.
     */
    static void displayTopMovies(const std::vector<Movie>& arr,
                                 size_t count = 10,
                                 SortCriteria criteria = SortCriteria::Year);
};

} // namespace CineSort
