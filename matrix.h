#ifndef MATRIX_H
#define MATRIX_H

#include "item.h"
#include "num.h"
#include "vect.h"
#include <vector>
#include <cstring>

//class matrix : public vect {
//    std::vector<vect> _vec;
//    int _row, _col;
//public:
//    void input() {
//        for (int i = 0; i < _row; i++) {
//            for (int j = 0; j < _col; j++) {
//                _vec[i][j].input();
//            }
//        }
//    }
//    std::string latex() const {
//        std::string res = "\\begin{pmatrix}\n";
//        for (int i = 0; i < _row; i++) {
//            for (int j = 1; j < _col; j++) {
//                res += _vec[i][j].latex() + "&";
//            }
//            res += _vec[i][_col].latex() + "\\\\\n";
//        }
//        res += "\\end{pmatrix}\n";
//        return res;
//    }
//    matrix(int row, int col) : _row(row), _col(col), _vec(row, vect(col)) {}
//    std::vector<num>& operator[] (int r) {
//        return _vec[r - 1];
//    }
//    const std::vector<num>& operator[] (int r) const {
//        return _vec[r - 1];
//    }
//};

class matrix : public vect<vect<num>> {
    int _m;
public:
    matrix(int row, int col) : _m(col), vect<vect<num>>(row, vect<num>(col)) {}
    std::string latex() const {
        std::string res = "\\begin{pmatrix}\n";
        for (int i = 0; i < _n; i++) {
            for (int j = 1; j < _m; j++) {
                res += _v[i][j].latex() + "&";
            }
            res += _v[i][_m].latex() + "\\\\\n";
        }
        res += "\\end{pmatrix}\n";
        return res;
    }
};

#endif
