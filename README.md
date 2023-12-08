# calculator

plan to implement some scientific calculation, supporting LaTeX output.

- [x] 

- [x] rational num

- [x] vector

- [x] matrix

- [x] poly (with integer cofficient)

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

recommanded to use the GMP library. (compile option: `-DGMP $(pkg-config --cflags --libs gmp)`)

for others, use `-DALT1` or `-DALT2` to your complination option.

see: [int.h](int.h)
