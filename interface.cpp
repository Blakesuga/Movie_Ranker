#include "interface.h"   
#include "sorting.h"    
#include "benchmark.h"   

#include <iostream>     
#include <string>   
#include <vector>     

namespace {

const std::size_t topResults = 25;

std::size_t textWidth(const std::string& text) {
    std::size_t width = 0;
    for (char c : text) {
        if ((static_cast<unsigned char>(c) & 0xC0) != 0x80) ++width;
    }
    return width;
}

std::string fit(const std::string& text, std::size_t width, bool alignRight = false) {
    std::string shown = text;
    if (textWidth(shown) > width) {
        std::size_t bytes = 0;
        std::size_t characters = 0;
        while (bytes < shown.size()) {
            const bool startsCharacter = (static_cast<unsigned char>(shown[bytes]) & 0xC0) != 0x80;
            if (startsCharacter && characters == width - 3) break;
            if (startsCharacter) ++characters;
            ++bytes;
        }
        shown = shown.substr(0, bytes) + "...";
    }
    const std::string padding(width - textWidth(shown), ' ');
    return alignRight ? padding + shown : shown + padding;
}

std::string center(const std::string& text, std::size_t width) {
    const std::size_t used = textWidth(text) < width ? textWidth(text) : width;
    const std::size_t left = (width - used) / 2;
    return std::string(left, ' ') + fit(text, width - left);
}

std::vector<std::string> box(const std::vector<std::string>& lines, std::size_t width, bool centered) {
    const std::string edge = "+" + std::string(width + 2, '-') + "+";
    std::vector<std::string> rows = {edge};
    for (const std::string& line : lines) {
        rows.push_back("| " + (centered ? center(line, width) : fit(line, width)) + " |");
    }
    rows.push_back(edge);
    return rows;
}

void printBoxes(const std::vector<std::vector<std::string>>& boxes) {
    for (std::size_t row = 0; row < boxes[0].size(); ++row) {
        for (std::size_t i = 0; i < boxes.size(); ++i) {
            std::cout << (i == 0 ? "" : "  ") << boxes[i][row];
        }
        std::cout << "\n";
    }
}

std::string formatNumber(double value, int decimals) {
    long long scale = 1;
    for (int i = 0; i < decimals; ++i) scale *= 10;
    const long long rounded = static_cast<long long>(value * static_cast<double>(scale) + 0.5);
    std::string fraction = std::to_string(rounded % scale);
    while (fraction.size() < static_cast<std::size_t>(decimals)) fraction = "0" + fraction;
    return std::to_string(rounded / scale) + "." + fraction;
}

std::string withCommas(std::size_t number) {
    std::string digits = std::to_string(number);
    for (std::size_t i = digits.size(); i > 3; i -= 3) digits.insert(i - 3, ",");
    return digits;
}

std::string joinGenres(const std::vector<std::string>& genres) {
    std::string joined;
    for (const std::string& genre : genres) joined += (joined.empty() ? "" : ", ") + genre;
    return joined;
}

bool hasGenre(const Movie& movie, const std::string& genre) {
    for (const std::string& movieGenre : movie.genres) {
        if (movieGenre == genre) return true;
    }
    return false;
}

void addGenre(std::vector<std::string>& genres, const std::string& genre) {
    for (const std::string& existing : genres) {
        if (existing == genre) return;
    }
    genres.push_back(genre);
    for (std::size_t i = genres.size() - 1; i > 0 && genres[i] < genres[i - 1]; --i) {
        const std::string temp = genres[i];
        genres[i] = genres[i - 1];
        genres[i - 1] = temp;
    }
}

std::string ask(const std::string& question) {
    std::cout << question;
    std::string answer;
    if (!std::getline(std::cin, answer)) return "";
    const std::size_t first = answer.find_first_not_of(" \t\r");
    if (first == std::string::npos) return "";
    return answer.substr(first, answer.find_last_not_of(" \t\r") - first + 1);
}

int askNumber(const std::string& question, int low, int high, int fallback) {
    while (true) {
        const std::string answer = ask(question);
        if (answer.empty()) return fallback;
        bool valid = answer.size() <= 9;
        int number = 0;
        for (std::size_t i = 0; valid && i < answer.size(); ++i) {
            if (answer[i] < '0' || answer[i] > '9') {
                valid = false;
            } else {
                number = number * 10 + (answer[i] - '0');
            }
        }
        if (valid && number >= low && number <= high) return number;
        std::cout << "Please type a number from " << low << " to " << high << ", or just press Enter.\n";
    }
}

void printTable(const std::vector<Movie>& sorted) {
    const std::vector<std::size_t> widths = {2, 33, 4, 19, 14};
    const std::vector<bool> alignRight = {true, false, true, false, true};
    std::string edge = "+";
    for (std::size_t width : widths) edge += std::string(width + 2, '-') + "+";

    auto printRow = [&](const std::vector<std::string>& cells) {
        std::cout << "|";
        for (std::size_t i = 0; i < cells.size(); ++i) std::cout << " " << fit(cells[i], widths[i], alignRight[i]) << " |";
        std::cout << "\n";
    };

    std::cout << edge << "\n";
    printRow({"#", "Title", "Year", "Genre", "Weighted Score"});
    std::cout << edge << "\n";
    for (std::size_t i = 0; i < sorted.size() && i < topResults; ++i) {
        const Movie& movie = sorted[i];
        printRow({std::to_string(i + 1), movie.title,
                  movie.release_year > 0 ? std::to_string(movie.release_year) : "-",
                  movie.genres.empty() ? "-" : joinGenres(movie.genres),
                  formatNumber(movie.weighted_score, 2)});
    }
    std::cout << edge << "\n";
}

}

void runInterface(const std::vector<Movie>& movies) {
    std::vector<std::string> genres;
    int minYear = 0;
    int maxYear = 0;
    for (const Movie& movie : movies) {
        for (const std::string& genre : movie.genres) addGenre(genres, genre);
        if (movie.release_year > 0 && (minYear == 0 || movie.release_year < minYear)) minYear = movie.release_year;
        if (movie.release_year > maxYear) maxYear = movie.release_year;
    }

    bool sortAgain = true;
    while (sortAgain) {
        std::cout << "\nFilters\n";
        std::vector<std::string> menu;
        const std::size_t rows = (genres.size() + 3) / 3;
        for (std::size_t row = 0; row < rows; ++row) {
            std::string line;
            for (std::size_t column = 0; column < 3; ++column) {
                const std::size_t number = column * rows + row;
                if (number > genres.size()) continue;
                line += fit(std::to_string(number) + ") " + (number == 0 ? "Any Genre" : genres[number - 1]), 28);
            }
            menu.push_back(line);
        }
        printBoxes({box(menu, 84, false)});

        const int genreNumber = askNumber("Genre number (Enter = Any Genre): ", 0, static_cast<int>(genres.size()), 0);
        const std::string genre = genreNumber == 0 ? "" : genres[static_cast<std::size_t>(genreNumber) - 1];
        const std::string yearRange = " (" + std::to_string(minYear) + "-" + std::to_string(maxYear) + ", Enter = Any): ";
        int yearFrom = askNumber("Release year from" + yearRange, minYear, maxYear, 0);
        int yearTo = askNumber("Release year to" + yearRange, minYear, maxYear, 0);
        if (yearFrom != 0 && yearTo != 0 && yearFrom > yearTo) {
            const int earlier = yearTo;
            yearTo = yearFrom;
            yearFrom = earlier;
        }

        std::cout << "\nSorting\n";
        const int sortBy = askNumber("Sort by:  1) Weighted Score  2) Release Year  (Enter = 1): ", 1, 2, 1);
        const int orderBy = askNumber("Order:    1) Ascending  2) Descending  (Enter = 2): ", 1, 2, 2);
        const sortingKey key = sortBy == 1 ? sortingKey::weightedScore : sortingKey::releaseYear;
        const sortingOrder order = orderBy == 1 ? sortingOrder::ascending : sortingOrder::descending;

        std::vector<Movie> byQuick;
        for (const Movie& movie : movies) {
            if (!genre.empty() && !hasGenre(movie, genre)) continue;
            if (yearFrom != 0 && movie.release_year < yearFrom) continue;
            if (yearTo != 0 && movie.release_year > yearTo) continue;
            if (key == sortingKey::releaseYear && movie.release_year == 0) continue;
            byQuick.push_back(movie);
        }
        std::vector<Movie> byMerge = byQuick;
        const double mergeMs = timedSort(byMerge, mergeSort, key, order);
        const double quickMs = timedSort(byQuick, quickSort, key, order);
        const bool quickFaster = quickMs <= mergeMs;
        const std::string fastest = quickFaster ? "Quick Sort" : "Merge Sort";

        std::cout << "\n";
        printBoxes({box({"Merge Sort", formatNumber(mergeMs, 3) + " ms"}, 24, true),
                    box({"Quick Sort", formatNumber(quickMs, 3) + " ms"}, 24, true),
                    box({"Fastest", fastest}, 24, true)});

        std::cout << "\nResults (" << (sortBy == 1 ? "Weighted Score" : "Release Year")
                  << (orderBy == 1 ? ", ascending" : ", descending") << ", from " << fastest << ")\n";
        printTable(quickFaster ? byQuick : byMerge);
        if (byQuick.empty()) {
            std::cout << "No movies match these filters.\n";
        } else {
            const std::size_t shown = byQuick.size() < topResults ? byQuick.size() : topResults;
            std::cout << "Top " << shown << " of " << withCommas(byQuick.size()) << " matching movies\n";
        }

        const std::string again = ask("\nSort again? (y/n): ");
        sortAgain = !again.empty() && (again[0] == 'y' || again[0] == 'Y');
    }
}
