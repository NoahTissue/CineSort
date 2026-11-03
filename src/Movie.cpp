#include "Movie.hpp"
#include <iomanip>

namespace CineSort {

Movie::Movie()
    : tconst(""), primaryTitle(""), startYear(0), runtimeMinutes(0), numVotes(0) {}

Movie::Movie(std::string id, std::string title, int year, int runtime, int votes)
    : tconst(std::move(id)),
      primaryTitle(std::move(title)),
      startYear(year),
      runtimeMinutes(runtime),
      numVotes(votes) {}

int Movie::getKey(SortCriteria criteria) const {
    switch (criteria) {
        case SortCriteria::Year:    return startYear;
        case SortCriteria::Runtime: return runtimeMinutes;
        case SortCriteria::Votes:   return numVotes;
        default:                    return 0;
    }
}

void Movie::printRow(int rank) const {
    if (rank > 0) {
        std::cout << std::setw(4) << rank << " | ";
    }
    
    // Truncate title if longer than 36 characters for terminal alignment
    std::string displayTitle = primaryTitle;
    if (displayTitle.length() > 36) {
        displayTitle = displayTitle.substr(0, 33) + "...";
    }

    std::cout << std::left << std::setw(10) << tconst << " | "
              << std::left << std::setw(36) << displayTitle << " | "
              << std::right << std::setw(6) << startYear << " | "
              << std::right << std::setw(7) << runtimeMinutes << "m | "
              << std::right << std::setw(10) << numVotes
              << std::endl;
}

} // namespace CineSort
