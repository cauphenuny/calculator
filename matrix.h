#ifndef MATRIX_H
#define MATRIX_H

#include "item.h"
#include "num.h"
#include <vector>
#include <cstring>

class matrix : public math_item {
    std::vector<vect> _vec;
    int _row, _col;
public:
    void input() {
        for (int i = 0; i < _row; i++) {
            for (int j = 0; j < _col; j++) {
                _vec[i][j].input();
            }
        }
    }
    std::string latex() const {
        std::string res = "\\begin{pmatrix}\n";
        for (int i = 0; i < _row; i++) {
            for (int j = 0; j < _col - 1; j++) {
                res += _vec[i][j].latex() + "&";
            }
            res += _vec[i][_col - 1].latex() + "\\\\\n";
        }
        res += "\\end{pmatrix}\n";
        return res;
    }
    matrix(int row, int col) : _row(row), _col(col), _vec(row, std::vector<num>(col)) {}
    std::vector<num>& operator[] (int r) {
        return _vec[r];
    }
    const std::vector<num>& operator[] (int r) const {
        return _vec[r];
    }
};

#endif
