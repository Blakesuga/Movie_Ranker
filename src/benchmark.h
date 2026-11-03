#ifndef MOVIERANKER_BENCHMARK_H
#define MOVIERANKER_BENCHMARK_H
#include <vector>
#include "Movie.h"
#include "sorting.h"

double timedSort(std::vector<Movie>& movies, void (*sortFunc)(std::vector<Movie>& movies, sortingKey key, sortingOrder order), sortingKey key, sortingOrder order);

#endif
