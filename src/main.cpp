#include <iostream>
#include "Matrix.hpp"

int main()
{
  std::cout << "Hello World!" << std::endl;
  Matrix *matriz1 = new Matrix(2, 4);
  matriz1->printMatrix();

  return 0;
}
