#pragma once

#ifdef DEV

#include "util.h"
#include <iostream>
#include <string>

class Integer {
    int _sgn;
    MemoryPool<int> _data;
public:
    Integer();
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

    friend std::istream &operator>>(std::istream &, Integer&);
    friend std::ostream &operator<<(std::ostream &, const Integer&);
};

#else
#ifdef ALT1

#include "int_alt.h"
using Integer = legendstane::BigInt;

#else
#ifdef ALT2

#include "int_alt2.h"
using Integer = BigIntDec;

#else

using Integer = long long;

#endif // ALT2
#endif // ALT1
#endif // DEV
