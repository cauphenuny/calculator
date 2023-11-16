#ifndef MATRIX_H
#define MATRIX_H

#include "num.h"
#include "vect.h"
#include <vector>
#include <string>
#include <cassert>

template<typename T>
class matrix : public vect<vect<T>> {
protected:
    size_t _n, _m;

public:
    matrix(size_t row, size_t col) : vect<vect<T>>(row, vect<T>(col)), _n(row), _m(col) {}
    matrix(const vect<vect<T>>& v) : vect<vect<T>>(v), _n(v._n), _m(v[1].size()) {}
    matrix(matrix&& mat) : vect<vect<T>>(mat), _n(mat._n), _m(mat._m) {}

    const T& operator() (size_t r, size_t c) const {
        return this -> operator[](r)[c];
    }
    T& operator() (size_t r, size_t c) {
        return this -> operator[](r)[c];
    }

    T det() const;
    size_t rank() const;
    matrix inverse() const;
    friend void gauss();

    size_t rsize() const { return _n; }
    size_t csize() const { return _m; }

    friend matrix<T> operator+ (const matrix<T>& mat1, const matrix<T>& mat2) {
        assert(mat1._n == mat2._n), assert(mat1._m == mat2._m);
        size_t n = mat1._n, m = mat1._m;
        matrix<T> res(n, m);
        for (size_t i = 1; i <= n; i++) {
            res[i] = mat1[i] + mat2[i];
        }
        return res;
    }
    friend matrix<T> operator- (const matrix<T>& mat1, const matrix<T>& mat2) {
        assert(mat1._n == mat2._n), assert(mat1._m == mat2._m);
        size_t n = mat1._n, m = mat1._m;
        matrix<T> res(n, m);
        for (size_t i = 1; i <= n; i++) {
            res[i] = mat1[i] - mat2[i];
        }
        return res;
    }
    friend matrix<T> operator* (const matrix<T>& mat1, const matrix<T>& mat2) {
        assert(mat1._m == mat2._n);
        matrix<T> res(mat1._n, mat2._m);
        for (size_t k = 1; k <= mat1._m; k++) {
            for (size_t i = 1; i <= mat1._n; i++) {
                for (size_t j = 1; j <= mat2._m; j++) {
                    res(i, j) += mat1(i, k) * mat2(k, j);
                }
            }
        }
        return res;
    }

    friend const std::string latex(const matrix<T>& mat) {
        std::string res = "\\begin{pmatrix}\n";
        auto n = mat.rsize(), m = mat.csize();
        for (size_t i = 1; i <= n; i++) {
            for (size_t j = 1; j < m; j++) {
                res += latex(mat(i, j)) + "&";
            }
            res += latex(mat(i, m)) + "\\\\\n";
        }
        res += "\\end{pmatrix}\n";
        return res;
    }
    friend std::ostream& operator<< (std::ostream& os, const matrix<T>& mat) {
        os << latex(mat);
        return os;
    }
};


using q_matrix = matrix<num>;

#endif
