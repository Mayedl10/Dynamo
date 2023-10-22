#ifndef PAIRS_HPP
#define PAIRS_HPP

#include "dynamo.hpp"

template<typename T1, typename T2>
struct customPair {
    T1 first;
    T2 second;
    customPair(T1 x, T2 y) {
        first = x;
        second = y;
    }
    customPair() {}
};

#endif