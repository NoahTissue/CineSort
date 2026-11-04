#pragma once

#include <vector>
#include "Movie.hpp"
#include "Common.hpp"

namespace CineSort {

// Noah: Simple terminal menu and display helpers
class UI {
public:
    static void displayBanner();
    static SortCriteria promptSortCriteria();
    static SortOrder promptSortOrder();
    static void displayTopMovies(const std::vector<Movie>& arr, size_t count = 10, SortCriteria criteria = SortCriteria::Year);
};

} // namespace CineSort
