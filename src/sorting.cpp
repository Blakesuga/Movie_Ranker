#include "sorting.h"

double getValue(const Movie& movie, sortingKey key, sortingOrder order) {
    if (key == sortingKey::weightedScore) {
        if (order == sortingOrder::ascending) {
            return movie.weighted_score;
        } else {
            return movie.weighted_score * -1;
        }
    }
    else {
        if (order == sortingOrder::ascending) {
            return movie.release_year;
        } else {
            return -static_cast<double> (movie.release_year);
        }
    }
}
