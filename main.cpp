#include <iostream>

#include "myrust.h"

int main() {
  int32_t a = 3;
  int32_t b = 4;
  const auto result = add(a, b);
  std::cout << a << " + " << b << " = " << result << std::endl;
  const auto mul_result = mul(a, b);
  std::cout << a << " * " << b << " = " << mul_result << std::endl;
  return 0;
}
