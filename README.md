# calculator

计划实现一些科学计算，支持 LaTeX 输出。

- [x] 自适应精度

- [x] 有理数

- [x] 向量

- [x] 矩阵

- [x] 整系数多项式

- [ ] 多变量多项式

## demo

[demo.cpp](demo.cpp)

## usage

```cpp
#include "calculator.h"
int main() {
    /*
        ...
    */
    return 0;
}
```

using `long long` as default;

for others, add `-DALT1` or `-DALT2` to your complination command.

e.g. `g++ demo.cpp -o demo -DALT1`

see: [int.h](int.h)
