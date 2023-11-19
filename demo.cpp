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
    debugl(sizeof(Num));
    debugl(sizeof(Vector<Num>));
    debugl(sizeof(Matrix<Num>));
    debugl(sizeof(std::vector<int>));
    debugl(sizeof(MemoryPool<int>));
    debugl(sizeof(Integer));
    //Matrix<double> m(4, 4);
    //cin >> m;
    //cout << m;
    //cout << m * m;
    //Integer a(), b(3);
    //cout << a % b << endl;
    //return 0;
    auto rnd1 = Matrix<Num>::rand(3, 3);
    auto res = rnd1;
    rnd1 /= randint(10, 20);
    cout << rnd1;
    rnd1.inverse();
    cout << rnd1;
    cout << rnd1 * res;
    return 0;
}

