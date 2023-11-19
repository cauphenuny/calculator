#pragma once

#include "vector.h"
#include "debug.h"
#include "rand.h"
#include <vector>
#include <string>
#include <cassert>

template<typename T>
class Matrix : public Vector<rowVector<T>> {
protected:
    size_t _m;
    Matrix<T>* _bind{nullptr};

public:
    Matrix(size_t row, size_t col):
        Vector<rowVector<T>>(row, rowVector<T>(col)), 
        _m(col) {
        //debuginfo;
    }
    Matrix(size_t row, size_t col, T t):
        Vector<rowVector<T>>(row, rowVector<T>(col, t)),
        _m(col) {
        //debuginfo;
    }
    Matrix(const Matrix<T>& mat):
        Vector<rowVector<T>>(mat),
        _m(mat._m) {
        //debuginfo;
    }
    Matrix(Matrix<T>&& mat):
        Vector<rowVector<T>>(mat),
        _m(mat._m) {
        //debugi << "copy constructor called";
    }
    Matrix<T>& operator= (const Matrix<T>& mat) {
        if (this != &mat) {
            Vector<rowVector<T>>::operator=(mat);
            _m = mat._m;
            _bind = mat._bind;
        }
        return *this;
    }
    Matrix<T>& operator= (Matrix<T>&& mat) {
        if (this != &mat) {
            Vector<rowVector<T>>::operator=(mat);
            _m = mat._m;
            _bind = mat._bind;
        }
        return *this;
    }

    const T& operator() (size_t r, size_t c) const {
        return (*this)[r][c];
    }
    T& operator() (size_t r, size_t c) {
        return (*this)[r][c];
    }
    void bind(Matrix<T>& mat) {
        _bind = &mat;
    }
    void unbind() {
        _bind = nullptr;
    }
    void swap(size_t row1, size_t row2) {
        (*this)[row1].swap((*this)[row2]);
        if (_bind != nullptr) {
            _bind->swap(row1, row2);
        }
    }
    void add(size_t row1, size_t row2, const T val) {
        //debug << "------------------------\n";
        //debugil(val);
        //debugil((*this)[row2][1]);
        (*this)[row1] += (*this)[row2] * val;
        if (_bind != nullptr) {
            _bind->add(row1, row2, val);
        }
    }
    void mul(size_t row, const T val) {
        (*this)[row] *= val;
        if (_bind != nullptr) {
            _bind->mul(row, val);
        }
    }
    void div(size_t row, const T val) {
        //debugil(row);
        (*this)[row] /= val;
        if (_bind != nullptr) {
            _bind->div(row, val);
        }
    }

    T det() const;
    size_t rank() const;

    Matrix<T> eliminate() {
        Matrix<T>& mat = *this;
        size_t col = 1, row = 1;
        size_t _n = mat._n;
        //debug << mat;
        while (row <= _n && col <= _m) {
            //debugil(row), debugil(col);
            size_t targ = 0; // target row
            for (size_t cand = row; cand <= _n; cand++) { // candidate row
                if (mat[cand][col] != T(0)) {
                    targ = cand;
                    break;
                }
            }
            //debugil(targ);
            if (!targ) {
                col++;
                continue;
            }
            if (row != targ) mat.swap(row, targ);
            //debug << "----before div " << mat[row][col] << "--------\n" << mat;
            mat.div(row, mat[row][col]);
            //debug << "----after div row " << row << " -----\n" << mat;
            for (size_t nrow = row + 1; nrow <= _n; nrow++) { // next row
                if (mat[nrow][col] != T(0)) {
                    //debug << "nrow " << nrow << "k = " << -mat[nrow][col] << std::endl;
                    mat.add(nrow, row, -mat[nrow][col]);
                }
            }
            //debug << "----after clearing column" << col << " -----\n" << mat;
            row++, col++;
        }
        return mat;
    }
    T det() {
        size_t _n = this->_n;
        assert(_n == _m);
        Matrix<T> mat(eliminate());
        T res = 1;
        for (size_t i = 1; i <= _n; i++) {
        }
    }
    size_t rank() {
        size_t _n = this->_n;
        Matrix<T> mat(eliminate());
        size_t r = 0, p = 0;
        while (r < _n) {
            bool empty = 1;
            while (p < _m) {
                p++;
                if (mat[r + 1][p] != 0) {
                    empty = 0;
                    break;
                }
            }
            if (empty) {
                break;
            } else {
                r++;
            }
        }
        return r;
    }
    Matrix<T> identify() {
        Matrix<T>& mat = *this;
        assert(mat._n == mat._m);
        mat.eliminate();
        debugi << "eliminated\n";
        for (size_t i = mat._n; i > 1; i--) {
            for (size_t j = i - 1; j >= 1; j--) {
                if (mat[j][i] != 0) {
                    add(j, i, -mat[j][i]);
                    //debug << mat;
                }
            }
        }
        debugi << "identified\n" << mat;
        return mat;
    }
    Matrix<T> inverse() {
        Matrix<T> tmp(*this);
        debugi << "copied\n";
        *this = Matrix<T>::id(this->_n);
        debugi << "reseted\n";
        tmp.bind(*this);
        debugi << "linked\n";
        tmp.identify();
        debugi << "calculated\n";
        return *this;
    }

    size_t rsize() const { return this -> _n; }
    size_t csize() const { return this -> _m; }

    friend void swap(Matrix<T>& mat1, Matrix<T>& mat2) {
        std::swap(mat1._n, mat2._n);
        std::swap(mat1._m, mat2._m);
        std::swap(mat1._data, mat2._data);
    }

    //using Vector<rowVector<T>>::operator==;
    //using Vector<rowVector<T>>::operator!=;

    using Vector<rowVector<T>>::operator+=;
    friend Matrix<T> operator+ (const Matrix<T>& mat1, const Matrix<T>& mat2) {
        Matrix<T> res(mat1);
        res += mat2;
        return res;
    }
    using Vector<rowVector<T>>::operator-=;
    friend Matrix<T> operator- (const Matrix<T>& mat1, const Matrix<T>& mat2) {
        Matrix<T> res(mat1);
        res -= mat2;
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
    using Vector<rowVector<T>>::operator*=;
    Matrix<T> operator* (const T val) {
        Matrix<T> res(*this);
        res *= val;
        return res;
    }
    friend Matrix<T> operator*(const T val, const Matrix<T>& mat) {
        Matrix<T> res(mat);
        res *= val;
        return res;
    }

    friend std::ostream& operator<< (std::ostream& os, const Matrix<T>& mat) {
        os << "\\begin{pmatrix}\n";
        auto n = mat.rsize(), m = mat.csize();
        for (size_t i = 1; i <= n; i++) {
            for (size_t j = 1; j < m; j++) {
                os << mat[i][j] << "&";
            }
            os << mat[i][m] << "\\\\\n";
        }
        os << "\\end{pmatrix}\n";
        return os;
    }

    static Matrix<T> id(int n) {
        Matrix<T> mat(n, n);
        for (int i = 1; i <= n; i++) {
            mat[i][i] = T(1);
        }
        return mat;
    }
    static Matrix<T> rand(int row, int col) {
        Matrix<T> mat(row, col);
        for (int i = 1; i <= row; i++) {
            for (int j = 1; j <= col; j++) {
                mat[i][j] = T(randint(-1000, 1000));
            }
        }
        return mat;
    }
};

