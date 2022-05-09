#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

#pragma once
using namespace std;

class Matrix
{
public:
  vector<vector<double> > data;
  int rows;
  int columns;
  Matrix(int i, int j);

  ~Matrix();

  void printMatrix();

  void addScalar(double scalar);
  void addMatrix(Matrix matrix);
  static Matrix matrixSubstract(Matrix m1, Matrix m2);
  void multiply(Matrix a);
  static Matrix transpose(Matrix a);
  static Matrix multiply(Matrix a, Matrix b);
};

#endif