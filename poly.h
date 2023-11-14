#ifndef POLY_H
#define POLY_H

#include "item.h"
#include "num.h"

class monomial : public math_item {
    rational_num co; // coefficient
public:
    char id;
    s64 deg;
    monomial operator+ (const monomial& m) {
        monomial res;
        res.co = co + m.co;
        res.id = id;
        res.deg = deg;
        return res;
    }
    monomial() : co(0), id(0), deg(0) {}
    char input() {
        char c = co.input();
        if (isalpha(c)) {
            id = c;
            if (isdigit(c = getchar())) {
                deg = c - '0';
                while (isdigit(c = getchar())) {
                    deg = deg * 10 + c - '0';
                }
            }
        } else {
            id = 0;
        }
        return c;
    }
    void prints() const {
        co.print();
        if (id) {
            printf("%c%lld", id, deg);
        }
        printf(" ");
    }
    bool neg() const {
        return co.neg();
    }
    bool pos() const {
        return co.neg();
    }
    std::string latex() const {
        std::string res = co.latex();
        if (id) {
            res += id;
            if (deg != 1) {
                res += "^{" + std::to_string(deg) + "}";
            }
        }
        return "{" + res + "}";
    }
};

bool operator< (const monomial& m1, const monomial& m2) {
    if (m1.id != m2.id) return m1.id < m2.id;
    else return m1.deg < m2.deg;
}
bool operator> (const monomial& m1, const monomial& m2) {
    return m2 < m1;
}

class polynomial : public math_item {
private:
    std::vector<monomial> mono;
public:
    void format() {
        std::sort(mono.begin(), mono.end());
    }
    polynomial() {}
    polynomial(const monomial& m) {
        mono.push_back(m);
    }
    polynomial operator+ (const polynomial& poly) {
        polynomial res;
        size_t p1 = 0, p2 = 0;
        while (p1 < mono.size() && p2 < poly.mono.size()) {
            if (mono[p1] < poly.mono[p2]) {
                res.mono.push_back(mono[p1]);
                p1++;
            } else if (mono[p1] > poly.mono[p2]) {
                res.mono.push_back(poly.mono[p2]);
                p2++;
            } else {
                res.mono.push_back(mono[p1] + poly.mono[p2]);
                p1++, p2++;
            }
        }
        if (p1 < mono.size()) {
            for (size_t i = p1; i < mono.size(); i++) {
                res.mono.push_back(mono[i]);
            }
        }
        if (p2 < poly.mono.size()) {
            for (size_t i = p2; i < poly.mono.size(); i++) {
                res.mono.push_back(poly.mono[i]);
            }
        }
        return res;
    }
    std::string latex() const {
        if (mono.empty()) return "";
        std::string res = mono[0].latex();
        for (int i = 1; i < mono.size(); i++) {
            if (!mono[i].neg()) {
                res += "+" + mono[i].latex();
            }
        }
        return res;
    }
};

#endif
