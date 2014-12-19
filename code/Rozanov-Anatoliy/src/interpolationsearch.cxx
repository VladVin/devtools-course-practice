// Copyright 2014 Anatoliy Rozanov

#include <stdexcept>
#include <string>
#include "include/interpolationsearch.h"

int InterpolationSearch::run(const int *a, const int &n, const int &k) {
    if (n == 0)
        throw std::string("ERROR: n == 0");
    if (a == 0)
        throw std::string("ERROR: a == 0");
    int left = 0;
    int right = n - 1;
    int mid;
    while (a[left] < k && k < a[right]) {
        mid = left + (k - a[left]) * (right - left) / (a[right] - a[left]);
        if (a[mid] < k)
            left = mid + 1;
        else if (a[mid] > k)
            right = mid - 1;
        else
            return mid;
    }
    if (a[left] == k)
        return left;
    else if (a[right] == k)
        return right;
    else
        return -1;
}
