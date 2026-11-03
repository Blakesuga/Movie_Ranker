//Probably where interface will go

#ifndef DATA_DIR
#define DATA_DIR "data"
#endif

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "csv.h"
#include "loader.h"

int main() {
    std::cout << "I love movies" << std::endl;


    // load movie data from CSV file
    auto movies = loadMovies(std::string(DATA_DIR) + "/kaggle_movie_dataset.csv");
    

    /* test CSV parser for movie data
    std::istringstream test(
        "id,title,genres\n"
        "1,\"Plain\",\"Drama\"\n"
        "2,\"Comma, Inside\",\"Action, Comedy\"\n"
        "3,\"Say \"\"Hi\"\"\",\"\"\n"
        "4,\"Line\nBreak\",Horror\n");
    

    std::vector<std::string> row;
    while (readRecord(test, row)) {
        std::cout << row.size() << " fields | title = [" << row[1] << "]\n";
    }
    

    for (size_t i = 0; i < 5; ++i) {
        const Movie& m = movies[i];
        std::cout << m.id << " | " << m.title << " | " << m.release_year
                << " | votes: " << m.vote_count << " | avg: " << m.vote_average
                << " | genres:";
        for (const auto& g : m.genres) std::cout << " [" << g << "]";
        std::cout << "\n";
    }
    */

    return 0;
}

