#include "matrix.h"
#include <tuple>

bool ISVERBOSE = false;
using namespace std;
enum ResType {
  NOSOL,
  INFSOL,
  UNIQUESOL,
};

struct Result {
  ResType SOL;
  std::vector<double> Solutions = {};
};
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

bool isZeroRow(vec row) { // [1 2 3 | 4]
  for (double x : row) {
    if (x != 0)
      return 0;
  }
  return 1;
}

Result gauss(Matrix M) {
  Matrix tempM = Matrix(M.matrix, M.Dimension);
  int pivotRowNumber = 0;
  int pivotColNumber = 0;
  double PIVOT = M.matrix[pivotRowNumber][pivotColNumber];
  if (PIVOT == 0 &&
      !(Matrix::isZeroCol(M.getCol(pivotColNumber)))) { // swapable zero pivot
    // swap rows
    vec temp = M.matrix[pivotRowNumber + 1];
    M.matrix[pivotRowNumber + 1] = M.matrix[pivotRowNumber];
    M.matrix[pivotRowNumber] = temp;
    return gauss(M);
  } else if (PIVOT == 0 && (Matrix::isZeroCol(M.getCol(pivotColNumber)))) {
    pivotColNumber++; // move right
  }

  for (pivotRowNumber = pivotRowNumber; pivotRowNumber <= M.rowsize;
       pivotRowNumber++) {

    tempM = rowEchlonForm(M, pivotRowNumber, pivotColNumber,
                          1);          // first pivot done
    while (M.matrix != tempM.matrix) { // would only equal each other if we
                                       // finished that specific Pivot
      M = tempM;
      tempM = rowEchlonForm(M, pivotRowNumber, pivotColNumber,
                            1); // first pivot done
      if (ISVERBOSE) {
        tempM.print();
        std::cout << "\n";
      }
    }
    pivotColNumber++;
  }

  vec temp = M.getRow(M.rowsize - 1);
  temp.pop_back();

  if (isZeroRow(M.getRow(M.rowsize - 1))) {
    Result res;
    res.SOL = INFSOL;
    return res;

  } else if (isZeroRow(temp) && (M.getRow(M.rowsize - 1).back() != 0)) {
    Result res;
    res.SOL = NOSOL;
    return res;

  } else {
    // this has unique SOLUTIONS
		// temporary handeling
		Result res;
		res.SOL = UNIQUESOL;
		return res;
 }

  return Result();
}

int main(int argc, char *argv[]) {
  Matrix InfManyproblem = Matrix({{1, 3, 1, 9},
                                  {1, 1, -1, 1},
                                  {3, 11, 5, 35},
                                  {
                                      1,
                                      1,
                                      -1,
                                      1,
                                  }},
                                 std::make_tuple(3, 4));
  Matrix NoSolProblem = Matrix({{1, 2, 3}, {2, 4, 7}}, std::make_tuple(2, 3));
  Matrix UniqueSolProblem = Matrix({{1, 2, 3, 14}, {0, 1, 2, 8}, {0, 0, 1, 3}},
                                   std::make_tuple(3, 4));
  Matrix zeroPivotProblem = Matrix({{0, 2, 1, 5}, {1, -1, 3, 4}, {2, 1, 1, 6}},
                                   std::make_tuple(3, 4));
  Matrix movingRightProblem = Matrix(
      {{0, 2, 3, 4}, {0, 4, 5, 10}, {0, 6, 7, 14}}, std::make_tuple(3, 4));

  if (argc > 1) {
    std::string cmd = argv[1];
    if (cmd == "-v")
      ISVERBOSE = true;
  }
  std::cout << gauss(movingRightProblem).SOL;
  // std::cout << gauss(InfManyproblem).SOL;
  // std::cout << gauss(NoSolProblem).SOL;

  // gauss(zeroPivotProblem);
	return 0;
}
