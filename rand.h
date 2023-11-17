#ifndef RANDOM_H
#define RANDOM_H

#include <random>

std::mt19937 rnd((std::random_device())());

template<typename T>
T randint(T l, T r) {
    std::uniform_int_distribution<T> distrib(l, r);
    return distrib(rnd);
}

#endif
