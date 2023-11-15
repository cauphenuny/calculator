#ifndef VECT_H
#define VECT_H

#include <vector>
#include <string>
#include <cassert>
#include "item.h"

template<typename T>
class vect : public math_item {
protected:
    std::vector<T> _v;
    int _n;
public:
    vect(int n) : _n(n), _v(n) {}
    vect(int n, const T& t) : _n(n), _v(n, t) {}
    vect(const vect& v) : _n(v._n), _v(v._v) {}

    void input() { 
        for (int i = 0; i < _n; i++) {
            _v[i].input();
        }
    }

    T& operator[] (int c) { return _v[c - 1]; }
    const T& operator[] (int c) const { return _v[c - 1]; }

    int size() const { return _n; }
    std::string latex() const;
};


template<typename T>
std::string vect<T>::latex() const {
    std::string res = "\\left(\\begin{array}{c}";
    if (_n) {
        for (int i = 0; i < _n - 1; i++) {
            res += _v[i].latex() + "\\\\";
        }
        res += _v[_n - 1].latex();
    }
    res += "\\end{array}\\right)";
    return res;
}

template<typename T>
vect<T> operator+ (const vect<T>& v1, const vect<T>& v2) {
    assert(v1.size() == v2.size());
    int n = v1.size();
    vect<T> res(n);
    for (int i = 1; i <= n; i++) {
        res[i] = v1[i] + v2[i];
    }
    return res;
}

template<typename T>
vect<T> operator- (const vect<T>& v1, const vect<T>& v2) {
    assert(v1.size() == v2.size());
    int n = v1.size();
    vect<T> res(n);
    for (int i = 1; i <= n; i++) {
        res[i] = v1[i] - v2[i];
    }
    return res;
}

template<typename T>
vect<T> operator* (const vect<T>& v, const num& c) {
    int n = v.size();
    vect<T> res(n);
    for (int i = 1; i <= n; i++) {
        res[i] = v[i] * c;
    }
    return res;
}

template<typename T>
vect<T> operator* (const num& c, const vect<T>& v) {
    int n = v.size();
    vect<T> res(n);
    for (int i = 1; i <= n; i++) {
        res[i] = v[i] * c;
    }
    return res;
}

template<typename T>
vect<T> operator/ (const vect<T>& v, const num& c) {
    int n = v.size();
    vect<T> res(n);
    for (int i = 1; i <= n; i++) {
        res[i] = v[i] / c;
    }
    return res;
}

using qn_vector = vect<num>; // vector in Qn

#endif
