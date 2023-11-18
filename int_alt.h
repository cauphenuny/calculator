#pragma once

#include "debug.h"

// Integer 1:
// 实现一个有符号的大整数类，只需支持简单的加减

// Integer 2:
// 实现一个有符号的大整数类，支持加减乘除，并重载相关运算符

// 请不要使用除了以下头文件之外的其它头文件
#include <complex>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

// 请不要使用 using namespace std;

namespace sjtu {

class int2048 {
    // todo
  public:
    // 构造函数
    int2048();
    int2048(long long);
    int2048(const std::string &);
    int2048(const int2048 &);

    // 以下给定函数的形式参数类型仅供参考，可自行选择使用常量引用或者不使用引用
    // 如果需要，可以自行增加其他所需的函数
    // ===================================
    // Integer1
    // ===================================

    // 读入一个大整数
    void read(const std::string &);
    // 输出储存的大整数，无需换行
    void print();

    // 加上一个大整数
    int2048 &add(const int2048);
    // 返回两个大整数之和
    friend int2048 add(int2048, const int2048);

    // 减去一个大整数
    int2048 &minus(const int2048);
    // 返回两个大整数之差
    friend int2048 minus(int2048, const int2048);

    // ===================================
    // Integer2
    // ===================================

    int2048 operator+() const;
    int2048 operator-() const;

    int2048 &operator=(const int2048);

    int2048 &operator+=(const int2048);
    friend int2048 operator+(int2048, const int2048);

    int2048 &operator-=(const int2048);
    friend int2048 operator-(int2048, const int2048);

    int2048 &operator*=(const int2048);
    friend int2048 operator*(int2048, const int2048);

    int2048 &operator/=(const int2048);
    friend int2048 operator/(int2048, const int2048);

    int2048 &operator%=(const int2048);
    friend int2048 operator%(int2048, const int2048);

    friend std::istream &operator>>(std::istream &, int2048 &);
    friend std::ostream &operator<<(std::ostream &, const int2048 &);

    friend bool operator==(const int2048 &, const int2048 &);
    friend bool operator!=(const int2048 &, const int2048 &);
    friend bool operator<(const int2048 &, const int2048 &);
    friend bool operator>(const int2048 &, const int2048 &);
    friend bool operator<=(const int2048 &, const int2048 &);
    friend bool operator>=(const int2048 &, const int2048 &);

    int tota;int sym;
    std::vector<int> a;
};

const int Amodd = 10000000;
const int zip = 7;
const long long Amod = 1ll * 4179340454199820289, Ag = 3,
                Agi = 1ll * 1393113484733273430;
// const int modd = 10000;
// const int zip = 4;
// const long long mod = 1ll * 998244353, g = 3, gi = 1ll * 332748118;
int Ar[(1 << 19) + 10];
int lim;
long long Ap[500010], Aq[500010];
int2048 temp;
int2048::int2048() {
    //debugi << "()\n";
    int i;
    if (a.size()) {
        for (i = 0; i < a.size(); i++) a[i] = 0;
    } else
        a.push_back(0);
    tota = 0;
    sym = 1;
}
int2048::int2048(long long x) {
    //debugi << "(long long)\n";
    int i;
    if (a.size()) {
        for (i = 0; i < a.size(); i++) a[i] = 0;
    }
    tota = -1;
    sym = (x < 0 ? -1 : 1);
    x *= sym;
    while (x) {
        tota++;
        if (a.size() > tota)
            a[tota] = x % Amodd;
        else
            a.push_back(x % Amodd);
        x /= Amodd;
    }
    if (tota < 0) {
        tota = 0;
        a.push_back(0);
    }
    //debugi << "done\n";
}
int2048::int2048(const std::string &s) {
    //debugi << "(string)\n";
    tota = -1;
    int j, m = s.length(), beg;
    if (a.size()) {
        for (int i = 0; i < a.size(); i++) a[i] = 0;
    }
    sym = (1 - ((s[0] == '-') << 1));
    beg = (s[0] == '-');
    for (int i = m - 1; i >= beg; i -= zip) {
        tota++;
        if (a.size() > tota)
            a[tota] = 0;
        else
            a.push_back(0);
        for (j = std::max(beg, i - zip + 1); j <= i; j++)
            a[tota] = (a[tota] << 1) + (a[tota] << 3) + (s[j] & 15);
    }
    while (tota && !a[tota]) tota--;
    if (!a[tota]) sym = 1;
}
int2048::int2048(const int2048 &x) {
    //debugi << "(copy)\n";
    int i;
    if (a.size()) {
        for (i = 0; i < a.size(); i++) a[i] = 0;
    }
    tota = x.tota;
    //debugil(tota);
    sym = x.sym;
    for (i = 0; i <= tota; i++) {
        //debugil(i);
        if (a.size() > i)
            a[i] = x.a[i];
        else
            a.push_back(x.a[i]);
    }
}
int2048 &int2048::operator=(const int2048 x) {
    int i, j = a.size();
    for (i = 0; i < j; i++) a[i] = 0;
    for (i = j; i <= x.tota; i++) a.push_back(0);
    tota = x.tota;
    sym = x.sym;
    for (i = 0; i <= tota; i++) a[i] = x.a[i];
    return (*this);
}
int2048 int2048::operator+() const {
    return (*this);
}
int2048 int2048::operator-() const {
    int2048 y = (*this);
    y.sym *= -1;
    return y;
}
void int2048::print() {
    int i, j;
    if (sym == -1) printf("-");
    for (i = tota; i >= 0; i--) {
        int t = 1;
        if (i == tota) {
            printf("%d", a[i]);
            continue;
        }
        for (j = 1; j < zip; j++) {
            t *= 10;
            if (!(a[i] / t)) printf("0");
        }
        printf("%d", a[i]);
    }
    return;
}
void int2048::read(const std::string &s) {
    int j, m = s.length(), beg, x = a.size();
    //  printf("%d %d ",tota,m);
    if (a.size()) {
        for (int i = 0; i < a.size(); i++) a[i] = 0;
    }
    tota = -1;
    sym = (1 - ((s[0] == '-') << 1));
    beg = (s[0] == '-');
    for (int i = m - 1; i >= beg; i -= zip) {
        tota++;
        if (tota >= x) a.push_back(0);
        for (j = std::max(beg, i - zip); j <= i; j++)
            a[tota] = (a[tota] << 1) + (a[tota] << 3) + (s[j] & 15);
    }
    if (!a[tota]) sym = 1;
    //  (*this).print();
    //  printf("!%d\n", (*this).a[2]);
    return;
}
int2048 &int2048::add(const int2048 xx) {
    int2048 x = xx;
    int i, j, m = std::max(tota, x.tota), seg = sym * x.sym, com = 0;
    while (a.size() <= m + 1) a.push_back(0);
    while (x.a.size() <= m + 1) x.a.push_back(0);
    for (i = m; i >= 0; i--) {
        if (a[i] > x.a[i]) {
            com = 1;
            break;
        }
        if (a[i] < x.a[i]) {
            com = -1;
            break;
        }
    }
    //  printf("!!!"); (*this).print(); printf("\n");
    //  x.print(); printf("\n");
    if (seg == 1) {
        while (a.size() <= m + 2) a.push_back(0);
        while (x.a.size() <= m + 2) x.a.push_back(0);
        for (i = 0; i <= m; i++) a[i] += x.a[i];
        //	printf("$ %d ",a[2]);
        for (i = 0; i <= m; i++)
            if (a[i] >= Amodd) {
                a[i + 1]++;
                a[i] -= Amodd;
            }
        //	if (a[m+1])printf("!");
        m += (a[m + 1] != 0);
        tota = m;
        //	printf("!%d %d ",tota, a[tota+1]);
        //	(*this).print();
        //	printf("\n");
        return (*this);
    }
    //  printf("! %d %d\n", sym, com);
    for (i = 0; i <= m; i++) a[i] = a[i] * com + x.a[i] * com * (-1);
    for (i = 0; i <= m; i++)
        if (a[i] < 0) {
            a[i] += Amodd;
            a[i + 1] -= 1;
        }
    tota = m;
    while (!a[tota] && tota > 0) tota--;
    sym *= com;
    if (!a[tota]) sym = 1;
    return (*this);
}
int2048 add(int2048 y, const int2048 x) {
    return y.add(x);
}
int2048 &int2048::minus(const int2048 x) {
    //  printf("m");
    sym *= -1;
    (*this).add(x);
    sym *= -1;
    if (!a[tota]) sym = 1;
    return (*this);
}
int2048 minus(int2048 y, const int2048 x) {
    return y.minus(x);
}
int2048 operator+(int2048 y, const int2048 x) {
    return add(y, x);
}
int2048 operator-(int2048 y, const int2048 x) {
    return minus(y, x);
}
long long qpow(long long x, long long y) {
    long long now = 1;
    while (y) {
        if (y & 1) now = ((__int128)now * (__int128)x % (__int128)Amod);
        x = ((__int128)x * (__int128)x % (__int128)Amod);
        y >>= 1;
    }
    return now;
}
void NTT(long long *b, int lim, int opt) {
    int i, j, mid, k;
    long long x, y, w, gn;
    //  for (i = 0; i < lim; i++) b[i] = q[i];
    for (i = 0; i < lim; i++)
        if (i < Ar[i]) std::swap(b[i], b[Ar[i]]);
    for (mid = 2; mid <= lim; mid <<= 1) {
        gn = qpow(opt == 1 ? Ag : Agi, (Amod - 1) / mid);
        k = mid >> 1;
        for (i = 0; i < lim; i += mid) {
            w = 1;
            for (j = i; j < i + k; j++) {
                x = b[j];
                y = ((__int128)b[j + k] * (__int128)w % (__int128)Amod);
                b[j] = (((__int128)x + (__int128)y) % (__int128)Amod);
                b[j + k] = (((__int128)x - (__int128)y + (__int128)Amod) %
                            (__int128)Amod);
                w = ((__int128)w * (__int128)gn % (__int128)Amod);
            }
        }
    }
    if (opt == -1) {
        //    for (k = 1; k <= (lim >> 1); k++) {x = b[i]; b[i] = b[lim - i];
        //    b[lim - i] = x;} std:: reverse (b + 1, b + lim - 1);
        long long inv = qpow(lim, Amod - 1ll * 2);
        for (i = 0; i < lim; i++)
            b[i] = ((__int128)b[i] * (__int128)inv % (__int128)Amod);
    }
    return;
}
int2048 operator*(int2048 y, const int2048 x) {
    //  printf ("%lld\n", qpow(g, (mod - 2)));
    int i, j, m = std::max(y.tota, x.tota), seg = y.sym * x.sym, lim = 1,
              lglim = 0;
    while (lim < ((m + 1) << 1)) lim <<= 1, lglim++;
    y.a.reserve(lim);
    while (y.a.size() < lim) y.a.push_back(0);
    for (i = 0; i < lim; i++) {
        Ar[i] = (Ar[i >> 1] >> 1) | ((i & 1) << lglim - 1);
        Ap[i] = y.a[i];
        if (i <= x.tota)
            Aq[i] = x.a[i];
        else
            Aq[i] = 0;
    }
    //  for (i = 0; i < lim; i++) printf("%lld ", Ap[i]); printf("\n");
    //  for (i = 0; i < lim; i++) printf("%lld ", Aq[i]); printf("\n");
    NTT(Ap, lim, 1);
    NTT(Aq, lim, 1);
    for (i = 0; i < lim; i++)
        Ap[i] = ((__int128)Ap[i] * (__int128)Aq[i] % (__int128)Amod);
    NTT(Ap, lim, -1);
    for (i = lim - 1; i >= 0; i--)
        if (Ap[i]) {
            y.tota = i;
            break;
        }
    //  for (i = 0; i <= y.tota; i++) printf("%lld ", Ap[i]); printf("\n");
    for (i = 0; i <= y.tota; i++)
        if (Ap[i] >= (long long)Amodd) {
            Ap[i + 1] += Ap[i] / (long long)Amodd;
            Ap[i] %= (long long)Amodd;
        }
    //	for (i = 0; i <= y.tota; i++) printf("%lld ", Ap[i]); printf("\n");
    while (Ap[y.tota + 1]) {
        Ap[y.tota + 1] += Ap[y.tota] / (long long)Amodd;
        Ap[y.tota] %= (long long)Amodd;
        y.tota++;
    }
    for (i = 0; i <= y.tota; i++) y.a[i] = (int)Ap[i];
    for (i = y.tota + 1; i <= lim - 1; i++) y.a[i] = 0;
    for (i = 0; i < lim; i++) {
        Ap[i] = 0;
        Aq[i] = 0;
    }
    y.sym *= x.sym;
    return y;
}
int2048 &int2048::operator+=(const int2048 x) {
    return (*this).add(x);
}
int2048 &int2048::operator-=(const int2048 x) {
    return (*this).minus(x);
}
int2048 &int2048::operator*=(const int2048 x) {
    int2048 y = (*this);
    y = (y * x);
    (*this) = y;
    return (*this);
}
std::istream &operator>>(std::istream &is, int2048 &y) {
    long long s;
    is >> s;
    //   int2048 x(s);
    y = s;
    return is;
}
std::ostream &operator<<(std::ostream &os, const int2048 &y) {
    int i, j;
    if (y.sym == -1) os << "-";
    for (i = y.tota; i >= 0; i--) {
        int t = 1;
        if (i == y.tota) {
            os << y.a[i];
            continue;
        }
        for (j = 1; j < zip; j++) {
            t *= 10;
            if (!(y.a[i] / t)) os << "0";
        }
        os << y.a[i];
    }
    return os;
}
bool operator==(const int2048 &x, const int2048 &y) {
    if (x.tota != y.tota || x.sym != y.sym) return 0;
    for (int i = 0; i <= x.tota; i++)
        if (x.a[i] != y.a[i]) return 0;
    return 1;
}
bool operator!=(const int2048 &x, const int2048 &y) {
    return 1 ^ (x == y);
}
bool operator<(const int2048 &x, const int2048 &y) {
    if (x.sym != y.sym) return (x.sym == -1);
    if (x.tota != y.tota) return (x.tota < y.tota) ^ (x.sym == -1);
    for (int i = x.tota; i >= 0; i--) {
        if (x.a[i] < y.a[i]) return (x.sym == 1);
        if (x.a[i] > y.a[i]) return (x.sym == -1);
    }
    return 0;
}
bool operator>(const int2048 &x, const int2048 &y) {
    return y < x;
}
bool operator<=(const int2048 &x, const int2048 &y) {
    return (x < y || x == y);
}
bool operator>=(const int2048 &x, const int2048 &y) {
    return y <= x;
}
int get_dig(int2048 x) {
    int i, j = 0;
    while (x.a[x.tota]) {
        x.a[x.tota] /= 10;
        j++;
    }
    j += x.tota * zip;
    return j;
}
int2048 timesten(int2048 x, int y) {
    int i, j, k;
    if (y == 0) return x;
    if (y > 0) {
        j = y / zip;
        k = (int)qpow(1ll * 10, 1ll * y % zip);
        x.a.reserve(x.tota + 1 + j + 1);
        while (x.a.size() < x.tota + 1 + j + 1) x.a.push_back(0);
        x.tota += j;
        for (i = x.tota; i >= j; i--) x.a[i] = x.a[i - j];
        for (i = j - 1; i >= 0; i--) x.a[i] = 0;
        for (i = x.tota; i >= j; i--) {
            x.a[i + 1] += x.a[i] / (Amodd / k);
            x.a[i] = (x.a[i] % (Amodd / k)) * k;
        }
        if (x.a[x.tota + 1]) x.tota++;
    }
    if (y < 0) {
        j = (-y) / zip;
        k = (int)qpow(1ll * 10, 1ll * (-y) % zip);
        x.tota -= j;
        if (x.tota < 0) x.tota = 0;
        for (i = 0; i <= x.tota; i++) x.a[i] = x.a[i + j];
        for (i = x.tota + 1; i <= x.tota + j; i++) x.a[i] = 0;
        for (i = 0; i <= x.tota; i++) {
            x.a[i] /= k;
            if (i != x.tota) x.a[i] += (x.a[i + 1] % k) * (Amodd / k);
        }
        if (!x.a[x.tota] && x.tota) x.tota--;
    }
    //  printf("!!!"); fflush(stdout);
    return x;
}
int2048 miner_change(int2048 x, int2048 y,
                            int2048 z, int range) {
    int tmp = x.sym;
    //  z.sym = x.sym * y.sym;
    x.sym = 1;
    y.sym = 1;
    z.sym = 1;
    long long x1 = -range, x2 = range, mi = 0;
    bool opt;
    int2048 w;
    if (!x.tota && x.a[0] < range) {
        x1 = -x.a[0];
        x2 = x.a[0];
    }
    while (x1 != x2) {
        mi = (x1 + x2 + 1) >> 1;
        //	x.a.push_back(1); x.tota ++;
        w = (int2048)mi;
        opt = ((x + w) * y <= z);
        //	x.print(); printf(" ");
        //	y.print(); printf(" ");
        //	(x * y).print(); printf(" ");
        //	z.print(); printf(" %d %d \n",(x * y).tota, z.tota);
        if (opt)
            x1 = mi;
        else
            x2 = mi - 1;
    }
    x += (int2048)x1;
    x.sym = tmp;
    if (!x.a[x.tota]) x.sym = 1;
    return x;
}
int2048 divide(int2048 x) {
    int i, j = get_dig(x);
    i = (j + 2) >> 1;
    if (j <= 3) {
        x.a[0] = qpow(10, j << 1) / x.a[0];
        return x;
    }
    int2048 y = divide(timesten(x, i - j));
    y = timesten(y, j - i) + timesten(y, j - i) -
        timesten(y * y * x, -(i << 1));
    y = miner_change(y, x, timesten((int2048)1, j << 1), 100);
    return y;
}
int2048 operator/(int2048 y, const int2048 xx) {
    int i, j, tmp;
    int2048 x = xx, yy;
    if (x.sym == y.sym) {
        x.sym = 1;
        y.sym = 1;
    } else {
        x.sym = -1;
        y.sym = 1;
    }
    tmp = x.sym;
    x.sym = 1;
    //  x.sym *= y.sym;
    if (x.tota > y.tota) return (int2048)0;
    if (y.tota >= (x.tota << 1)) {
        j = y.tota - (x.tota << 1) + 1;
        //	printf("!%d\n", j);
        y.tota += j;
        x.tota += j;
        y.a.reserve(y.tota + 1);
        x.a.reserve(x.tota + 1);
        while (y.a.size() < y.tota) y.a.push_back(0);
        while (x.a.size() < x.tota) x.a.push_back(0);
        for (i = x.tota; i >= j; i--) x.a[i] = x.a[i - j];
        for (i = y.tota; i >= j; i--) y.a[i] = y.a[i - j];
        for (i = j - 1; i >= 0; i--) {
            x.a[i] = 0;
            y.a[i] = 0;
        }
    }
    yy = x;
    j = get_dig(x);
    //  x.print(); printf("\n");
    x = divide(x);
    //  x.print(); printf("\n");
    x *= y;
    x = timesten(x, -(j << 1));
    //  x.print(); printf("\n");

    //  yy.print(); printf("\n");

    //  y.print(); printf("\n");
    //  x.print(); printf("\n");
    //  x.sym = tmp;
    //  x.print(); printf("\n");
    //  yy.print(); printf("\n");
    //  y.print(); printf("\n");
    x = miner_change(x, yy, y, 10);
    //  w.print(); printf("\n");
    //  x.print(); printf("\n");
    //  printf("%d\n", (x * yy <= y));
    x.sym = tmp;
    if (x.sym == -1 && x * yy < y) x -= 1;
    x.sym *= y.sym;
    return x;
}
int2048 operator%(int2048 y, const int2048 xx) {
    return y - (y / xx) * xx;
}
int2048 &int2048::operator/=(const int2048 x) {
    int2048 y = (*this);
    y = (y / x);
    (*this) = y;
    return (*this);
}
int2048 &int2048::operator%=(const int2048 x) {
    int2048 y = (*this);
    y = (y % x);
    (*this) = y;
    return (*this);
}
}
