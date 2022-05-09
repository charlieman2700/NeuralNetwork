/*
  This code was based on the one presented in the following tutorial:
  https://towardsdatascience.com/understanding-and-implementing-neural-networks-in-java-from-scratch-61421bb6352c
*/
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
      // this->data[rowIndex][columnIndex] = -1 + (double)(rand()) / ((double)(RAND_MAX / (1 - -1)));
      this->data[rowIndex][columnIndex] = 3;
    }
  }
  this->rows = rows;
  this->columns = columns;
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

void Matrix::addScalar(double scalar)
{
  for (int rowIndex = 0; rowIndex < rows; rowIndex++)
  {
    for (int column = 0; column < this->columns; column++)
    {
      this->data[rowIndex][column] += scalar;
    }
  }
}

void Matrix::addMatrix(Matrix matrix)
{
  if (this->columns != matrix.columns || this->rows != matrix.rows)
  {
    cout << "The matrices have different shapes";
  }
  else
  {
    for (int row = 0; row < this->rows; row++)
    {
      for (int column = 0; column < this->columns; column++)
      {
        this->data[row][column] += matrix.data[row][column];
      }
    }
  }
}

Matrix Matrix::matrixSubstract(Matrix m1, Matrix m2)
{
  Matrix temp = *new Matrix(m1.rows, m1.columns);
  if (m1.columns != m2.columns || m1.rows != m2.rows)
  {
    cout << "The matrices have different shapes";
  }
  else
  {
    for (int row = 0; row < m1.rows; row++)
    {
      for (int column = 0; column < m1.columns; column++)
      {
        temp.data[row][column] = m1.data[row][column] - m2.data[row][column];
      }
    }
  }
  return temp;
}

Matrix Matrix::transpose(Matrix a)
{
  Matrix temp = *new Matrix(a.columns, a.rows);
  for (int row = 0; row < a.rows; row++)
  {
    for (int column = 0; column < a.columns; column++)
    {
      temp.data[column][row] = a.data[row][column];
    }
  }
  return temp;
}

void Matrix::multiply(Matrix a)
{
  for (int row = 0; row < a.rows; row++)
  {
    for (int column = 0; column < a.columns; column++)
    {
      this->data[row][column] *= a.data[row][column];
    }
  }
}

Matrix Matrix::multiply(Matrix a, Matrix b)
{
  Matrix temp = *new Matrix(a.rows, b.columns);

  if (a.columns != b.rows)
  {
    cout << "The matrices have different shapes";
  }
  else
  {

    for (int i = 0; i < temp.columns; i++)
    {

      for (int j = 0; j < temp.columns; j++)
      {
        double sumNumber = 0;
        for (int k = 0; k < a.columns; k++)
        {
          sumNumber += a.data[i][k] * b.data[k][j];
        }
        temp.data[i][j] = sumNumber;
      }
    }
  }
  return temp;
}
