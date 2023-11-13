#ifndef RAT_H
#define RAT_H

#include <string>
#include <cstdio>
#include "item.h"

class rational_num : public math_item {
private:
    s64 up{0}; // numerator
    s64 down{1}; // denominator

public:
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
        return "Hello World!";
        //std::string res;
        //if (down != 1) res = std::to_string(up);
        //else {
        //    res = "\\dfrac{" + std::to_string(up) + "}{" + std::to_string(down) + "}";
        //}
        //return res;
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

    void operator= (const s64& val) {
        up = val, down = 1;
    }
    rational_num operator+ (const rational_num& val) {
        rational_num res;
        s64 g = gcd(down, val.down);
        res.up = up * (val.down / g) + val.up * (down / g);
        res.down = down / g * val.down;
        res.format();
        return res;
    }
    rational_num operator- (const rational_num& val) {
        rational_num res;
        s64 g = gcd(down, val.down);
        res.up = up * (val.down / g) - val.up * (down / g);
        res.down = down / g * val.down;
        res.format();
        return res;
    }
    void operator+= (const rational_num& val) {
        s64 g = gcd(down, val.down);
        up *= (val.down / g);
        up += val.up * (down / g);
        down *= (val.down / g);
        format();
    }
    void operator-= (const rational_num& val) {
        s64 g = gcd(down, val.down);
        up *= (val.down / g);
        up -= val.up * (down / g);
        down *= (val.down / g);
        format();
    }
    void operator*= (const rational_num& val) {
        up *= val.up;
        down *= val.down;
        format();
    }
    void operator/= (const rational_num& val) {
        up *= val.down;
        down *= val.up;
        format();
    }

    rational_num(s64 numerator = 0, s64 denominator = 1): up(numerator), down(denominator) {}
};

#endif
