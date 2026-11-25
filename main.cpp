#include <iostream>

#include "myrust.h"

int main() {
  int32_t a = 3;
  int32_t b = 4;
  int32_t result = add(a, b);
  std::cout << a << " + " << b << " = " << result << std::endl;
  return 0;
}
