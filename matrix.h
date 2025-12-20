#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>


using Dim = std::tuple<int, int>;
using Mat = std::vector<std::vector<double>>;
using vec = std::vector<double>;


// Prints Vectors and other containers.
template <typename T> void printContainer(const std::vector<T>& vec) {
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
    int rowsize = 0;
    int columnsize = 0;


    //Constructor
    Matrix(Mat mat, Dim Dimension) {
        this->matrix = mat;
        this->Dimension = Dimension;
        this->rowsize = std::get<0>(Dimension);
        this->columnsize = std::get<1>(Dimension);
        if (mat.size() == 0) {
            for (int i = 0; i < rowsize; i++) {
                matrix.push_back({});

                for (int j = 0; j < columnsize; j++) {
                    matrix[i].push_back(0);
                }
            }
        }
    }


    // A Function that multiplies to matrices by each other.
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


    // Returns the row of a matrix
    vec getRow(int n) { return this->matrix[n]; }

    //Returns the column of a matrix
    vec getCol(int n) {
        vec res;
        for (int i = 0; i < rowsize; i++) {
            res.push_back(this->matrix[i][n]);
        }
        return res;
    }


    // Function that prints a matrix
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


    // A Function that multiplies a matrix by a constant
    static Matrix Constmultiplication(Matrix TargetedMat, double k) {

        Matrix Result({}, std::make_tuple(TargetedMat.rowsize, TargetedMat.columnsize));


        for (int i = 0; i < TargetedMat.rowsize; i++) {

            for (int j = 0; j < TargetedMat.columnsize; j++) {

                Result.matrix[i][j] = TargetedMat.matrix[i][j] * k;
            }
        }

        return Result;

    }


    // A Function that Adds 2 matrices together
    static Matrix AddMatrix(Matrix Mat1, Matrix Mat2) {

        if (Mat1.Dimension != Mat2.Dimension) {
            throw std::invalid_argument(
                "INVALID OPERATION UNEQUAL DIMENSIONS! Matrix addition operation "
                "should have = dimensions");
        }

        else {
            Matrix Result({}, std::make_tuple(Mat1.rowsize, Mat1.columnsize));

            for (int i = 0; i < Mat1.rowsize; i++) {

                for (int j = 0; j < Mat1.columnsize; j++) {

                    Result.matrix[i][j] = Mat1.matrix[i][j] + Mat2.matrix[i][j];
                }
            }

            return Result;
        }
    }



    // A Function that subtracts 2 matrices
    static Matrix SubtractMatix(Matrix Mat1, Matrix Mat2) {

        if (Mat1.Dimension != Mat2.Dimension) {
            throw std::invalid_argument(
                "INVALID OPERATION UNEQUAL DIMENSIONS! Matrix addition operation "
                "should have = dimensions");

        }

        else {
            Matrix Result({}, std::make_tuple(Mat1.rowsize, Mat1.columnsize));

            for (int i = 0; i < Mat1.rowsize; i++) {

                for (int j = 0; j < Mat1.columnsize; j++) {

                    Result.matrix[i][j] = Mat1.matrix[i][j] - Mat2.matrix[i][j];
                }
            }

            return Result;
        }
    }


    // A Function that adds 2 rows in a matrix
    static vec addRow(vec r1, vec r2) {
        if (r1.size() != r2.size()) {
            throw std::invalid_argument("NOT EQUAL ROWS");
        }
        vec Result;
        for (unsigned int i = 0; i < r1.size(); i++) {
            Result.push_back(r1[i] + r2[i]);
        }

        return Result;
    }


    // A Function that subtracts 2 rows in a matrix
    static vec subtRow(vec r1, vec r2) {
        if (r1.size() != r2.size()) {
            throw std::invalid_argument("NOT EQUAL ROWS");
        }
        vec Result;
        for (unsigned int i = 0; i < r1.size(); i++) {

            Result.push_back(r1[i] - r2[i]);
        }
        return Result;
    }


    // A Function that multiplies a row by a constant in a matrix
    static vec rowConstantMul(vec r1, double constant) {
        vec Result{};
        for (unsigned int i = 0; i < r1.size(); i++) {
            Result.push_back(r1[i] * constant);
        }

        return Result;
    }


    // A Function that multiplies 2 rows by each other in a matrix
    static vec RowByRowMul(vec r1, vec r2) {
        vec Result{};
        for (unsigned int i = 0; i < r1.size(); i++) {
            Result.push_back(r1[i] * r2[i]);
        }

        return Result;
    }


    // A Function to check if an entire row in a matrix is zeros
    static bool isZeroRow(vec row) { // [1 2 3 | 4]
        for (double x : row) {
            if (x != 0)
                return 0;
        }
        return 1;
    }

    // A Function to check is an entire column is zeros 
    static bool isZeroCol(const vec& Col, int start) {

        bool IsZero = true;

        for (int i = start; i < Col.size(); i++) {
            if (Col[i] != 0) {

                return IsZero = false;
            }

        }
        return IsZero;
    }

    // A Function that checkes if an entire matrix is made of zeros
    static bool isZeroMatrix(Matrix M) {

        bool IsZero = false;

        for (int i = 0; i < M.rowsize; i++) {

            vec MatrixCol = M.getCol(i);

            if (isZeroCol(MatrixCol, 0) == true) {
                IsZero = true;

            }
        }
        return IsZero;
    }
};
