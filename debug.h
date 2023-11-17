#ifndef DEBUG_H
#define DEBUG_H

#include <cstdio>
#include <iostream>

#define debugw(x) std::cerr << #x << " = " << (x) << " "
#define debugl(x) std::cerr << #x << " = " << (x) << std::endl
#define debugi std::cerr << __FILE__ << ":" << __LINE__ << ", " << __func__ << ": "
#define debugil(x) std::cerr << __FILE__ << ":" << __LINE__ << ", " << __func__ << ": " << #x << " = " << (x) << std::endl
#define debug std::cerr 

#endif
