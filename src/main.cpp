#ifndef DATA_DIR
#define DATA_DIR "data"
#endif

#include <iostream>
#include <string>
#include <vector>
#include "loader.h"
#include "interface.h"

int main()
{
    std::cout << "Loading movies...\n";

    std::vector<Movie> movies;
    try
    {
        movies = loadMovies(std::string(DATA_DIR) + "/kaggle_movie_dataset.csv");
    }
    catch (const std::exception& error)
    {
        std::cerr << "Couldn't load the movies: " << error.what() << "\n";
        return 1;
    }

    runInterface(movies);
    return 0;
}

/*
// Probably where interface will go

#ifndef DATA_DIR
#define DATA_DIR "data"
#endif

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <chrono>
#include <random>
#include "sorting.h"
#include "loader.h"
#include "benchmark.h"

int main()
{
    std::cout << "I love movies" << std::endl;

    // load movie data from CSV file
    auto movies = loadMovies(std::string(DATA_DIR) + "/kaggle_movie_dataset.csv");

    // sort by vote_average, weighted_score is still 0.0 until quick sort is completed
    const sortingKey keys[] = {sortingKey::weightedScore, sortingKey::releaseYear};
    const sortingOrder orders[] = {sortingOrder::ascending, sortingOrder::descending};

    for (auto key : keys)
    {
        for (auto order : orders)
        {
            auto mine = movies;
            auto ref = movies;

            mergeSort(mine, key, order);
            std::stable_sort(ref.begin(), ref.end(), [key, order](const Movie &a, const Movie &b)
                             { return getValue(a, key, order) < getValue(b, key, order); });

            for (size_t i = 0; i < mine.size(); ++i)
            {
                assert(mine[i].id == ref[i].id);
            }

            if (key == sortingKey::releaseYear && order == sortingOrder::descending)
            {
                assert(mine.front().release_year != 0);
            }
        }

        std::cout << "All key/order combinations match std::stable_sort\n";

        // sets up a comparator for sorting movies by weighted score in descending order via a timer
        auto timeIt = [](const char *label, std::vector<Movie> data)
        {
            auto start = std::chrono::steady_clock::now();
            mergeSort(data, sortingKey::weightedScore, sortingOrder::descending);
            auto end = std::chrono::steady_clock::now();
            std::cout << label << ": "
                      << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                      << " ms\n";
        };

        auto shuffled = movies;
        std::shuffle(shuffled.begin(), shuffled.end(), std::mt19937(42));

        // counts time it takes to sort the original and shuffled data 3 times each
        for (int run = 1; run <= 3; ++run)
        {
            timeIt("Merge sort, original order", movies);
            timeIt("Merge sort, shuffled      ", shuffled);
        }

    }
    // ONLY UNCOMMENT IF BENCHMARK RESULTS ARE ACTUALLY NEEDED
    // benchmarkResults(movies);

    return 0;
}
*/
