# CineSort Architecture & Development Guide
**COP3530 Data Structures and Algorithms — Project 2b**  
**Group 99**: Noah Techoueyres, Erik Woods, Fareed Zaki

---

## 1. Project Goal
Compare the empirical performance, memory footprint, and theoretical characteristics of:
- **Heap Sort**: In-place, comparison-based sort ($\Theta(n \log n)$ time, $O(1)$ auxiliary space).
- **LSD Radix Sort**: Linear-time, non-comparison sort ($O(d \cdot (n + k))$ time, $O(n)$ auxiliary space).

Both algorithms are executed across $\ge 100,000$ IMDb movie titles on three selectable numeric keys:
1. Release Year (`startYear`)
2. Runtime in Minutes (`runtimeMinutes`)
3. Total User Votes (`numVotes`)

---

## 2. Canvas Rubric & Policy Compliance

| Requirement | Rule | Implementation in CineSort |
| :--- | :--- | :--- |
| **From Scratch** | NO `std::sort`, NO `std::priority_queue`. (-25% per violation) | Hand-crafted binary heap with 0-based array index arithmetic; hand-crafted 10-bucket counting sort passes. |
| **Dataset Size** | Minimum 100,000 rows. | 120,000 IMDb movie records. |
| **Individual Contribution** | $\ge 15\%$ commits/lines of code per team member. | Noah (DataLoader, UI, Models), Erik (HeapSort, Verifier), Fareed (RadixSort, Benchmark). |
| **Deliverables** | Source code, 5-minute video walkthrough, 5-page PDF report. | Modular structure ready for screencast and LaTeX/Word report template. |

---

## 3. Team Member Modules

### Noah Techoueyres
- `include/Movie.hpp` & `src/Movie.cpp`
- `include/MovieDataLoader.hpp` & `src/MovieDataLoader.cpp`
- `include/UI.hpp` & `src/UI.cpp`
- Branch: `feature/data-loader-ui`

### Erik Woods
- `include/HeapSort.hpp` & `src/HeapSort.cpp`
- Benchmark verification subroutines
- Branch: `feature/heap-sort`

### Fareed Zaki
- `include/RadixSort.hpp` & `src/RadixSort.cpp`
- `include/Benchmark.hpp` & `src/Benchmark.cpp`
- Branch: `feature/radix-sort`

---

## 4. Build & Execution

### Using Make (or mingw32-make)
```bash
make
./bin/cinesort.exe
```

### Direct GCC Compilation
```bash
g++ -std=c++20 src/*.cpp -Iinclude -O2 -o bin/cinesort.exe
./bin/cinesort.exe
```
