#pragma once

#include "debug.h"
#include <cstdio>
#include <vector>
#include <string>
#include <cassert>

template<typename T>
class Vector {
protected:
    T* _data;
    size_t _n;

public:
    Vector(): _data(nullptr) {}
    Vector(size_t n) {
        //debugi << "#1 start n = " << n << "\n";
        _n = n;
        _data = new T[n];
        //debugi << "#1 done n = " << n << "\n";
    }
    Vector(size_t n, const T t) {
        //debugi << "#2 start n = " << n << "\n";
        _n = n;
        _data = new T[_n];
        for (size_t i = 0; i < _n; i++) {
            _data[i] = T(t);
        }
        //debugi << "#2 done n = " << n << "\n";
        for (size_t i = 0; i < _n; i++) {
            //debug << _data[i] << "\n";
        }
        //debug << "\n";
    }
    Vector(const Vector<T>& v) {
        _n = v._n;
        _data = new T[_n];
        for (size_t i = 0; i < _n; i++) {
            _data[i] = T(v._data[i]);
        }
        //debugi << "#3 done (deep copy)\n";
    }
    Vector(Vector<T>&& v) {
        _n = v._n;
        _data = v._data;
        v._data = nullptr;
        //debugi << "#4 done (copy)\n";
    }
    ~Vector() {
        if (_data != nullptr) {
            //debugi << "free memory\n";
            delete[] _data;
        }
    }

    T& operator[] (size_t c) { return _data[c - 1]; }
    const T& operator[] (size_t c) const { return _data[c - 1]; }
    Vector<T>& operator= (const Vector<T>& v) {
        //debugi << "deep copy\n";
        if (this != &v) {
            if (v._n > _n) {
                if (_data != nullptr) delete[] _data;
                _data = new T[_n];
            }
            _n = v._n;
            for (size_t i = 1; i <= _n; i++) {
                (*this)[i] = T(v[i]);
            }
        }
        return *this;
    }
    Vector<T>& operator= (Vector<T>&& v) {
        //debugi << "copy\n";
        if (this != &v) {
            if (_data != nullptr) delete[] _data;
            _data = v._data;
            _n = v._n;
            v._data = nullptr;
        }
        return *this;
    }
    bool operator== (const Vector<T>& v) const {
        for (size_t i = 1; i <= v.size(); i++) {
            if ((*this)[i] != v[i]) {
                //debugl((*this)[i]);
                //debugl(v[i]);
                return 0;
            }
        }
        return 1;
    }
    bool operator!= (const Vector<T>& v) const {
        //debugi << std::endl;
        return !(this->operator==(v));
    }

    size_t size() const { return _n; }
    friend std::istream& operator>> (std::istream& is, Vector<T>& vec) {
        //debugi << std::endl;
        for (size_t i = 1; i <= vec.size(); i++) {
            is >> vec[i];
        }
        return is;
    }

    friend void swap(Vector<T>& v1, Vector<T>& v2) {
        std::swap(v1._data, v2._data);
        std::swap(v1._n, v2._n);
    }
    void swap(Vector<T>& v2) {
        std::swap(this->_data, v2._data);
        std::swap(this->_n, v2._n);
    }

    friend Vector<T> operator+ (const Vector<T>& v1, const Vector<T>& v2) {
        assert(v1.size() == v2.size());
        size_t n = v1.size();
        Vector<T> res(n);
        for (size_t i = 1; i <= n; i++) {
            res[i] = v1[i] + v2[i];
        }
        return res;
    }
    Vector<T>& operator+= (const Vector<T>& v2) {
        assert(_n == v2._n);
        for (size_t i = 1; i <= _n; i++) {
            (*this)[i] += v2[i];
        }
        return *this;
    }

    friend Vector<T> operator- (const Vector<T>& v1, const Vector<T>& v2) {
        assert(v1.size() == v2.size());
        size_t n = v1.size();
        Vector<T> res(n);
        for (size_t i = 1; i <= n; i++) {
            res[i] = v1[i] - v2[i];
        }
        return res;
    }
    Vector<T>& operator-= (const Vector<T>& v2) {
        assert(_n == v2._n);
        for (size_t i = 1; i <= _n; i++) {
            (*this)[i] -= v2[i];
        }
        return *this;
    }

    friend Vector<T> operator* (const Vector<T>& v, const T& c) {
        size_t n = v.size();
        Vector<T> res(n);
        for (size_t i = 1; i <= n; i++) {
            res[i] = v[i] * c;
        }
        return res;
    }
    template<typename T2>
    Vector<T>& operator*= (const T2 c) {
        for (size_t i = 1; i <= _n; i++) {
            (*this)[i] *= c;
        }
        return *this;
    }
    friend Vector<T> operator* (const T c, const Vector<T>& v) {
        size_t n = v.size();
        Vector<T> res(n);
        for (size_t i = 1; i <= n; i++) {
            res[i] = v[i] * c;
        }
        return res;
    }

    friend Vector<T> operator/ (const Vector<T>& v, const T c) {
        size_t n = v.size();
        Vector<T> res(n);
        for (size_t i = 1; i <= n; i++) {
            res[i] = v[i] / c;
        }
        return res;
    }
    template<typename T2>
    Vector<T>& operator/= (const T2 c) {
        //debugil(_n);
        for (size_t i = 1; i <= _n; i++) {
            //debugil((*this)[i]);
            //debugil(c);
            (*this)[i] /= c;
        }
        return *this;
    }
};

template<typename T>
class colVector : public Vector<T> {
    using Vector<T>::Vector;
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
    using Vector<T>::Vector;
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
