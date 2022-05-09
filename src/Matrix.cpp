#include "Matrix.hpp"
#include <vector>
#include "iostream"

using namespace std;

Matrix::Matrix(int rows, int columns)
{
  this->data.resize(rows);

  for (int rowIndex = 0; rowIndex < rows; rowIndex++)
  {
    this->data[rowIndex].resize(columns);
    for (int columnIndex = 0; columnIndex < columns; columnIndex++)
    {
      this->data[rowIndex][columnIndex] = 1;
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
      cout << this->data[rowIndex][columnIndex];
    }
    cout << "\n";
  }
}
