#pragma once

#ifdef GMP

#include <gmpxx.h>

using Integer = mpz_class;

#else
#warning "using other implements of integer may cause some problems!"
#ifdef DEV

#include "util.h"
#include <iostream>
#include <string>

class Integer: public printable {
    int _sgn;
    Dynarray<int> _data;
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

    Integer operator-() const;
    Integer operator+() const;

    bool operator==(const Integer&) const;
    bool operator!=(const Integer&) const;
    bool operator<(const Integer&) const;
    bool operator>(const Integer&) const;
    bool operator>=(const Integer&) const;
    bool operator<=(const Integer&) const;
};

#else
#ifdef ALT1

#include "int_alt.h"
using Integer = int_alt1::BigInt;

#else
#ifdef ALT2

#include "int_alt2.h"
using Integer = int_alt2::BigIntDec;

#else

using Integer = long long;

#endif // ALT2
#endif // ALT1
#endif // DEV
#endif // GMP
