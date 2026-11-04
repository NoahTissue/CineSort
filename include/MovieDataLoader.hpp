#pragma once

#include <vector>
#include <string>
#include "Movie.hpp"

namespace CineSort {

// Noah: Reads and cleans the IMDb TSV file into memory
class MovieDataLoader {
public:
    static bool loadFromTSV(const std::string& filepath,
                           std::vector<Movie>& outMovies,
                           size_t maxRows = 0);
};

} // namespace CineSort
