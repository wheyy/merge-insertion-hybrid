// Benchmark driver CLI.
//
// Usage: ./benchmark <ins|merge|hybrid> <n> <S> <seed>
//
// Generates a random array of `n` ints in [1, MAX_VALUE] using a
// std::mt19937 seeded with `seed`, sorts it with the chosen algorithm,
// and prints one CSV line to stdout:
//
//   algo,n,S,seed,comparisons,time_ms
//
// `S` is ignored (printed as 0) for `ins` and `merge`. Only the sort call
// itself is timed; array generation is excluded.

#include "insertion_sort.hpp"
#include "merge_sort.hpp"
#include "hybrid_sort.hpp"

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <random>
#include <string>
#include <vector>

namespace {
constexpr int MAX_VALUE = 1000000000;
}

int main(int argc, char** argv) {
    if (argc != 5) {
        std::fprintf(stderr, "usage: %s <ins|merge|hybrid> <n> <S> <seed>\n", argv[0]);
        return 1;
    }

    std::string algo = argv[1];
    long n = std::atol(argv[2]);
    int S = std::atoi(argv[3]);
    unsigned int seed = static_cast<unsigned int>(std::atol(argv[4]));

    if (n <= 0) {
        std::fprintf(stderr, "n must be positive\n");
        return 1;
    }

    std::vector<int> arr(n);
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(1, MAX_VALUE);
    for (long i = 0; i < n; ++i) {
        arr[i] = dist(rng);
    }

    long long comparisons = 0;
    int reportedS = 0;

    auto start = std::chrono::steady_clock::now();
    if (algo == "ins") {
        comparisons = insertionSort(arr.data(), 0, static_cast<int>(n - 1));
    } else if (algo == "merge") {
        comparisons = mergeSort(arr.data(), 0, static_cast<int>(n - 1));
    } else if (algo == "hybrid") {
        comparisons = hybridSort(arr.data(), 0, static_cast<int>(n - 1), S);
        reportedS = S;
    } else {
        std::fprintf(stderr, "unknown algorithm '%s' (expected ins|merge|hybrid)\n", algo.c_str());
        return 1;
    }
    auto end = std::chrono::steady_clock::now();
    double timeMs = std::chrono::duration<double, std::milli>(end - start).count();

    // Sanity check: verify the array is actually sorted before trusting
    // the comparison count.
    for (long i = 1; i < n; ++i) {
        if (arr[i - 1] > arr[i]) {
            std::fprintf(stderr, "ERROR: output not sorted at index %ld\n", i);
            return 2;
        }
    }

    std::printf("%s,%ld,%d,%u,%lld,%.6f\n", algo.c_str(), n, reportedS, seed, comparisons, timeMs);
    return 0;
}
