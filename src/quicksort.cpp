#include <utility>
#include <vector>
#include <random>

#include "sorting.h"
#include "Movie.h"

namespace {
    std::mt19937 rng(3530);

    std::pair<int, int> partition(std::vector<Movie>& movies, int lo, int hi, sortingKey key, sortingOrder order) {
        int i = lo;
        int lt = lo;
        int gt = hi;
        int randNum = std::uniform_int_distribution<int>(lo, hi)(rng);
        double pivot = getValue(movies[randNum], key, order);

        while (i <= gt) {
            double val = getValue(movies[i], key, order);
            if (val < pivot) {
                std::swap(movies[i], movies[lt]);
                i++;
                lt++;
            }
            else if (val > pivot) {
                std::swap(movies[i], movies[gt]);
                gt--;
            }
            else { i++; }
        }
        return {lt, gt};
    }

    void sortRange(std::vector<Movie>& movies, int lo, int hi, sortingKey key, sortingOrder order) {
        while (lo < hi) {
            std::pair<int, int> lt_gt = partition(movies, lo, hi, key, order);
            int lt = lt_gt.first;
            int gt = lt_gt.second;
            if ((lt - lo) > (hi - gt)) {
                sortRange(movies, gt + 1, hi, key, order);
                hi = lt - 1;
            } else {
                sortRange(movies, lo, lt - 1, key, order);
                lo = gt + 1;
            }
        }
    }
}

void quickSort(std::vector<Movie>& movies, sortingKey key, sortingOrder order) {
    sortRange(movies, 0, static_cast<int>(movies.size()) - 1, key, order);
}