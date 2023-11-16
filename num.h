#ifndef RAT_H
#define RAT_H

#include <string>
#include <iostream>

int64_t gcd(int64_t a, int64_t b) {
    return b == 0 ? a : gcd(b, a % b);
}

class num { // rational num
private:
    int64_t up; // numerator
    int64_t down; // denominator

public:
    friend void input(num&);
    friend const std::string latex(const num&);
    friend std::istream& operator>> (std::istream &, num&);
    friend std::ostream& operator<< (std::ostream &, const num&);

    void format() {
        if (!down) throw "divided by zero!";
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

    num(int64_t numerator = 0, int64_t denominator = 1): up(numerator), down(denominator) {}
    num(const num& n): up(n.up), down(n.down) {}
    num(const std::string& str) {
        auto c = str.begin();
        int64_t sig = 0;
        while (!isdigit(*c) && c != str.end()) {
            sig = (*c == '-'), c++;
        }
        while (isdigit(*c) && c != str.end()) {
            up = up * 10 + *c - '0', c++;
        }
        up *= sig ? -1 : 1;
        if (*c == '/') {
            sig = 0;
            while (!isdigit(*c) && c != str.end()) {
                sig = (*c == '-'), c++;
            }
            down = 0;
            while (isdigit(*c) && c != str.end()) {
                down = down * 10 + *c - '0', c++;
            }
            down *= sig ? -1 : 1;
        }
        format();
    }

    void operator= (const int64_t& val) {
        up = val, down = 1;
    }
    num operator+ (const num& val) const {
        num res;
        int64_t g = gcd(down, val.down);
        res.up = up * (val.down / g) + val.up * (down / g);
        res.down = down / g * val.down;
        res.format();
        return res;
    }
    num operator- (const num& val) const {
        num res;
        int64_t g = gcd(down, val.down);
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
    num& operator+= (const num& val) {
        int64_t g = gcd(down, val.down);
        up *= (val.down / g);
        up += val.up * (down / g);
        down *= (val.down / g);
        format();
        return *this;
    }
    num& operator-= (const num& val) {
        int64_t g = gcd(down, val.down);
        up *= (val.down / g);
        up -= val.up * (down / g);
        down *= (val.down / g);
        format();
        return *this;
    }
    num& operator*= (const num& val) {
        up *= val.up;
        down *= val.down;
        format();
        return *this;
    }
    num& operator/= (const num& val) {
        up *= val.down;
        down *= val.up;
        format();
        return *this;
    }
    num& operator= (const num& val) {
        up = val.up, down = val.down;
        return *this;
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
    bool operator!= (const num& val) const {
        return (down != val.down) || (up != val.up);
    }

};

const std::string latex(const num& n) {
    std::string res;
    auto &up = n.up, &down = n.down;
    if (up == 0) return "{0}";
    if (down == 1) { 
        res = "{" + std::to_string(up) + "}"; 
    } else {
        res = "\\frac{" + std::to_string(up) + "}{" + std::to_string(down) + "}";
    }
    return res;
}

std::istream& operator>> (std::istream &is, num& n) {
    std::string str;
    is >> str;
    n = str;
    return is;
}

std::ostream& operator<< (std::ostream &os, const num& n) {
    os << latex(n);
    return os;
}

#endif
