#ifndef MOVIE_RANKER_MOVIE_H


#define MOVIE_RANKER_MOVIE_H

#include <string>
#include <vector>
struct Movie {
    unsigned int id;
    std::string title;
    unsigned int vote_count;
    double vote_average;
    double weighted_score;
    double popularity;
    unsigned int release_year;
    std::vector<std::string> genres;

    Movie() : id(0), vote_count(0), vote_average(0.0), weighted_score(0.0), popularity(0.0), release_year(0) {}
    Movie(unsigned int i, std::string t, unsigned int vc, double va,
        double pop, unsigned int ry, std::vector<std::string> g) : id(i), title(t), vote_count(vc),
        vote_average(va), weighted_score(0.0), popularity(pop), release_year(ry), genres(g) {}

};

#endif
