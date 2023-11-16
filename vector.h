#ifndef VECT_H
#define VECT_H

#include <vector>
#include <string>
#include <cassert>
#include "basic.h"
#include <cstdio>
#include "debug.h"

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
        logl("#1 done");
    }
    Vector(size_t n, const T& t) {
        _n = n;
        _data = new T[_n];
        for (size_t i = 0; i < _n; i++) {
            _data[i] = t;
        }
        logl("#2 done");
    }
    Vector(const Vector<T>& v) {
        _n = v._n;
        _data = new T[_n];
        for (size_t i = 0; i < _n; i++) {
            _data[i] = v._data[i];
        }
        logl("#3 done");
    }
    Vector(Vector<T>&& v) {
        _n = v._n;
        _data = v._data;
        v._data = nullptr;
        logl("#4 done");
    }
    ~Vector() {
        logl("detructor");
        if (_data != nullptr) {
            logl("free memory");
            delete[] _data;
        }
    }

    T& operator[] (size_t c) { return _data[c - 1]; }
    const T& operator[] (size_t c) const { return _data[c - 1]; }
    Vector<T>& operator= (const Vector<T>& v) {
        if (v._n > _n) {
            if (_data != nullptr) delete[] _data;
            _data = new T[_n];
        }
        _n = v._n;
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

    friend void swap(Vector<T>& v1, Vector<T>& v2) {
        std::swap(v1._data, v2._data);
        std::swap(v1._n, v2._n);
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
Vector<T> operator* (const Vector<T>& v, const T& c) {
    size_t n = v.size();
    Vector<T> res(n);
    for (size_t i = 1; i <= n; i++) {
        res[i] = v[i] * c;
    }
    return res;
}

template<typename T>
Vector<T> operator* (const T& c, const Vector<T>& v) {
    size_t n = v.size();
    Vector<T> res(n);
    for (size_t i = 1; i <= n; i++) {
        res[i] = v[i] * c;
    }
    return res;
}

template<typename T>
Vector<T> operator/ (const Vector<T>& v, const T& c) {
    size_t n = v.size();
    Vector<T> res(n);
    for (size_t i = 1; i <= n; i++) {
        res[i] = v[i] / c;
    }
    return res;
}

#endif
