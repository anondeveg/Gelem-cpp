#include "matrix.h"
#include <ratio>
#include <stdexcept>
#include <tuple>
#include <type_traits>

using namespace std;

vec addRow(vec r1, vec r2) {
  if (r1.size() != r2.size()) {
    throw invalid_argument("NOT EQUAL ROWS");
  }
  vec Result;
  for (int i = 0; i < r1.size(); i++) {
    Result.push_back(r1[i] + r2[i]);
  }

  return Result;
}

vec subtRow(vec r1, vec r2) {
  if (r1.size() != r2.size()) {
    throw invalid_argument("NOT EQUAL ROWS");
  }
  vec Result;
  for (int i = 0; i < r1.size(); i++) {

    Result.push_back(r1[i] - r2[i]);
  }
  return Result;
}

vec rowConstantMul(vec r1, double constant) {
  vec Result{};
  for (int i = 0; i < r1.size(); i++) {
    Result.push_back(r1[i] * constant);
  }

  return Result;
}

vec RowByRowMul(vec r1, vec r2) {
  vec Result{};
  for (int i = 0; i < r1.size(); i++) {
    Result.push_back(r1[i] * r2[i]);
  }

  return Result;
}

Matrix zeoring(Matrix M,int pivotRowNumber, int pivotColNumber, int workingrowDistance) {

	if (pivotRowNumber + workingrowDistance >= M.rowsize) return M;
  double workingN = M.matrix[pivotRowNumber + workingrowDistance][pivotColNumber];
  double PIVOT = M.matrix[pivotRowNumber][pivotColNumber];
  if (workingN != 0) {
    vec pivotRow = M.getRow(pivotRowNumber);
    vec workingRow = M.getRow(pivotRowNumber + workingrowDistance);
    vec tempPivot = rowConstantMul(pivotRow, workingN);
    vec tempWorkingRow = rowConstantMul(workingRow, (PIVOT * -1));
    vec result = addRow(tempPivot, tempWorkingRow);

    M.matrix[pivotRowNumber + workingrowDistance] = result;
    M.print();
		std::cout << '\n';
  }

	return zeoring(M,pivotRowNumber,pivotColNumber,workingrowDistance+1);
}


double gauss(Matrix M) {
  int pivotRowNumber = 0;
  int pivotColNumber = 0;
	zeoring(M,pivotRowNumber,pivotColNumber,1);
  return 0.0;
};

int main() {
  Matrix problem = Matrix({{2, 5, 2, -38}, {3, -2, 4, 17}, {-6, 1, -7, -12}},
                          std::make_tuple(3, 4));
  gauss(problem);
}

// n pivot / underpivot
// n * -1
