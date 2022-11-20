#include "set.h"

#include <iostream>

int main(void) {
  Set<int> s1;

  Set<int> s{ 1, 8, 2, 5, 7, 6, 3, 4, 5 };
  for (const auto &item : s) std::cout << item << ' ';
  std::cout << std::endl;

  return 0;
}
