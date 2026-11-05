#pragma once
#include <vector>
#include <utility>
#include "sorting.h"

namespace detail {
    // merges sorted halves a[lo,mid) and a[mid, hi) -> a[lo, hi]
    template <typename T, typename Cmp>
    void merge(std::vector<T>& a, std::vector<T>& tmp, size_t lo, size_t mid, size_t hi, Cmp cmp) {
        size_t i = lo, j = mid, k = lo;

        while (i < mid && j < hi) {
            if (cmp(a[j], a[i])) 
                tmp[k++] = std::move(a[j++]);    // right is smaller
            
            else 
                tmp[k++] = std::move(a[i++]);    // ties go left
        }

        while (i < mid) 
            tmp[k++] = std::move(a[i++]);
        
        while (j < hi)
            tmp[k++] = std::move(a[j++]);

        for (size_t x = lo; x < hi; ++x) 
            a[x] = std::move(tmp[x]);
    }

    template <typename T, typename Cmp>
    inline void mergeSortRec(std::vector<T>& a, std::vector<T>& tmp, size_t lo, size_t hi, Cmp cmp) {
        if (hi - lo < 2) 
            return; // base case: 0 or 1 element

        size_t mid = lo + (hi - lo) / 2;
        mergeSortRec(a, tmp, lo, mid, cmp);
        mergeSortRec(a, tmp, mid, hi, cmp);

        // checks if in order, skips merge if sorted
        if (!cmp(a[mid], a[mid - 1])) 
            return; // already sorted

        merge(a, tmp, lo, mid, hi, cmp);
    }
}   

template <typename T, typename Cmp>
void mergeSort(std::vector<T>& a, Cmp cmp) {
    std::vector<T> tmp(a.size());
    detail::mergeSortRec(a, tmp, 0, a.size(), cmp);
}