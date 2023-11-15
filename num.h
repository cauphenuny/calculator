#ifndef RAT_H
#define RAT_H

#include <string>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include "item.h"

class num : public math_item { // rational num
private:
    s64 up{0}; // numerator
    s64 down{1}; // denominator

public:
    num(s64 numerator = 0, s64 denominator = 1): up(numerator), down(denominator) {}
    num(const num& n): up(n.up), down(n.down) {}

    void format() {
        if (!down) throw "divided by zero!";
        if (up) {
            s64 g = gcd(up, down);
            up /= g, down /= g;
        } else {
            down = 1;
        }
        if (down < 0) {
            up = -up, down = -down;
        }
    }

    inline void print() const {
        if (down != 1) {
            printf("%lld/%lld", up, down);
        } else {
            printf("%lld", up);
        }
    }
    inline void prints() const { // print with space
        print();
        printf(" ");
    }
    std::string latex() const {
        std::string res;
        if (up == 0) return "{0}";
        if (down == 1) { 
            res = "{" + std::to_string(up) + "}"; 
        } else {
            res = "\\frac{" + std::to_string(up) + "}{" + std::to_string(down) + "}";
        }
        return res;
    }

    char input() {
        char c = getchar();
        s64 sig = 0;
        while (!isdigit(c)) sig = (c == '-'), c = getchar();
        up = 0;
        while (isdigit(c)) up = up * 10 + c - '0', c = getchar();
        up *= sig ? -1 : 1;
        if (c == '/') {
            sig = 0;
            while (!isdigit(c)) sig = (c == '-'), c = getchar();
            down = 0;
            while (isdigit(c)) down = down * 10 + c - '0', c = getchar();
            down *= sig ? -1 : 1;
        }
        format();
        return c;
    }

    bool neg() const { // negative
        return up < 0;
    }
    bool pos() const { // positive
        return up > 0;
    }

    void operator= (const s64& val) {
        up = val, down = 1;
    }
    num operator+ (const num& val) const {
        num res;
        s64 g = gcd(down, val.down);
        res.up = up * (val.down / g) + val.up * (down / g);
        res.down = down / g * val.down;
        res.format();
        return res;
    }
    num operator- (const num& val) const {
        num res;
        s64 g = gcd(down, val.down);
        res.up = up * (val.down / g) - val.up * (down / g);
        res.down = down / g * val.down;
        res.format();
        return res;
    }
    num operator* (const num& val) const {
        num res(up * val.up, down * val.down);
        res.format();
        return res;
    }
    num operator/ (const num& val) const {
        num res(up * val.down, down * val.up);
        res.format();
        return res;
    }
    void operator+= (const num& val) {
        s64 g = gcd(down, val.down);
        up *= (val.down / g);
        up += val.up * (down / g);
        down *= (val.down / g);
        format();
    }
    void operator-= (const num& val) {
        s64 g = gcd(down, val.down);
        up *= (val.down / g);
        up -= val.up * (down / g);
        down *= (val.down / g);
        format();
    }
    void operator*= (const num& val) {
        up *= val.up;
        down *= val.down;
        format();
    }
    void operator/= (const num& val) {
        up *= val.down;
        down *= val.up;
        format();
    }

    bool operator== (const num& val) const {
        return (up == val.up) && (down == val.down);
    }
    bool operator< (const num& val) const {
        return (up * val.down) < (val.up * down);
    }
    bool operator> (const num& val) const {
        return (up * val.down) > (val.up * down);
    }
    bool operator<= (const num& val) const {
        return (up * val.down) <= (val.up * down);
    }
    bool operator>= (const num& val) const {
        return (up * val.down) >= (val.up * down);
    }

};

#endif
