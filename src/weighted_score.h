#ifndef MOVIERANKER_WEIGHTED_SCORE_H
#define MOVIERANKER_WEIGHTED_SCORE_H
#include "Movie.h"

double weightedScore(const Movie& movie, double meanVoteAverage);
void populatingScore(std::vector<Movie>& movies);

#endif //MOVIERANKER_WEIGHTED_SCORE_H
