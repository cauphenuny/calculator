#ifndef VECT_H
#define VECT_H

#include <vector>
#include <string>
#include <cassert>
#include "item.h"

class vect : public math_item {
    std::vector<num> _a;
    int _n;
public:
    vect(int n) : _n(n), _a(n) {}
    vect(const vect& v) : _n(v._n), _a(v._a) {}

    void input() { 
        for (int i = 0; i < _n; i++) {
            _a[i].input();
        }
    }

    num& operator[] (int c) { return _a[c - 1]; }
    const num& operator[] (int c) const { return _a[c - 1]; }

    int size() const { return _n; }
    std::string latex() const;
};


std::string vect::latex() const {
    std::string res = "\\left(\\begin{array}{c}";
    if (_n) {
        for (int i = 0; i < _n - 1; i++) {
            res += _a[i].latex() + "\\\\";
        }
        res += _a[_n - 1].latex();
    }
    res += "\\end{array}\\right)";
    return res;
}

vect operator+ (const vect& v1, const vect& v2) {
    assert(v1.size() == v2.size());
    int n = v1.size();
    vect res(n);
    for (int i = 1; i <= n; i++) {
        res[i] = v1[i] + v2[i];
    }
    return res;
}

vect operator- (const vect& v1, const vect& v2) {
    assert(v1.size() == v2.size());
    int n = v1.size();
    vect res(n);
    for (int i = 1; i <= n; i++) {
        res[i] = v1[i] - v2[i];
    }
    return res;
}

vect operator* (const vect& v, const num& c) {
    int n = v.size();
    vect res(n);
    for (int i = 1; i <= n; i++) {
        res[i] = v[i] * c;
    }
    return res;
}

vect operator* (const num& c, const vect& v) {
    int n = v.size();
    vect res(n);
    for (int i = 1; i <= n; i++) {
        res[i] = v[i] * c;
    }
    return res;
}

vect operator/ (const vect& v, const num& c) {
    int n = v.size();
    vect res(n);
    for (int i = 1; i <= n; i++) {
        res[i] = v[i] / c;
    }
    return res;
}

#endif
