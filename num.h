#ifndef NUM_H
#define NUM_H

#include <string>
#include <iostream>
#include <cassert>
#include "debug.h"

int64_t gcd(int64_t a, int64_t b) {
    return b == 0 ? a : gcd(b, a % b);
}

class Num { // rational Num
private:
    int64_t up; // numerator
    int64_t down; // denominator

public:
    friend std::istream& operator>> (std::istream &, Num&);
    friend std::ostream& operator<< (std::ostream &, const Num&);

    void format() {
        assert(down != 0);
        if (up) {
            int64_t g = gcd(up, down);
            up /= g, down /= g;
        } else {
            down = 1;
        }
        if (down < 0) {
            up = -up, down = -down;
        }
    }

    bool neg() const { // negative
        return up < 0;
    }
    bool pos() const { // positive
        return up > 0;
    }

    Num(int64_t numerator = 0, int64_t denominator = 1): up(numerator), down(denominator) {}
    Num(const Num& n): up(n.up), down(n.down) {}
    Num(const std::string& str) {
        auto c = str.begin();
        int64_t sig = 0;
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

    void operator= (const int64_t& val) {
        up = val, down = 1;
    }
    Num operator- () const {
        return Num(-up, down);
    }
    Num operator+ () const {
        return Num(up, down);
    }
    Num operator+ (const Num& val) const {
        Num res;
        int64_t g = gcd(down, val.down);
        res.up = up * (val.down / g) + val.up * (down / g);
        res.down = down / g * val.down;
        res.format();
        return res;
    }
    Num operator- (const Num& val) const {
        Num res;
        int64_t g = gcd(down, val.down);
        res.up = up * (val.down / g) - val.up * (down / g);
        res.down = down / g * val.down;
        res.format();
        return res;
    }
    Num operator* (const Num& val) const {
        Num res(up * val.up, down * val.down);
        res.format();
        return res;
    }
    Num operator/ (const Num& val) const {
        Num res(up * val.down, down * val.up);
        res.format();
        return res;
    }
    Num& operator+= (const Num& val) {
        int64_t g = gcd(down, val.down);
        up *= (val.down / g);
        up += val.up * (down / g);
        down *= (val.down / g);
        format();
        return *this;
    }
    Num& operator-= (const Num& val) {
        int64_t g = gcd(down, val.down);
        up *= (val.down / g);
        up -= val.up * (down / g);
        down *= (val.down / g);
        format();
        return *this;
    }
    Num& operator*= (const Num& val) {
        up *= val.up;
        down *= val.down;
        format();
        return *this;
    }
    Num& operator/= (const Num& val) {
        up *= val.down;
        down *= val.up;
        format();
        return *this;
    }
    Num& operator= (const Num& val) {
        up = val.up, down = val.down;
        return *this;
    }

    bool operator== (const Num& val) const {
        return (up == val.up) && (down == val.down);
    }
    bool operator< (const Num& val) const {
        return (up * val.down) < (val.up * down);
    }
    bool operator> (const Num& val) const {
        return (up * val.down) > (val.up * down);
    }
    bool operator<= (const Num& val) const {
        return (up * val.down) <= (val.up * down);
    }
    bool operator>= (const Num& val) const {
        return (up * val.down) >= (val.up * down);
    }
    bool operator!= (const Num& val) const {
        return (down != val.down) || (up != val.up);
    }

};

std::istream& operator>> (std::istream &is, Num& n) {
    std::string str;
    is >> str;
    n = str;
    //debugil(n);
    return is;
}

std::ostream& operator<< (std::ostream &os, const Num& n) {
    auto &up = n.up, &down = n.down;
    if (down == 1) { 
        os << "{" << up << "}"; 
    } else {
        if (up > 0) {
            os << "\\dfrac{" << up << "}{" << down << "}";
        } else {
            os << "{-\\dfrac{" << -up << "}{" << down << "}}";
        }
    }
    return os;
}

#endif
