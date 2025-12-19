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

  ResType SOL;
  std::vector<double> Solutions = {};
};
static int FirstNonZeroInCol(vec Col, int PivotPos) {
  auto it = std::find_if(Col.begin() + PivotPos, Col.end(),
                         [](int i) { return i != 0; });
  int index = std::distance(Col.begin(), it);

  return index;
}

static Result Gauss(Matrix ArgumentMatrix) {

  int MatrixColumnSize = ArgumentMatrix.columnsize;

  for (int i = 0; i < ArgumentMatrix.columnsize - 1; i++) {

    int PivotRowNum = i;
    int PivotColumnNum = i;
    double Pivot = ArgumentMatrix.matrix[PivotRowNum][PivotColumnNum];
    int MatrixRowSize = ArgumentMatrix.rowsize - 1;

    vec PivotColumn = ArgumentMatrix.getCol(PivotColumnNum);
    auto it = std::find_if(PivotColumn.begin(), PivotColumn.end(),
                           [Pivot](double i) { return i == Pivot; });
    int PivotPos = std::distance(PivotColumn.begin(), it);

    vec PivotRow = ArgumentMatrix.getRow(PivotPos);

    // 2
    for (int j = 0; j < ArgumentMatrix.rowsize - 1 - PivotPos; j++) {

      if (Matrix::isZeroCol(ArgumentMatrix.getCol(i))) {
        // Go RIGHT
        if (PivotColumnNum < MatrixColumnSize - 2) {

          PivotColumnNum += 1;
          PivotPos += 1;

        } else {
          Result result = Result();
          result.SOL = NOSOL;
          return result;
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

        } else {

          if (MatrixRowSize != 0 &&
              PivotRow != ArgumentMatrix.getRow(ArgumentMatrix.rowsize - 1)) {

            vec RowUnderPivot = ArgumentMatrix.getRow(MatrixRowSize);
            double Multipiler = RowUnderPivot[PivotPos] / Pivot;
            vec SubtractorRow = Matrix::rowConstantMul(PivotRow, Multipiler);
            vec FinalRow = Matrix::subtRow(RowUnderPivot, SubtractorRow);
            ArgumentMatrix.matrix[MatrixRowSize] = FinalRow;
            MatrixRowSize--;
          }
        }
      }
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

  Matrix zeroSecondPivot = Matrix(
      {{2, 3, 4, 8, 10}, {0, 0, 1, 1, 20}, {0, 5, 6, 9, 30}, {0, 2, 7, 3, 40}},
      std::make_tuple(4, 5));

  Matrix test = Matrix({{2, 5, 2, -38}, {3, -2, 4, 17}, {-6, 1, -7, -12}},
                       std::make_tuple(3, 4));
	std::cout << Gauss(InfManyproblem).SOL;
}
