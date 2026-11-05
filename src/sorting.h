#ifndef MOVIERANKER_SORTING_H
#define MOVIERANKER_SORTING_H
#include "Movie.h"

#pragma once
#include "Movie.h"


enum class sortingKey { weightedScore, releaseYear };
enum class sortingOrder { ascending, descending };

double getValue(const Movie& movie, sortingKey key, sortingOrder order);

void quickSort(std::vector<Movie>& movies, sortingKey key, sortingOrder order);

void mergeSort(std::vector<Movie>& movies, sortingKey key, sortingOrder order);


// some example comparators for sorting movies by different criteria
inline bool scoreDesc(const Movie& a, const Movie& b) {
    return a.weighted_score > b.weighted_score;
}

inline bool scoreAsc(const Movie& a, const Movie& b) {
    return a.weighted_score < b.weighted_score;
}

inline bool yearDesc(const Movie& a, const Movie& b) {
    return a.release_year > b.release_year;
}

inline bool yearAsc(const Movie& a, const Movie& b) {
    return a.release_year < b.release_year;
}


#endif
