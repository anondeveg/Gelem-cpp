#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using Dim = std::tuple<int, int>;
using Mat = std::vector<std::vector<double>>;
using vec = std::vector<double>;

template <typename T> void printContainer(const std::vector<T> &vec) {
  std::cout << "--------------\n";
  for (T item : vec) {
    std::cout << item << "\n";
  }
  std::cout << "--------------\n";
}

class Matrix {

public:
  Dim Dimension;
  Mat matrix;
  double rowsize = 0;
  double columnsize = 0;

  Matrix(Mat mat, Dim Dimension) {
    this->matrix = mat;
    this->Dimension = Dimension;
    this->rowsize = std::get<0>(Dimension);
    this->columnsize = std::get<1>(Dimension);
    if (mat.size() == 0) {
      for (int i = 0; i < rowsize; i++) {
        matrix.push_back({});

        for (int j = 0; j < columnsize; j++) {
          matrix[i].emplace_back(0);
        }
      }
    }
  }

  static Matrix dot(Matrix m1, Matrix m2) {
    if (m1.columnsize != m2.rowsize) { // m1.col != m2.rowj
      throw std::invalid_argument(
          "INVALID OPERATION UNEQUAL DIMENSIONS! Matrix of columnsize " +
          std::to_string(m1.columnsize) + " and Matrix of rowsize of " +
          std::to_string(m2.rowsize));
    }

    Matrix matrixProduct({}, std::make_tuple(m1.rowsize, m2.columnsize));

    for (int i = 0; i < m1.columnsize /*2*/; i++) {
      vec m1_row = m1.getRow(i);
      for (int j = 0; j < m2.columnsize /*3*/; j++) {
        vec m2_col = m2.getCol(j);

        double sum{};
        for (unsigned int k = 0; k < m2_col.size(); k++) {

          sum += (m1_row[k] * m2_col[k]);
        }
        matrixProduct.matrix[i][j] = sum;
      }
    }

    return matrixProduct;
  }

  vec getRow(int n) { return this->matrix[n]; }
  vec getCol(int n) {
    vec res;
    for (int i = 0; i < rowsize; i++) {
      res.emplace_back(this->matrix[i][n]);
    }
    return res;
  }

  void print() {
    for (int i = 0; i < rowsize; i++) {

      std::cout << "\n";
      std::cout << "(";
      for (int j = 0; j < columnsize; j++) {
        std::cout << matrix[i][j];
        j != columnsize - 1 ? std::cout << "\t" : std::cout << "";
      }
      std::cout << ")";
    }
  }
  static Matrix Constmultiplication(const Matrix &TargetedMat, int k) {

    Matrix Result({},
                  std::make_tuple(TargetedMat.rowsize, TargetedMat.columnsize));

    for (int i = 0; i < TargetedMat.rowsize; i++) {

      for (int j = 0; j < TargetedMat.columnsize; j++) {

        Result.matrix[i][j] = TargetedMat.matrix[i][j] * k;
      }
    }

    return Result;
  }

  static Matrix AddMatrix(const Matrix &Mat1, const Matrix &Mat2) {

    Matrix Result({}, std::make_tuple(Mat1.rowsize, Mat1.columnsize));
    if (Mat1.Dimension != Mat2.Dimension) {
      /*throw std::invalid_argument(
          "INVALID OPERATION UNEQUAL DIMENSIONS!");*/           // Dont know why doesn't it work

      std::cout << "INVALID OPERATION UNEQUAL DIMENSIONS!";
    }

    else {

      for (int i = 0; i < Mat1.rowsize; i++) {

        for (int j = 0; j < Mat1.columnsize; j++) {

          Result.matrix[i][j] = Mat1.matrix[i][j] + Mat2.matrix[i][j];
        }
      }

      return Result;
    }

    return Result;
  }

  static Matrix SubtractMatix(const Matrix &Mat1, const Matrix &Mat2) {

    Matrix Result({}, std::make_tuple(Mat1.rowsize, Mat1.columnsize));
    if (Mat1.Dimension != Mat2.Dimension) {

      std::cout << "INVALID OPERATION UNEQUAL DIMENSIONS!";
    }

    else {

      for (int i = 0; i < Mat1.rowsize; i++) {

        for (int j = 0; j < Mat1.columnsize; j++) {

          Result.matrix[i][j] = Mat1.matrix[i][j] - Mat2.matrix[i][j];
        }
      }

      return Result;
    }

    return Result;
  }
  vec addRow(vec r1, vec r2) {
    if (r1.size() != r2.size()) {
      throw std::invalid_argument("NOT EQUAL ROWS");
    }
    vec Result;
    for (unsigned int i = 0; i < r1.size(); i++) {
      Result.emplace_back(r1[i] + r2[i]);
    }

    return Result;
  }

  vec subtRow(const vec& r1, const vec& r2) {
    if (r1.size() != r2.size()) {
      throw std::invalid_argument("NOT EQUAL ROWS");
    }
    vec Result;
    for (unsigned int i = 0; i < r1.size(); i++) {

      Result.emplace_back(r1[i] - r2[i]);
    }
    return Result;
  }

  vec rowConstantMul(const vec& r1, double constant) {
    vec Result{};
    for (unsigned int i = 0; i < r1.size(); i++) {
      Result.emplace_back(r1[i] * constant);
    }

    return Result;
  }

  vec RowByRowMul(const vec& r1, const vec& r2) {
    vec Result{};
    for (unsigned int i = 0; i < r1.size(); i++) {
      Result.emplace_back(r1[i] * r2[i]);
    }

    return Result;
  }
  bool isZeroRow(const vec& row) { // [1 2 3 | 4]
    for (double x : row) {
      if (x != 0)
        return 0;
    }
    return 1;
  }
  static bool isZeroCol(const vec& Col, int start = 0) {

    bool IsZero = true;

    for (unsigned int i = start; i < Col.size(); i++) {
      if (Col[i] != 0) {

        return IsZero = false;
      }
    }
    return IsZero;
  }
};
