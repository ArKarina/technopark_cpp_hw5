#include "set.h"
#include "iterator.h"

#include <iostream>

int main(void) {
  Matrix<int> m1 = {{5, 2, 3}, {4, 7, 6}, {7, 8, 9}};

  std::cout << m1;

  return 0;
}
