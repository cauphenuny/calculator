#ifndef ITEM_H 
#define ITEM_H

#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
using s64 = long long;
using u64 = unsigned long long;

s64 gcd(s64 a, s64 b) {
    return b == 0 ? a : gcd(b, a % b);
}

template<typename T> T read() {
    T a = 0, f = 0; char c = getchar();
    while (!isdigit(c)) { f = c == '-', c = getchar(); }
    while (isdigit(c)) { a = a * 10 + (c ^ 48), c = getchar(); }
    a *= f ? -1 : 1;
    return a;
}

class math_item {
    char end_char = ' ';
public:
    char input();
    char end() const {
        return end_char;
    }
    std::string latex() const;
};

//struct mathin_t {
//    template<typename T>
//    mathin_t& operator >> (T& x) { x = read<T>(); return *this; }
//    
//    template<typename T>
//    mathin_t& operator >> (T& m) { m.input(); return *this; }
//} mathin;
//
//struct mathout_t {
//    template<typename T>
//    mathout_t& operator << (const T& x) { std::cout << x; return *this; }
//    template<typename T>
//    mathout_t& operator << (const T& m) { m.prints(); return *this; }
//} mathout;

struct latexprt_t {
    latexprt_t& operator << (char c) { std::cout << c; return *this; }
    latexprt_t& operator << (const char *s) { std::cout << s; return *this; }
    latexprt_t& operator << (const std::string& s) { std::cout << s; return *this; }
    template<typename T>
    latexprt_t& operator << (const T& a) { std::cout << a.latex() << a.end(); return *this; }
} latex_print;

#endif
