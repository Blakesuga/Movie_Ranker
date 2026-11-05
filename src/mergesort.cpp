#include "sorting.h"
#include "mergesort.h"

void mergeSort(std::vector<Movie>& movies, sortingKey key, sortingOrder order) {
    mergeSort(movies, [key, order](const Movie& a, const Movie& b) {
        return getValue(a, key, order) < getValue(b, key, order);
    });
}

 