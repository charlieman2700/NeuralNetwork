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

  Matrix();
  
  Matrix(int i, int j);

  ~Matrix();

  void printMatrix();
  void sigmoid();
  void addScalar(double scalar);
  void addMatrix(Matrix& matrix);
  static Matrix matrixSubstract(Matrix &m1, Matrix& m2);
  void multiply(Matrix& a);
  void multiply(double scalar);
  static Matrix transpose(Matrix& a);
  static Matrix multiply(Matrix &a, Matrix &b);
  static Matrix fromArray(vector<double> values);
  vector<double> toArray();
  Matrix dsigmoid();

};

#endif