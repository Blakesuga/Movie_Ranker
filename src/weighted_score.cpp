#include "weighted_score.h"

double weightedScore(const Movie& movie, double meanVoteAverage) {
    const double m = 200;
    double weighted = ((movie.vote_count)/(movie.vote_count+m))*movie.vote_average;
    weighted += ((m)/(movie.vote_count+m))*meanVoteAverage;
    return weighted;
}

void populatingScore(std::vector<Movie>& movies) {
    double totalVoteAverage = 0;
    int moviesWithVotes = 0;
    for (const auto & movie : movies) {
        if (movie.vote_count > 0) {
            moviesWithVotes++;
            totalVoteAverage += movie.vote_average;
        }
    }
    const double C = totalVoteAverage / moviesWithVotes;
    for (auto & movie : movies) {
        movie.weighted_score = weightedScore(movie, C);
    }
}