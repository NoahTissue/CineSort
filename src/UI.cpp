#include "UI.hpp"
#include <iostream>
#include <iomanip>
#include <limits>

namespace CineSort {

void UI::displayBanner() {
    std::cout << "========================================\n"
              << "  CineSort: Heap Sort vs. Radix Sort    \n"
              << "  COP3530 Project 2b - Group 99        \n"
              << "========================================\n\n";
}

SortCriteria UI::promptSortCriteria() {
    while (true) {
        std::cout << "Choose an attribute to sort by:\n"
                  << "  1. Release Year\n"
                  << "  2. Runtime (Minutes)\n"
                  << "  3. Number of Votes\n"
                  << "Selection (1-3): ";

        int choice;
        if (std::cin >> choice && choice >= 1 && choice <= 3) {
            return static_cast<SortCriteria>(choice);
        }

        if (std::cin.eof()) {
            std::exit(0);
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice, please enter 1, 2, or 3.\n\n";
    }
}

SortOrder UI::promptSortOrder() {
    while (true) {
        std::cout << "\nChoose sort order:\n"
                  << "  1. Ascending\n"
                  << "  2. Descending\n"
                  << "Selection (1-2): ";

        int choice;
        if (std::cin >> choice && (choice == 1 || choice == 2)) {
            return static_cast<SortOrder>(choice);
        }

        if (std::cin.eof()) {
            std::exit(0);
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice, please enter 1 or 2.\n";
    }
}

void UI::displayTopMovies(const std::vector<Movie>& arr, size_t count, SortCriteria criteria) {
    size_t limit = (count < arr.size()) ? count : arr.size();

    std::cout << "\nTop " << limit << " movies sorted by " << criteriaToString(criteria) << ":\n";
    std::cout << "Rank | "
              << std::left << std::setw(10) << "IMDb ID" << " | "
              << std::left << std::setw(36) << "Title" << " | "
              << std::right << std::setw(6) << "Year" << " | "
              << std::right << std::setw(8) << "Runtime" << " | "
              << std::right << std::setw(10) << "Votes" << "\n";
    std::cout << std::string(75, '-') << "\n";

    for (size_t i = 0; i < limit; ++i) {
        arr[i].printRow(static_cast<int>(i + 1));
    }
    std::cout << std::string(75, '-') << "\n";
}

} // namespace CineSort
