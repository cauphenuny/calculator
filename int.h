#pragma once

#ifdef DEV

#include "util.h"
#include <iostream>
#include <string>

class Integer {
    int _sgn;
    MemoryPool<int> _data;
public:
    Integer(long long);
    Integer(const std::string&);
    Integer(const Integer&);
    Integer(Integer&&);

    Integer& operator=(const Integer&);
    Integer& operator=(Integer&&);
    Integer& operator+=(const Integer&);
    Integer& operator-=(const Integer&);
    Integer& operator*=(const Integer&);
    Integer& operator/=(const Integer&);
    Integer& operator%=(const Integer&);

    friend Integer operator+(const Integer&, const Integer&);
    friend Integer operator-(const Integer&, const Integer&);
    friend Integer operator*(const Integer&, const Integer&);
    friend Integer operator/(const Integer&, const Integer&);
    friend Integer operator%(const Integer&, const Integer&);

    Integer operator-();
    Integer operator+();

    friend 

    friend std::istream &operator>>(std::istream &, Integer&);
    friend std::ostream &operator<<(std::ostream &, const Integer&);
};

#else
#ifdef NATIVE

using Integer = long long;

#else

#include "int_alt.h"
using Integer = legendstane::BigInt;

#endif
#endif // ifdef DEV
