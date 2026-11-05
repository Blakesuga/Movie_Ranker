#include "benchmark.h"
#include <chrono>

double timedSort(std::vector<Movie>& movies, void (*sortFunc)(std::vector<Movie>& movies, sortingKey key, sortingOrder order), sortingKey key, sortingOrder order) {
    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    sortFunc(movies, key, order);
    std::chrono::time_point<std::chrono::steady_clock> finish = std::chrono::steady_clock::now();
    double milliseconds = std::chrono::duration<double, std::milli>(finish - start).count();
    return milliseconds;
}