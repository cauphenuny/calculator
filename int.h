#ifndef INT_H
#define INT_H

#include "util.h"
#include <iostream>

class Integer {
    int _sgn;
    MemoryPool<int> _data;
public:
    Integer(long long);
    Integer(const Integer&);
    Integer(Integer&&);

    Integer& operator=(const Integer&);
    Integer& operator=(Integer&&);
    Integer& operator+=(const Integer&);
    Integer& operator-=(const Integer&);
    Integer& operator*=(const Integer&);
    Integer& operator/=(const Integer&);
    friend Integer operator+(const Integer&, const Integer&);
    friend Integer operator-(const Integer&, const Integer&);
    friend Integer operator*(const Integer&, const Integer&);
    friend Integer operator/(const Integer&, const Integer&);
    friend Integer operator%(const Integer&, const Integer&);

    friend std::istream &operator>>(std::istream &, Integer&);
    friend std::ostream &operator<<(std::ostream &, const Integer&);
};

#endif
