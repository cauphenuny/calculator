//#include "poly.h"
#include <iostream>
#include <vector>
#include "calculator.h"
int main() {
    using std::cin, std::cout, std::endl;
    using T = Num;

    Matrix<T> mat1 = {{3, 3,-4, 3},
                      {0, 6, 1, 1},
                      {5, 4, 2, 1},
                      {2, 3, 3, 2}};
    cout << "-- mat1 --\n" << mat1.inverse() << endl;
    cout << mat1 * mat1 * (mat1 ^ -2) << endl;

    auto mat2 = Matrix<T>::diag({1, 2, 3, 4});
    cout << "-- mat2 --\n" << mat2 << endl;

    auto rnd1 = Matrix<T>::rand(5, 5);
    auto rnd2 = Matrix<T>::rand(5, 5, {-100, 100});
    assert(rnd1 == ((rnd1 ^ -1) ^ -1));
    cout << "-- rnd --\n" << rnd1 << "\n" << rnd2 << endl;

    colVector<T> vec{3, 2, 1, 4};
    cout << "-- vec --\n" << vec << "\n" << mat1 * vec << endl;

    return 0;
}

