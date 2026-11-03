#ifndef MOVIERANKER_SORTING_H
#define MOVIERANKER_SORTING_H

#pragma once
#include "Movie.h"

//merge sort and quick sort are both divide and conquer, so lots of helper functions can be shared between us,
//hence why it's just sorting.h and not any specific one.

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
