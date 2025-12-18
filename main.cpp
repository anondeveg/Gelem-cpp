#include "matrix.h"


static int FirstNonZeroInCol(vec Col, int PivotPos) {


	auto it = std::find_if(Col.begin() + PivotPos, Col.end(), [](int i) { return i != 0; });
	int index = std::distance(Col.begin(), it);

	return index;
}




static Matrix RowEchlon(Matrix ArgumentMatrix) {

	int MatrixColumnSize = ArgumentMatrix.columnsize;
	static int MatrixRowSize = ArgumentMatrix.rowsize - 1;

	static int PivotRowNum = 0;
	static int PivotColumnNum = 0;
	double Pivot = ArgumentMatrix.matrix[PivotRowNum][PivotColumnNum];



	vec PivotRow = ArgumentMatrix.getRow(PivotRowNum);
	vec PivotColumn = ArgumentMatrix.getCol(PivotColumnNum);

	auto it = std::find_if(PivotColumn.begin(), PivotColumn.end(), [Pivot](double i) { return i == Pivot; });
	static int PivotPos = std::distance(PivotColumn.begin(), it);
	int PivotColEnd = std::distance(it, PivotColumn.end());


	if (Matrix::isZeroCol(PivotColumn)) {
		// Go RIGHT
		if (PivotColumnNum < MatrixColumnSize - 2) {

			PivotColumnNum += 1;
			PivotPos += 1;
			RowEchlon(ArgumentMatrix);
		}
		else {
			std::cout << "This System has no solutions!";
		}

	}
	else {


		if (Pivot == 0) {

			int RowUnderPivotIndex = FirstNonZeroInCol(ArgumentMatrix.getCol(PivotColumnNum), PivotPos);
			vec temp = ArgumentMatrix.matrix[RowUnderPivotIndex];
			ArgumentMatrix.matrix[RowUnderPivotIndex] = ArgumentMatrix.matrix[PivotPos];
			ArgumentMatrix.matrix[PivotPos] = temp;

			ArgumentMatrix.print(); std::cout << '\n';

			RowEchlon(ArgumentMatrix);

		}
		else {

			if (MatrixRowSize != 0) {

				vec RowUnderPivot = ArgumentMatrix.getRow(MatrixRowSize);
				double Multipiler = RowUnderPivot[PivotPos] / Pivot;
				vec SubtractorRow = Matrix::rowConstantMul(PivotRow, Multipiler);
				vec FinalRow = Matrix::subtRow(RowUnderPivot, SubtractorRow);
				ArgumentMatrix.matrix[MatrixRowSize] = FinalRow;
				MatrixRowSize--;

				ArgumentMatrix.print(); std::cout << '\n';

				RowEchlon(ArgumentMatrix);
			}

		}
	}

	return ArgumentMatrix;

}

int main() {

	Matrix zeroPivotProblem = Matrix({ {0,2,1,5  },
									   {0,-1,3,4 },
									   {0,1,1,6  } }, std::make_tuple(3, 4));

	Matrix zeroPivotProblem2 = Matrix({ {0,0,0,5  },
									   {0,0,0,4 },
									   {0,0,0,6  } }, std::make_tuple(3, 4));

	Matrix NoSolProblem = Matrix({ {1, 2, 3},
								   {2, 4, 7} }, std::make_tuple(2, 3));

	Matrix NoSolProblem2 = Matrix({ {2, 5, 2, -38   },
									{3, -2, 4, 17   },
									{-6, 1, -7, -12 } }, std::make_tuple(3, 4));


	Matrix m = RowEchlon(zeroPivotProblem2);
	//Matrix m = RowEchlon(NoSolProblem);


	//std::cout << Matrix::isZeroCol(zeroPivotProblem.getCol(0));


}