#include "UI.hpp"
#include <iostream>
#include <iomanip>
#include <limits>

namespace CineSort {

void UI::displayBanner() {
    std::cout << "========================================================================\n"
              << "       ___ _            ____             _   \n"
              << "      / __(_)_ __   ___/ ___|  ___  _ __| |_ \n"
              << "     / /  | | '_ \\ / _ \\___ \\ / _ \\| '__| __|\n"
              << "    / /___| | | | |  __/___) | (_) | |  | |_ \n"
              << "    \\____/|_|_| |_|\\___|____/ \\___/|_|   \\__|\n"
              << "  Empirical Comparison: Heap Sort vs. Radix Sort on IMDb Movies\n"
              << "  Course: COP3530 - Project 2b | Group 99 (Noah, Erik, Fareed)\n"
              << "========================================================================\n\n";
}

SortCriteria UI::promptSortCriteria() {
    while (true) {
        std::cout << "Select Movie Attribute to Sort By:\n"
                  << "  [1] Release Year (startYear)\n"
                  << "  [2] Runtime in Minutes (runtimeMinutes)\n"
                  << "  [3] Total User Rating Votes (numVotes)\n"
                  << "Enter selection (1-3): ";

        int choice;
        if (std::cin >> choice) {
            if (choice >= 1 && choice <= 3) {
                return static_cast<SortCriteria>(choice);
            }
        }

        // Check if stdin reached End-Of-File (e.g. user pressed Ctrl+C/Ctrl+D or empty pipe)
        if (std::cin.eof()) {
            std::cout << "\n[Notice] Input stream closed (EOF). Exiting program.\n";
            std::exit(0);
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "[Invalid input] Please enter 1, 2, or 3.\n\n";
    }
}

SortOrder UI::promptSortOrder() {
    while (true) {
        std::cout << "\nSelect Sort Direction:\n"
                  << "  [1] Ascending  (Lowest to Highest)\n"
                  << "  [2] Descending (Highest to Lowest)\n"
                  << "Enter selection (1-2): ";

        int choice;
        if (std::cin >> choice) {
            if (choice == 1 || choice == 2) {
                return static_cast<SortOrder>(choice);
            }
        }

        // Check if stdin reached End-Of-File
        if (std::cin.eof()) {
            std::cout << "\n[Notice] Input stream closed (EOF). Exiting program.\n";
            std::exit(0);
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "[Invalid input] Please enter 1 or 2.\n";
    }
}

void UI::displayTopMovies(const std::vector<Movie>& arr,
                          size_t count,
                          SortCriteria criteria) {
    size_t limit = (count < arr.size()) ? count : arr.size();

    std::cout << "\n--- Top " << limit << " Movies Sorted by " 
              << criteriaToString(criteria) << " ---\n";
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
