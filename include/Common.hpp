#pragma once

#include <string>

namespace CineSort {

// Attribute choices for sorting
enum class SortCriteria {
    Year = 1,
    Runtime = 2,
    Votes = 3
};

enum class SortOrder {
    Ascending = 1,
    Descending = 2
};

inline std::string criteriaToString(SortCriteria criteria) {
    switch (criteria) {
        case SortCriteria::Year:    return "Release Year";
        case SortCriteria::Runtime: return "Runtime (Minutes)";
        case SortCriteria::Votes:   return "Number of Votes";
        default:                    return "Unknown";
    }
}

inline std::string orderToString(SortOrder order) {
    return (order == SortOrder::Ascending) ? "Ascending" : "Descending";
}

} // namespace CineSort
