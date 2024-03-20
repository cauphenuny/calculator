#pragma once

#include <string>
#include <iostream>
#include <cassert>
#include "debug.h"
#include "int.h"
#include "util.h"

#ifndef ALT1
inline Integer gcd(Integer a, Integer b) {
    // debugi << "a = " << a << ", b = " << b << std::endl;
    return b == Integer(0) ? a : gcd(b, a % b);
}
#endif

class Num { // rational Num
  private:
    Integer up;   // numerator
    Integer down; // denominator

  public:
    void format() {
        assert(down != 0);
        // debugi << "up = " << up << " down = " << down << std::endl;
        if (down < 0) {
            up = -up, down = -down;
        }
        if (up != 0) {
            // debugi << "before gcd\n";
            Integer g = gcd(up > 0 ? up : -up, down);
            // debugil(g);
            up /= g, down /= g;
            // debugi << "after gcd: up = " << up << " down = " << down << "\n";
        } else {
            down = 1;
        }
    }

    bool neg() const { // negative
        return up < 0;
    }
    bool pos() const { // positive
        return up > 0;
    }

    Num(int val = 0) : up(val), down(1) {
    }
    Num(const Integer &numerator, const Integer &denominator)
        : up(numerator), down(denominator) {
    }
    Num(const Num &n) : up(n.up), down(n.down) {
    }
    Num(const std::string &str) {
        auto c = str.begin();
        int sig = 0;
        while (c != str.end() && !isdigit(*c)) {
            sig = (*c == '-'), c++;
        }
        up = 0, down = 1;
        while (c != str.end() && isdigit(*c)) {
            up = up * 10 + *c - '0', c++;
        }
        up *= sig ? -1 : 1;
        if (*c == '/') {
            sig = 0;
            while (c != str.end() && !isdigit(*c)) {
                sig = (*c == '-'), c++;
            }
            down = 0;
            while (c != str.end() && isdigit(*c)) {
                down = down * 10 + *c - '0', c++;
            }
            down *= sig ? -1 : 1;
        }
        format();
    }

    void operator=(const Integer &val) {
        up = val, down = 1;
    }
    Num operator-() const {
        return Num(-up, down);
    }
    Num operator+() const {
        return Num(up, down);
    }
    Num operator+(const Num &val) const {
        Num res;
        Integer g = gcd(down, val.down);
        res.up = up * (val.down / g) + val.up * (down / g);
        res.down = down / g * val.down;
        res.format();
        return res;
    }
    Num operator-(const Num &val) const {
        Num res;
        Integer g = gcd(down, val.down);
        res.up = up * (val.down / g) - val.up * (down / g);
        res.down = down / g * val.down;
        res.format();
        return res;
    }
    Num operator*(const Num &val) const {
        // debugil(*this), //debugil(val);
        Num res(up * val.up, down * val.down);
        // debugil(res);
        res.format();
        // debugil(res);
        return res;
    }
    Num operator/(const Num &val) const {
        Num res(up * val.down, down * val.up);
        res.format();
        return res;
    }
    Num &operator+=(const Num &val) {
        Integer g = gcd(down, val.down);
        up *= (val.down / g);
        up += val.up * (down / g);
        down *= (val.down / g);
        format();
        return *this;
    }
    Num &operator-=(const Num &val) {
        Integer g = gcd(down, val.down);
        up *= (val.down / g);
        up -= val.up * (down / g);
        down *= (val.down / g);
        format();
        return *this;
    }
    Num &operator*=(const Num &val) {
        up *= val.up;
        down *= val.down;
        format();
        return *this;
    }
    Num &operator/=(const Num &val) {
        // debugil(*this);
        // debugil(val);
        up *= val.down;
        down *= val.up;
        // debugil(*this);
        format();
        // debugil(*this);
        return *this;
    }
    Num &operator=(const Num &val) {
        up = val.up, down = val.down;
        return *this;
    }

    bool operator==(const Num &val) const {
        return (up == val.up) && (down == val.down);
    }
    bool operator<(const Num &val) const {
        return (up * val.down) < (val.up * down);
    }
    bool operator>(const Num &val) const {
        return (up * val.down) > (val.up * down);
    }
    bool operator<=(const Num &val) const {
        return (up * val.down) <= (val.up * down);
    }
    bool operator>=(const Num &val) const {
        return (up * val.down) >= (val.up * down);
    }
    bool operator!=(const Num &val) const {
        return (down != val.down) || (up != val.up);
    }
    friend std::istream &operator>>(std::istream &is, Num &n) {
        std::string str;
        is >> str;
        // debugi << std::endl;
        n = Num(str);
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const Num &n) {
        if (n.down == 1) {
            os << "{" << n.up << "}";
        } else {
            if (n.up > 0) {
                os << "\\frac{" << n.up << "}{" << n.down << "}";
            } else {
                os << "{-\\frac{" << -n.up << "}{" << n.down << "}}";
            }
        }
        return os;
    }
};
