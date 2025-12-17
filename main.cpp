#include "matrix.h"
#include <tuple>

using namespace std;


Matrix zeroing(Matrix M, int pivotRowNumber, int pivotColNumber, int workingrowDistance) {

    if (pivotRowNumber + workingrowDistance >= M.rowsize) {

        return M;
    }
    
    double workingN = M.matrix[pivotRowNumber + workingrowDistance][pivotColNumber];
    double PIVOT = M.matrix[pivotRowNumber][pivotColNumber];

	if(PIVOT == 0){
		// swap rows 
		vec temp = M.matrix[pivotRowNumber+1];
		M.matrix[pivotRowNumber + 1] = M.matrix[pivotRowNumber];
		M.matrix[pivotRowNumber] = temp;
		zeroing(M,pivotRowNumber,pivotColNumber,workingrowDistance);
	}
    if (workingN != 0) {

      vec pivotRow = M.getRow(pivotRowNumber);
      vec workingRow = M.getRow(pivotRowNumber + workingrowDistance);
      vec tempPivot = Matrix::rowConstantMul(pivotRow, ((workingN * -1) / PIVOT));
      vec result = Matrix::addRow(tempPivot, workingRow);
  
      M.matrix[pivotRowNumber + workingrowDistance] = result;
    }

    return zeroing(M, pivotRowNumber, pivotColNumber, workingrowDistance + 1);
}


double gauss(Matrix M) {
  Matrix tempM = Matrix(M.matrix, M.Dimension);
	int pivotRowNumber = 0;
	int pivotColNumber = 0;
	double PIVOT = M.matrix[pivotRowNumber][pivotColNumber];
	if(PIVOT == 0){
		// swap rows 
		vec temp = M.matrix[pivotRowNumber+1];
		M.matrix[pivotRowNumber + 1] = M.matrix[pivotRowNumber];
		M.matrix[pivotRowNumber] = temp;
		return gauss(M);
	}
 
  for (int i = 0; i <= M.rowsize; i++) {
    tempM = zeroing(M, i /*PIVOT ROW NUMBER*/, i,
                    /*PIVOT COLUMN NUMBER*/ 1); // first pivot done
    while (M.matrix != tempM.matrix) { // would only equal each other if we
                                       // finished that specific Pivot
      M = tempM;
      tempM = zeroing(M, i, i, 1); // first pivot done
    }
  }

  M.print();
  std::cout << '\n';
  vec temp = M.getRow(M.rowsize - 1);
  temp.pop_back();

  if (Matrix::isZeroRow(M.getRow(M.rowsize - 1))) {
    std::cout << "THIS SYSTEM HAS INFENITLY MANY SOLUTIONS";
    std::cout << '\n';
  } else if (Matrix::isZeroRow(temp) && (M.getRow(M.rowsize - 1).back() != 0)) {
    std::cout << "THIS SYSTEM HAS NO SOLUTIONS";
    std::cout << '\n';

  } else {
    // this has unique SOLUTIONS
    vec lastRow = M.getRow(M.rowsize - 1);      // last euation
    double resR3 = lastRow[lastRow.size() - 1]; // result is last element;
    double zR3 = lastRow[lastRow.size() - 2];   // Z value in the last equation;
    double Z = resR3 / zR3;
    std::cout << "\nZ:" << Z;
    vec YRow = M.getRow(M.rowsize - 2);
    double ZR2 = YRow[YRow.size() - 2] * Z;

    double resR2 = YRow[YRow.size() - 1];
    double Y;
    double X;
    if (ZR2 > 0) {
      Y = (resR2 - ZR2) / YRow[YRow.size() - 3];
      std::cout << "\nY:" << Y << "\n";
    } else {
      Y = (resR2 + ZR2) / YRow[YRow.size() - 3];
      std::cout << "\nY:" << Y << "\n";
    }

    vec XRow = M.getRow(M.rowsize - 3);
    double ZR1 = XRow[XRow.size() - 2] * Z;
    double YR1 = XRow[XRow.size() - 3] * Y;
    double YZ = ZR1 + YR1;
    double resR1 = XRow[XRow.size() - 1];

    if (YZ > 0) {
      X = (resR1 - YZ) / XRow[XRow.size() - 4];
      std::cout << "X:" << X << "\n";

    } else {
      X = (resR1 + YZ) / XRow[XRow.size() - 4];
      std::cout << "X:" << X << "\n";
    }
  }

  return 0.0;
};

int main() {
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
  Matrix zeroPivotProblem= Matrix({{0,2,1,5},{1,-1,3,4},{2,1,1,6}}, std::make_tuple(3, 4));
  //gauss(InfManyproblem);
  //gauss(NoSolProblem);
  //gauss(UniqueSolProblem);
  gauss(zeroPivotProblem);
}
