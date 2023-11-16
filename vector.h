#ifndef VECT_H
#define VECT_H

#include <vector>
#include <string>
#include <cassert>
#include "basic.h"

template<typename T>
class Vector {
protected:
    T* _data;
    size_t _n;
public:
    Vector() : _data(nullptr) {}
    Vector(size_t n) {
        _n = n;
        _data = new T[n];
    }
    Vector(size_t n, const T& t) {
        _n = n;
        _data = new T[n];
        for (size_t i = 0; i < n; i++) {
            _data[i] = t;
        }
    }
    Vector(const Vector<T>& v) {
        _n = v._n;
        _data = new T[_n];
        for (size_t i = 0; i < _n; i++) {
            _data[i] = v._data[i];
        }
    }
    Vector(Vector<T>&& v) {
        _n = v._n;
        _data = v._data;
        v._data = nullptr;
    }
    ~Vector() {
        if (_data != nullptr) {
            delete[] _data;
        }
    }

    T& operator[] (size_t c) { return _data[c - 1]; }
    const T& operator[] (size_t c) const { return _data[c - 1]; }
    Vector<T>& operator= (const Vector<T>& v) {
        if (_data != nullptr) delete[] _data;
        _n = v._n;
        _data = new T[_n];
        for (size_t i = 0; i < _n; i++) {
            _data[i] = v._data[i];
        }
        return *this;
    }

    size_t size() const { return _n; }
    friend std::istream& operator>> (std::istream& is, Vector<T>& vec) {
        for (size_t i = 1; i <= vec.size(); i++) {
            is >> vec[i];
        }
        return is;
    }
};

template<typename T>
class colVector : public Vector<T> {
    friend std::ostream& operator<< (std::ostream &os, const colVector<T>& vec) {
        os << "\\left(\\begin{array}{c}";
        auto n = vec.size();
        if (n) {
            for (size_t i = 1; i < n; i++) {
                os << vec[i] << "\\\\";
            }
            os << vec[n];
        }
        os << "\\end{array}\\right)";
        return os;
    }
};

template<typename T>
class rowVector : public Vector<T> {
    friend std::ostream& operator<< (std::ostream &os, const rowVector<T>& vec) {
        os << "\\left(\\begin{array}{c}";
        auto n = vec.size();
        if (n) {
            for (size_t i = 1; i < n; i++) {
                os << vec[i] << "&";
            }
            os << vec[n];
        }
        os << "\\end{array}\\right)";
        return os;
    }
};

using qrowVector = rowVector<Num>; // row vector in Q^n
using rrowVector = rowVector<double>; // row vector in R^n
using qcolVector = colVector<Num>; // column vector in Q^n
using rcolVector = colVector<double>; // column vector in R^n

template<typename T>
Vector<T> operator+ (const Vector<T>& v1, const Vector<T>& v2) {
    assert(v1.size() == v2.size());
    size_t n = v1.size();
    Vector<T> res(n);
    for (size_t i = 1; i <= n; i++) {
        res[i] = v1[i] + v2[i];
    }
    return res;
}

template<typename T>
Vector<T> operator- (const Vector<T>& v1, const Vector<T>& v2) {
    assert(v1.size() == v2.size());
    size_t n = v1.size();
    Vector<T> res(n);
    for (size_t i = 1; i <= n; i++) {
        res[i] = v1[i] - v2[i];
    }
    return res;
}

template<typename T>
Vector<T> operator* (const Vector<T>& v, const Num& c) {
    size_t n = v.size();
    Vector<T> res(n);
    for (size_t i = 1; i <= n; i++) {
        res[i] = v[i] * c;
    }
    return res;
}

template<typename T>
Vector<T> operator* (const Num& c, const Vector<T>& v) {
    size_t n = v.size();
    Vector<T> res(n);
    for (size_t i = 1; i <= n; i++) {
        res[i] = v[i] * c;
    }
    return res;
}

template<typename T>
Vector<T> operator/ (const Vector<T>& v, const Num& c) {
    size_t n = v.size();
    Vector<T> res(n);
    for (size_t i = 1; i <= n; i++) {
        res[i] = v[i] / c;
    }
    return res;
}

#endif
