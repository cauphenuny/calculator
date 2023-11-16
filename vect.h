#ifndef VECT_H
#define VECT_H

#include <vector>
#include <string>
#include <cassert>

template<typename T>
class vect {
protected:
    T* _data;
    size_t _n;
public:
    vect() : _data(nullptr) {}
    vect(size_t n) {
        _n = n;
        _data = new T[n];
    }
    vect(size_t n, const T& t) {
        _n = n;
        _data = new T[n](t);
    }
    vect(const vect<T>& v) {
        _n = v._n;
        _data = new T[_n];
        for (size_t i = 0; i < _n; i++) {
            _data[i] = v._data[i];
        }
    }
    vect(vect<T>&& v) {
        _n = v._n;
        _data = v._data;
        v._data = nullptr;
    }
    ~vect() {
        if (_data != nullptr) {
            delete[] _data;
        }
    }

    T& operator[] (size_t c) { return _data[c - 1]; }
    const T& operator[] (size_t c) const { return _data[c - 1]; }
    vect<T>& operator= (const vect<T>& v) {
        if (_data != nullptr) delete[] _data;
        _n = v._n;
        _data = new T[_n];
        for (size_t i = 0; i < _n; i++) {
            _data[i] = v._data[i];
        }
        return *this;
    }

    size_t size() const { return _n; }
    friend std::istream& operator>> (std::istream& is, vect<T>& vec) {
        for (size_t i = 1; i <= vec.size(); i++) {
            is >> vec[i];
        }
        return is;
    }
};

template<typename T>
class col_vector : public vect<T> {
    friend const std::string latex(const col_vector<T>& vec) {
        std::string res = "\\left(\\begin{array}{c}";
        auto n = vec.size();
        if (n) {
            for (size_t i = 1; i < n; i++) {
                res += latex(vec[i]) + "\\\\";
            }
            res += latex(vec[n]);
        }
        res += "\\end{array}\\right)";
        return res;
    }
    friend std::ostream& operator<< (std::ostream &os, const col_vector<T>& cv) {
        os << latex(cv);
        return os;
    }
};

template<typename T>
class row_vector : public vect<T> {
    friend const std::string& latex(const row_vector<T>& vec) {
        std::string res = "\\left(\\begin{array}{c}";
        auto n = vec.size();
        if (n) {
            for (size_t i = 1; i < n; i++) {
                res += latex(vec[i]) + "&";
            }
            res += latex(vec[n]);
        }
        res += "\\end{array}\\right)";
        return res;
    }
    friend std::ostream& operator<< (std::ostream &os, const row_vector<T>& rv) {
        os << latex(rv);
        return os;
    }
};

using rq_vector = row_vector<num>; // row vector in Q^n
using cq_vector = col_vector<num>; // column vector in Q^n

template<typename T>
vect<T> operator+ (const vect<T>& v1, const vect<T>& v2) {
    assert(v1.size() == v2.size());
    size_t n = v1.size();
    vect<T> res(n);
    for (size_t i = 1; i <= n; i++) {
        res[i] = v1[i] + v2[i];
    }
    return res;
}

template<typename T>
vect<T> operator- (const vect<T>& v1, const vect<T>& v2) {
    assert(v1.size() == v2.size());
    size_t n = v1.size();
    vect<T> res(n);
    for (size_t i = 1; i <= n; i++) {
        res[i] = v1[i] - v2[i];
    }
    return res;
}

template<typename T>
vect<T> operator* (const vect<T>& v, const num& c) {
    size_t n = v.size();
    vect<T> res(n);
    for (size_t i = 1; i <= n; i++) {
        res[i] = v[i] * c;
    }
    return res;
}

template<typename T>
vect<T> operator* (const num& c, const vect<T>& v) {
    size_t n = v.size();
    vect<T> res(n);
    for (size_t i = 1; i <= n; i++) {
        res[i] = v[i] * c;
    }
    return res;
}

template<typename T>
vect<T> operator/ (const vect<T>& v, const num& c) {
    size_t n = v.size();
    vect<T> res(n);
    for (size_t i = 1; i <= n; i++) {
        res[i] = v[i] / c;
    }
    return res;
}

#endif
