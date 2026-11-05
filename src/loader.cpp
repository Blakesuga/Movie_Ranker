#include <iostream>
#include <fstream>
#include <stdexcept>
#include <unordered_map>
#include <cctype>

#include "csv.h"
#include "loader.h"
#include "weighted_score.h"

// only helpers are visible in this file, not outside of it
namespace {

    // helper functions to load movie data and catch empty cells
    double toDouble(const std::string& s, double fallback = 0.0) {
        if (s.empty())
            return fallback;
        
        try {
            return std::stod(s);
        }

        catch (...) {
            return fallback;
        }
    }

    unsigned toUInt(const std::string& s, unsigned fallback = 0) {
        if (s.empty())
            return fallback;
        
        try {
            return static_cast<unsigned>(std::stoul(s));
        }

        catch (...) {
            return fallback;
        }
    }

    // release_date looks like YYYY-MM-DD, first 4 chars are year, 0 if empty/unknown
    unsigned yearFromDate(const std::string& d) {
        return d.size() >= 4 ? toUInt(d.substr(0, 4)) : 0;
    }

    // split genre string into a vector of genres
    std::vector<std::string> splitGenres(const std::string& s) {
        std::vector<std::string> out;
        std::string curr;

        for (char c : s) {
            if (c == ',') {
                if (!curr.empty())
                    out.push_back(curr);

                curr.clear();
            }

            else if (!(c == ' ' && curr.empty())) {
                curr += c;  // ignores leading spaces after a comma     
            }     
        }

        if (!curr.empty())
            out.push_back(curr);

        return out;
    }

    // filter out adult movies from raw data
    const std::vector<std::string> kBlockedWords = {
        "adult", "porn", "pornography", "kink", "xxx", "sex", "erotic", "nude", "nudity", "hentai", "pervert", "fetish", "bdsm", "bondage", "s&m", "sado-masochism", "sadomasochism"
    };

    std::string toLower(std::string s){
        for (char& c : s)
            c = static_cast<char>(std::tolower(c));

        return s;
    }

    bool containsBlocked(const std::string& text) {
        std::string lower = toLower(text);

        for (const auto& w : kBlockedWords) {
            if (lower.find(w) != std::string::npos)
                return true;
        }

        return false;
    }
}


// 
std::vector<Movie> loadMovies(const std::string& path) {
    std::ifstream in(path);
    if (!in)
        throw std::runtime_error("Failed to open file: " + path);

    std::vector<std::string> header, row;
    if (!readRecord(in, header))
        throw std::runtime_error("Empty file");

    // check for BOM
    if(header[0].rfind("\xEF\xBB\xBF", 0) == 0)
        header[0].erase(0, 3);

    // map column names to their indices
    std::unordered_map<std::string, size_t> col;
    for (size_t i = 0; i < header.size(); ++i)
        col[header[i]] = i;
    
    auto need = [&](const std::string& name) {
        auto it = col.find(name);
        if (it == col.end())
            throw std::runtime_error("Missing column: " + name);

        return it -> second;
    };

    const size_t ID = need("id"), 
                 TITLE = need("title"),
                 VA = need("vote_average"), 
                 VC = need("vote_count"), 
                 DATE = need("release_date"), 
                 POP = need("popularity"),
                 GEN = need("genres"),
                 ADULT = need("adult");


    std::vector<Movie> movies;
    movies.reserve(1'700'000); // rough estimate of movies in database
    size_t skipped = 0, filtered = 0;

    while (readRecord(in, row)) {
        if (row.size() != header.size() || row[TITLE].empty()) {
            ++skipped;
            continue;
        }

        if (row[ADULT] == "True") {
            ++filtered;
            continue;
        }

        movies.emplace_back(toUInt(row[ID]), 
                        std::move(row[TITLE]),
                        toUInt(row[VC]),
                        toDouble(row[VA]),
                        toDouble(row[POP]),
                        yearFromDate(row[DATE]), 
                        splitGenres(row[GEN]));                  

    }

    // This populates the weighted scored directly after all movies are loaded.
    populatingScore(movies);

    std::cerr << "Loaded " << movies.size() << " movies, skipped " << skipped
              << " malformed rows, filtered " << filtered << " adult movies\n";
    return movies;
}