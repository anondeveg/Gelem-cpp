#include "matrix.h"
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <vector>

enum ResType {
  NOSOL,
  INFSOL,
  UNIQUESOL,
};

struct Result {

Matrix rowEchlonForm(Matrix M, int pivotRowNumber, int pivotColNumber,
                     int workingrowDistance) {

  if (pivotRowNumber + workingrowDistance >= M.rowsize)
    return M;
  double workingN =
      M.matrix[pivotRowNumber + workingrowDistance][pivotColNumber];
  double PIVOT = M.matrix[pivotRowNumber][pivotColNumber];
  if (PIVOT == 0) {
    // swap rows
    vec temp = M.matrix[pivotRowNumber + 1];
    M.matrix[pivotRowNumber + 1] = M.matrix[pivotRowNumber];
    M.matrix[pivotRowNumber] = temp;
    rowEchlonForm(M, pivotRowNumber, pivotColNumber, workingrowDistance);
  }
  if (workingN != 0) {
    vec pivotRow = M.getRow(pivotRowNumber);
    vec workingRow = M.getRow(pivotRowNumber + workingrowDistance);
    vec tempPivot = M.rowConstantMul(pivotRow, ((workingN * -1) / PIVOT));
    vec result = M.addRow(tempPivot, workingRow);

    M.matrix[pivotRowNumber + workingrowDistance] = result;
  }

  return rowEchlonForm(M, pivotRowNumber, pivotColNumber,
                       workingrowDistance + 1);
}

      } else {

        if (Pivot == 0) {

          int RowUnderPivotIndex = FirstNonZeroInCol(
              ArgumentMatrix.getCol(PivotColumnNum), PivotPos);
          vec temp = ArgumentMatrix.matrix[RowUnderPivotIndex];
          ArgumentMatrix.matrix[RowUnderPivotIndex] =
              ArgumentMatrix.matrix[PivotPos];
          ArgumentMatrix.matrix[PivotPos] = temp;

          return Gauss(ArgumentMatrix);

double gauss(Matrix M) {
  Matrix tempM = Matrix(M.matrix, M.Dimension);
  int pivotRowNumber = 0;
  int pivotColNumber = 0;
  double PIVOT = M.matrix[pivotRowNumber][pivotColNumber];
  if (PIVOT == 0) {
    // swap rows
    vec temp = M.matrix[pivotRowNumber + 1];
    M.matrix[pivotRowNumber + 1] = M.matrix[pivotRowNumber];
    M.matrix[pivotRowNumber] = temp;
    return gauss(M);
  }

  for (int i = 0; i <= M.rowsize; i++) {
    tempM = rowEchlonForm(M, i /*PIVOT ROW NUMBER*/, i,
                          /*PIVOT COLUMN NUMBER*/ 1); // first pivot done
    while (M.matrix != tempM.matrix) { // would only equal each other if we
                                       // finished that specific Pivot
      M = tempM;
      tempM = rowEchlonForm(M, i, i, 1); // first pivot done
    }
  }

  if (ArgumentMatrix.isZeroRow(
          ArgumentMatrix.getRow(ArgumentMatrix.rowsize - 1))) {
    Result result;
    result.SOL = INFSOL;
    return result;
  }
  vec temp = ArgumentMatrix.getRow(ArgumentMatrix.rowsize - 1);
  temp.pop_back();
  if (ArgumentMatrix.isZeroRow(temp) &&
      ArgumentMatrix.getRow(ArgumentMatrix.rowsize - 1).back() != 0) {
    Result result;
    result.SOL = NOSOL;
    return result;
  } else {

    Result result;
    result.SOL = UNIQUESOL;
    int push = 2;
    for (int i = ArgumentMatrix.rowsize - 1; i >= 0; i--) { // loop from down up
      double var;
      vec Row = ArgumentMatrix.getRow(i); // equation

      double res = Row[Row.size() - 1]; // result is last element;
      int index = Row.size() - push;
      double sol = Row[index];

      if (result.Solutions.size() > 0) {
        std::vector<double> rowofsols; // for example Z value in X's row
        for (int j = 0; j < result.Solutions.size(); j++) {

        }

      } else {

        var = res / sol;
      }

      result.Solutions.push_back(var);
      push++;
      std::cout << var;
    }
  }
  return Result();
}

int main() {

  Matrix InfManyproblem =
      Matrix({{1, 3, 1, 9}, {1, 1, -1, 1}, {3, 11, 5, 35}, {1, 1, -1, 1}},
             std::make_tuple(4, 4));

  Matrix NoSolProblem = Matrix({{1, 2, 3}, {2, 4, 7}}, std::make_tuple(2, 3));

  Matrix UniqueSolProblem = Matrix({{1, 2, 3, 14}, {0, 1, 2, 8}, {0, 0, 1, 3}},
                                   std::make_tuple(3, 4));
  Matrix zeroPivotProblem = Matrix({{0, 2, 1, 5}, {1, -1, 3, 4}, {2, 1, 1, 6}},
                                   std::make_tuple(3, 4));
  // gauss(InfManyproblem);
  // gauss(NoSolProblem);
  // gauss(UniqueSolProblem);
  gauss(zeroPivotProblem);
}
