#ifndef MATRIX_H
#define MATRIX_H

#include "num.h"
#include "vector.h"
#include "basic.h"
#include <vector>
#include <string>
#include <cassert>

template<typename T>
class Matrix : public Vector<Vector<T>> {
protected:
    size_t _n, _m;

public:
    Matrix(size_t row, size_t col) :
        Vector<Vector<T>>(row, Vector<T>(col)), 
        _n(row),
        _m(col) {
    }
    Matrix(size_t row, size_t col, T t) :
        Vector<Vector<T>>(row, Vector<T>(col, t)),
        _n(row),
        _m(col) {
    }
    Matrix(const Vector<Vector<T>>& v) : 
        Vector<Vector<T>>(v),
        _n(v._n),
        _m(v[1].size()) {
    }
    Matrix(Matrix&& mat) :
        Vector<Vector<T>>(mat),
        _n(mat._n),
        _m(mat._m) {
    }

    const T& operator() (size_t r, size_t c) const {
        return this -> operator[](r)[c];
    }
    T& operator() (size_t r, size_t c) {
        return this -> operator[](r)[c];
    }

    T det() const;
    size_t rank() const;
    Matrix inverse() const;
    friend void gauss();

    size_t rsize() const { return _n; }
    size_t csize() const { return _m; }

    friend Matrix<T> operator+ (const Matrix<T>& mat1, const Matrix<T>& mat2) {
        assert(mat1._n == mat2._n), assert(mat1._m == mat2._m);
        size_t n = mat1._n, m = mat1._m;
        Matrix<T> res(n, m);
        for (size_t i = 1; i <= n; i++) {
            res[i] = mat1[i] + mat2[i];
        }
        return res;
    }
    friend Matrix<T> operator- (const Matrix<T>& mat1, const Matrix<T>& mat2) {
        assert(mat1._n == mat2._n), assert(mat1._m == mat2._m);
        size_t n = mat1._n, m = mat1._m;
        Matrix<T> res(n, m);
        for (size_t i = 1; i <= n; i++) {
            res[i] = mat1[i] - mat2[i];
        }
        return res;
    }
    friend Matrix<T> operator* (const Matrix<T>& mat1, const Matrix<T>& mat2) {
        assert(mat1._m == mat2._n);
        Matrix<T> res(mat1._n, mat2._m);
        for (size_t k = 1; k <= mat1._m; k++) {
            for (size_t i = 1; i <= mat1._n; i++) {
                for (size_t j = 1; j <= mat2._m; j++) {
                    res(i, j) += mat1(i, k) * mat2(k, j);
                }
            }
        }
        return res;
    }

    friend std::ostream& operator<< (std::ostream& os, const Matrix<T>& mat) {
        os << "\\begin{pMatrix}\n";
        auto n = mat.rsize(), m = mat.csize();
        for (size_t i = 1; i <= n; i++) {
            for (size_t j = 1; j < m; j++) {
                os << mat(i, j) << "&";
            }
            os << mat(i, m) << "\\\\\n";
        }
        os << "\\end{pMatrix}\n";
        return os;
    }
};


using qMatrix = Matrix<Num>;
using rMatrix = Matrix<double>;

#endif
