#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

#pragma once
using namespace std;

class Matrix
{
public:
  vector<vector<double> > data;

  Matrix(int i, int j);

  ~Matrix();

  void printMatrix();

private:
};

#endif