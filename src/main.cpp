//Probably where interface will go

#ifndef DATA_DIR
#define DATA_DIR "data"
#endif

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include "sorting.h"
#include "csv.h"
#include "loader.h"
#include "mergesort.h"
#include <chrono>
#include <random>

int main() {
    std::cout << "I love movies" << std::endl;


    // load movie data from CSV file
    auto movies = loadMovies(std::string(DATA_DIR) + "/kaggle_movie_dataset.csv");
    
    // sort by vote_average, weighted_score is still 0.0 until quick sort is completed
    auto byAvgDesc = [](const Movie& a, const Movie& b) {
        return a.vote_average > b.vote_average;
    };

    // sets up a comparator for sorting movies by weighted score in descending order via a timer
    auto timeIt = [&](const char* label, std::vector<Movie> data) {
        auto start = std::chrono::steady_clock::now();
        mergeSortRec(data, byAvgDesc);
        auto end = std::chrono::steady_clock::now();
        std::cout << label << ": "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                  << " ms\n";
    };      
    
    auto shuffled = movies;
    std::shuffle(shuffled.begin(), shuffled.end(), std::mt19937(42));

    // counts time it takes to sort the original and shuffled data 3 times each
    for (int run = 1; run <= 3; ++run) {
        timeIt("Merge sort, original order", movies);
        timeIt("Merge sort, shuffled      ", shuffled);
    }

    inline void mergeSort(std::vector<Movie>& a, sortingKey key, sortingOrder order) {
        mergeSort(a, [key, order](const Movie& x, const Movie& y) {
            return getValue(x, key, order) < getValue(y, key, order);
                
        });
    }

    return 0;
}

