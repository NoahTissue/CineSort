# CineSort: Comparing Heap Sort and Radix Sort on IMDb Movies

**Course:** COP3530 - Data Structures and Algorithms (Project 2b)  
**Group:** 99  
**Team Members:**
- **Noah Techoueyres** (`NoahTissue`) — Data Loader (TSV Streaming), Model Definitions, Interactive CLI UI
- **Erik Woods** — From-Scratch In-Place Heap Sort, Heapify / Sift-Down Engine, Verification
- **Fareed Zaki** (`Gliz935`) — From-Scratch LSD Radix Sort, Counting Sort Subroutines, Benchmark Instrumentation

---

## Overview

CineSort is a high-performance C++20 empirical benchmarking application designed to compare two fundamental sorting paradigms on large-scale, real-world movie datasets ($100,000+$ records from IMDb):

1. **Heap Sort**: Comparison-based, in-place sort with guaranteed $\Theta(n \log n)$ time complexity and $O(1)$ auxiliary space.
2. **Radix Sort (LSD)**: Non-comparison, stable distribution sort running in $O(d \cdot (n + k))$ time complexity with $O(n)$ auxiliary memory.

Users can interactively choose between multiple movie attributes to sort:
- **Release Year** (`startYear`)
- **Runtime in Minutes** (`runtimeMinutes`)
- **Total User Rating Votes** (`numVotes`)

---

## Project Structure

```text
CineSort/
├── .gitignore                     # Ignores build outputs and large raw data
├── CMakeLists.txt                 # CMake configuration for IDEs/graders
├── Makefile                       # Cross-platform Makefile
├── README.md                      # Project overview and instructions
├── data/
│   ├── download_dataset.py        # Python script to download & clean 120k IMDb records
│   └── README.md                  # Dataset specifications and format
├── docs/
│   ├── ARCHITECTURE.md            # Architectural blueprint and Canvas compliance notes
│   └── COURSE_GITHUB_GUIDE.md     # COP3530 course GitHub guide
├── include/
│   ├── Benchmark.hpp              # Timing and metrics comparison table
│   ├── Common.hpp                 # Sorting enums and shared constants
│   ├── HeapSort.hpp               # In-place Heap Sort declaration
│   ├── Movie.hpp                  # Movie struct with IMDb fields
│   ├── MovieDataLoader.hpp        # Fast TSV streamer and fallback mock generator
│   ├── RadixSort.hpp              # LSD Radix Sort declaration
│   └── UI.hpp                     # Interactive CLI menus and top 10 display
└── src/
    ├── Benchmark.cpp              # Timing & sortedness verification
    ├── HeapSort.cpp               # From-scratch Heap Sort implementation
    ├── Movie.cpp                  # Movie representation and formatting
    ├── MovieDataLoader.cpp        # TSV parsing & data handling
    ├── RadixSort.cpp              # From-scratch LSD Radix Sort implementation
    ├── UI.cpp                     # Console formatting and menus
    └── main.cpp                   # Application entry point and orchestrator
```

---

## Build and Run

### Prerequisites
- C++20 compliant compiler (`g++` 10+, `clang` 11+, or MSVC 2019+)
- (Optional) `make` or `mingw32-make` / `cmake`

### Compilation via Makefile
```bash
mingw32-make
./bin/cinesort.exe
```

### Direct Compilation with G++
```bash
# Create bin directory
mkdir bin

# Compile all source files
g++ -std=c++20 src/*.cpp -Iinclude -O2 -static -static-libgcc -static-libstdc++ -o bin/cinesort.exe

# Execute
./bin/cinesort.exe
```

### Dataset Setup
To download and prepare the real IMDb dataset (120,000+ rows):
```bash
python data/download_dataset.py
```
*Note: If no dataset is detected on launch, CineSort automatically generates 120,000 synthetic records so the program can be run and tested immediately.*
