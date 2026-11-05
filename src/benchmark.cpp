#include "benchmark.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <utility>

namespace {
    double median(std::vector<double> timeVector) {
        std::sort(timeVector.begin(), timeVector.end());
        return timeVector[timeVector.size() / 2];
    }
}

double timedSort(std::vector<Movie>& movies, void (*sortFunc)(std::vector<Movie>& movies, sortingKey key, sortingOrder order), sortingKey key, sortingOrder order) {
    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    sortFunc(movies, key, order);
    std::chrono::time_point<std::chrono::steady_clock> finish = std::chrono::steady_clock::now();
    double milliseconds = std::chrono::duration<double, std::milli>(finish - start).count();
    return milliseconds;
}

void benchmarkResults(std::vector<Movie>& movies) {
    std::vector<Movie> shuffled = movies;
    std::shuffle(shuffled.begin(), shuffled.end(), std::mt19937(42));
    std::vector<double> quickSortTime;
    std::vector<double> quickSortShuffleTime;
    std::vector<double> mergeSortTime;
    std::vector<double> mergeSortShuffleTime;

    // Quick Sort Analysis
    for (int i = 0; i < 9; i++) {
        std::vector<Movie> movie_copy = movies;
        std::vector<Movie> shuffled_copy = shuffled;

        double time_movie = timedSort(movie_copy, quickSort, sortingKey::weightedScore, sortingOrder::descending);
        double time_shuffle = timedSort(shuffled_copy, quickSort, sortingKey::weightedScore, sortingOrder::descending);
        quickSortTime.emplace_back(time_movie);
        quickSortShuffleTime.emplace_back(time_shuffle);
    }

    // Merge Sort Analysis
    for (int i = 0; i < 9; i++) {
        std::vector<Movie> movie_copy = movies;
        std::vector<Movie> shuffled_copy = shuffled;

        double time_movie = timedSort(movie_copy, mergeSort, sortingKey::weightedScore, sortingOrder::descending);
        double time_shuffle = timedSort(shuffled_copy, mergeSort, sortingKey::weightedScore, sortingOrder::descending);
        mergeSortTime.emplace_back(time_movie);
        mergeSortShuffleTime.emplace_back(time_shuffle);
    }

    std::cout << "Median quick sort time, original order: " << median(quickSortTime) << " ms" << std::endl;
    std::cout << "Median quick sort time, shuffled order: " << median(quickSortShuffleTime) << " ms" << std::endl;
    std::cout << "Median merge sort time, original order: " << median(mergeSortTime) << " ms" << std::endl;
    std::cout << "Median merge sort time, shuffled order: " << median(mergeSortShuffleTime) << " ms" << std::endl;
}