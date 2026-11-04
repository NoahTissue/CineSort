#pragma once

#include <string>
#include "Common.hpp"

namespace CineSort {

// Represents one movie row from IMDb
struct Movie {
    std::string tconst;
    std::string primaryTitle;
    int startYear;
    int runtimeMinutes;
    int numVotes;

    Movie();
    Movie(std::string id, std::string title, int year, int runtime, int votes);

    // Returns the integer key based on the user's sort choice
    int getKey(SortCriteria criteria) const;
    void printRow(int rank = -1) const;
};

} // namespace CineSort
