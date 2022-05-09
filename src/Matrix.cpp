#include "Matrix.hpp"
#include <vector>
#include "iostream"
#include "stdlib.h"
#include "time.h"
#include "cstdlib"

using namespace std;

// double initNeuron() { return ((double)rand()) / RAND_MAX; }
Matrix::Matrix(int rows, int columns)
{
  srand(time(NULL));
  this->data.resize(rows);

  for (int rowIndex = 0; rowIndex < rows; rowIndex++)
  {
    this->data[rowIndex].resize(columns);
    for (int columnIndex = 0; columnIndex < columns; columnIndex++)
    {
      this->data[rowIndex][columnIndex] = -1 + (double)(rand()) / ((double)(RAND_MAX / (1 - -1)));
    }
  }
}

Matrix::~Matrix()
{
  this->data.clear();
}

void Matrix::printMatrix()
{
  for (size_t rowIndex = 0; rowIndex < this->data.size(); rowIndex++)
  {
    for (size_t columnIndex = 0; columnIndex < data[0].size(); columnIndex++)
    {
      cout << this->data[rowIndex][columnIndex] << " ";
    }
    cout << "\n";
  }
}
