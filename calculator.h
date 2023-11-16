#ifndef CALC_H
#define CALC_H

#include "num.h"
#include "vector.h"
#include "matrix.h"

using qMatrix = Matrix<Num>;
using rMatrix = Matrix<double>;

using qrowVector = rowVector<Num>; // row vector in Q^n
using rrowVector = rowVector<double>; // row vector in R^n
using qcolVector = colVector<Num>; // column vector in Q^n
using rcolVector = colVector<double>; // column vector in R^n

#endif
