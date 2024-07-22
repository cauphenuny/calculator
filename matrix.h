#pragma once

#if __cplusplus < 202300
#warning "c++23 recommended"
#endif

#include <vector>
#include <string>
#include <cassert>
#include "vector.h"
#include "debug.h"
#include "rand.h"
#include "util.h"

template <typename T> class Matrix : public Vector<Vector<T>> {
  protected:
    size_t _m;
    Matrix<T> *_bind{nullptr};

  public:

    using Vector<Vector<T>>::operator[];

#if __cplusplus >= 202300
    const T &operator[](size_t r, size_t c) const {
        return (*this)[r][c];
    }
    T &operator[](size_t r, size_t c) {
        return (*this)[r][c];
    }
#endif

    const T &operator()(size_t r, size_t c) const {
        return (*this)[r][c];
    }
    T &operator()(size_t r, size_t c) {
        return (*this)[r][c];
    }

    Matrix(size_t row, size_t col)
        : Vector<Vector<T>>(row, Vector<T>(col)), _m(col) {
        // debuginfo;
    }
    Matrix(size_t row, size_t col, T t)
        : Vector<Vector<T>>(row, Vector<T>(col, t)), _m(col) {
        // debuginfo;
    }
    Matrix(const Matrix<T> &mat)
        : Vector<Vector<T>>(mat), _m(mat._m) {
        // debugi << "copy constructor called";
    }
    Matrix(Matrix<T> &&mat)
        : Vector<Vector<T>>(mat), _m(mat._m) {
        // debugi << "move constructor called";
    }
    Matrix(std::initializer_list<Vector<T>> content)
        : Vector<Vector<T>>(content), _m(content.begin()->size()) {
    }
    Matrix(rowVector<T> vec)
        : Vector<Vector<T>>(1, vec), _m(vec.size()) {
    }
    Matrix(colVector<T> vec)
        : Vector<Vector<T>>(vec.size(), Vector<T>(1)), _m(1) {
        for (int i = 1; i <= vec.size(); i++) {
            (*this)[i][1] = vec[i];
        }
    }
    Matrix<T> &operator=(const Matrix<T> &mat) {
        if (this != &mat) {
            _m = mat._m;
            _bind = mat._bind;
            Vector<Vector<T>>::operator=(mat);
        }
        return *this;
    }
    Matrix<T> &operator=(Matrix<T> &&mat) {
        if (this != &mat) {
            _m = mat._m;
            _bind = mat._bind;
            Vector<Vector<T>>::operator=(mat);
        }
        return *this;
    }
    size_t rsize() const {
        return this->_n;
    }
    size_t csize() const {
        return this->_m;
    }

    Matrix<T> transpos() {
        size_t n = rsize(), m = csize();
        Matrix<T> mat(m, n);
        for (size_t i = 1; i <= n; i++) {
            for (size_t j = 1; j <= m; j++) {
                mat[j][i] = (*this)[i][j];
            }
        }
        return mat;
    }

    using Vector<Vector<T>>::operator==;
    using Vector<Vector<T>>::operator!=;

    using Vector<Vector<T>>::operator+=;
    friend Matrix<T> operator+(const Matrix<T> &mat1, const Matrix<T> &mat2) {
        Matrix<T> res(mat1);
        res += mat2;
        return res;
    }
    using Vector<Vector<T>>::operator-=;
    friend Matrix<T> operator-(const Matrix<T> &mat1, const Matrix<T> &mat2) {
        Matrix<T> res(mat1);
        res -= mat2;
        return res;
    }
    friend Matrix<T> operator*(const Matrix<T> &mat1, const Matrix<T> &mat2) {
        assert(mat1._m == mat2._n);
        Matrix<T> res(mat1._n, mat2._m);
        for (size_t k = 1; k <= mat1._m; k++) {
            for (size_t i = 1; i <= mat1._n; i++) {
                for (size_t j = 1; j <= mat2._m; j++) {
                    res[i][j] += mat1[i][k] * mat2[k][j];
                }
            }
        }
        return res;
    }
    friend Matrix<T> operator*(const Matrix<T> &mat, const colVector<T> &vec) {
        return mat * Matrix<T>(vec);
    }
    friend Matrix<T> operator*(const rowVector<T> &vec, const Matrix<T> &mat) {
        return Matrix<T>(vec) * mat;
    }
    Matrix<T>& operator*=(const Matrix<T> &mat) {
        (*this) = (*this) * mat;
        return (*this);
    }
    using Vector<Vector<T>>::operator*=;
    Matrix<T> operator*(const T val) {
        Matrix<T> res(*this);
        res *= val;
        return res;
    }
    friend Matrix<T> operator*(const T val, const Matrix<T> &mat) {
        Matrix<T> res(mat);
        res *= val;
        return res;
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &mat) 
        requires printable<T>
    {
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

    Matrix<T> operator^(unsigned p) requires (!divisible<T, T>) {
        assert(rsize() == csize());
        Matrix<T> base = (*this);
        Matrix<T> ans = id(rsize());
        while (p) {
            if (p & 1) {
                ans *= base;
            }
            base *= base;
            p /= 2;
        }
        return ans;
    }
    Matrix<T> operator^(int p) requires divisible<T, T> {
        assert(rsize() == csize());
        Matrix<T> base = (*this);
        Matrix<T> ans = id(rsize());
        if (p < 0) {
            base = base.inverse();
            p = -p;
        }
        while (p) {
            if (p & 1) {
                ans *= base;
            }
            base *= base;
            p /= 2;
        }
        return ans;
    }
    friend void swap(Matrix<T> &mat1, Matrix<T> &mat2) {
        std::swap(mat1._n, mat2._n);
        std::swap(mat1._m, mat2._m);
        std::swap(mat1._data, mat2._data);
    }

    static Matrix<T> zero(int n) {
        Matrix<T> mat(n, n);
        for (int i = 1; i <= n; i++) {
            mat[i][i] = T(0);
        }
        return mat;
    }

    static Matrix<T> id(int n) {
        Matrix<T> mat(n, n);
        for (int i = 1; i <= n; i++) {
            mat[i][i] = T(1);
        }
        return mat;
    }

    static Matrix<T> diag(std::initializer_list<T> array) {
        size_t n = array.size();
        Matrix<T> mat(n, n, 0);
        auto it = array.begin();
        for (size_t i = 1; i <= n; i++, it++) {
            mat[i][i] = *it;
        }
        return mat;
    }

    static Matrix<T> rand(int row, int col,
                          std::initializer_list<T> range = {-10, 10}) {
        Matrix<T> mat(row, col);
        int minv = *(range.begin());
        int maxv = *(std::next(range.begin()));
        int div = 0;
        do {
            div = randint(minv, maxv);
        } while (div == 0);
        for (int i = 1; i <= row; i++) {
            for (int j = 1; j <= col; j++) {
                mat[i][j] = T(randint(minv, maxv)) / div;
            }
        }
        return mat;
    }

    void bind(Matrix<T> &mat) {
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
  private:
    void add(size_t row1, size_t row2, const T val)
        requires addable<decltype((*this)[0])> && 
                 multipliable<decltype((*this)[0]), T>
    {
        // debug << "------------------------\n";
        // debugil(val);
        // debugil((*this)[row2, 1]);
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
        // debugil(row);
        (*this)[row] /= val;
        if (_bind != nullptr) {
            _bind->div(row, val);
        }
    }
  public:

    size_t rank();

    Matrix<T> eliminate() {
        Matrix<T> &mat = *this;
        size_t col = 1, row = 1;
        size_t n = mat._n, m = mat._m;
        // debug << mat;
        while (row <= n && col <= m) {
            // debugil(row), debugil(col);
            size_t targ = 0;                              // target row
            for (size_t cand = row; cand <= n; cand++) { // candidate row
                if (mat[cand][col] != T(0)) {
                    targ = cand;
                    break;
                }
            }
            // debugil(targ);
            if (!targ) {
                col++;
                continue;
            }
            if (row != targ) mat.swap(row, targ);
            // debug << "----before div " << mat[row, col] << "--------\n" <<
            // mat; debug << "----after div row " << row << " -----\n" << mat;
            for (size_t nrow = row + 1; nrow <= n; nrow++) { // next row
                if (mat[nrow][col] != T(0)) {
                    // debug << "nrow " << nrow << "k = " << -mat[nrow, col] <<
                    // std::endl;
                    mat.add(nrow, row, -mat[nrow][col] / mat[row][col]);
                }
            }
            // debug << "----after clearing column" << col << " -----\n" << mat;
            row++, col++;
        }
        return mat;
    }
    T det() const {
        size_t _n = this->_n;
        assert(_n == _m);
        Matrix<T> mat(*this);
        mat.eliminate();
        T res = 1;
        for (size_t i = 1; i <= _n; i++) {
            res *= mat[i][i];
        }
        return res;
    }
    size_t rank() const {
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
        Matrix<T> &mat = *this;
        assert(mat._n == mat._m);
        mat.eliminate();
        // debugi << "eliminated\n";
        for (size_t i = mat._n; i > 1; i--) {
            mat.div(i, mat[i][i]);
            for (size_t j = i - 1; j >= 1; j--) {
                if (mat[j][i] != T(0)) {
                    mat.add(j, i, -mat[j][i]);
                    // debug << mat;
                }
            }
        }
        mat.div(1, mat[1][1]);
        // debugi << "identified\n";
        return mat;
    }

    Matrix<T> inverse() const {
        Matrix<T> tmp(*this);
        // debugi << "copied\n";
        Matrix<T> ans = id(rsize());
        // debugi << "reseted\n";
        tmp.bind(ans);
        // debugi << "linked\n";
        tmp.identify();
        // debugi << "calculated\n";
        return ans;
    }

    Matrix<T> operator/(const Matrix<T> &mat) {
        assert(mat.rsize() == mat.csize());
        return (*this) * mat.inverse();
    }
};

template<typename T>
