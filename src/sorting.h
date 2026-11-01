#ifndef MOVIERANKER_SORTING_H
#define MOVIERANKER_SORTING_H
#include "Movie.h"

enum class sortingKey { weightedScore, releaseYear };
enum class sortingOrder { ascending, descending };

double getValue(const Movie& movie, sortingKey key, sortingOrder order);
void quickSort(std::vector<Movie>& movies, sortingKey key, sortingOrder order);
void mergeSort(std::vector<Movie>& movies, sortingKey key, sortingOrder order);

#endif //MOVIERANKER_SORTING_H
