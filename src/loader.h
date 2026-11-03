#pragma once
#include <string>
#include <vector>
#include "Movie.h"

// reads movie csv file and returns all valid movies in a vector
// returns error if empty data columns or file not found
std::vector<Movie> loadMovies(const std::string& path);