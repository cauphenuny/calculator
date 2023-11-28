//#include "poly.h"
#include <iostream>
#include <vector>
#include "calculator.h"
int main() {
    using std::cin, std::cout, std::endl;
    //num a(1), b(3);
    //cin >> a >> b;
    //cout << a << endl << b << endl;
    //latex_print << a / 2 + b / 4 << "\n";
    //num c;
    //latex_print << c << "\n";
    //matrix m(2, 3);
    //m.input();
    //latex_print << m[0][0] << m[0][1] << m[0][2] << "\n";
    //m[1][2] = 0;
    //latex_print << m;
    //vect<num> v(3);
    //v.input();
    //std::cout << v.latex() << std::endl;
    //matrix<num> m(2, 3), n(2, 3);
    //std::cin >> m >> n;
    //std::cout << m + n;
    //char c;
    //std::cin >> c;
    using T = Num;
    Matrix<T> mat1 = {{3, 3,-4, 3},
                      {0, 6, 1, 1},
                      {5, 4, 2, 1},
                      {2, 3, 3, 2}};
    mat1.inverse();
    cout << mat1 << endl;
    auto rnd1 = Matrix<T>::rand(5, 5);
    auto rnd2 = Matrix<T>::rand(5, 5);
    cout << rnd1;
    auto rst = rnd1;
    rnd1.inverse();
    rnd1.inverse();
    assert(rnd1 == rst);
    //auto rst = rnd1 * rnd2;
    return 0;
}

