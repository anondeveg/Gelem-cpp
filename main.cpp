#include "matrix.h"


static int FirstNonZeroInCol(vec Col, int PivotPos) {

	auto it = std::find_if(Col.begin() + PivotPos, Col.end(), [](int i) { return i != 0; });
	int index = std::distance(Col.begin(), it);

	return index;
}

int PivotRowNum = 0;
int PivotColumnNum = 0;

static Matrix Gauss(Matrix ArgumentMatrix) {

	int MatrixColumnSize = ArgumentMatrix.columnsize; // "Not Zero Indexed"
	int MatrixRowSize = ArgumentMatrix.rowsize; // "Not Zero Indexed"


	double Pivot = ArgumentMatrix.matrix[PivotRowNum][PivotColumnNum];


	vec PivotColumn = ArgumentMatrix.getCol(PivotColumnNum);
	auto it = std::find_if(PivotColumn.begin(), PivotColumn.end(), [Pivot](double i) { return i == Pivot; }); // Returns an iterator of the pivot's position
	int PivotPos = std::distance(PivotColumn.begin(), it); // return the pivots postion inside the column "Zero indexed"
	vec PivotRow = ArgumentMatrix.getRow(PivotPos); // returns the row of the pivot


	if (PivotColumnNum != ArgumentMatrix.columnsize - 1) {
		if (Matrix::isZeroCol(ArgumentMatrix.getCol(PivotColumnNum), PivotPos)) {

			if (PivotColumnNum < MatrixColumnSize - 2) {

				PivotColumnNum += 1;

				return Gauss(ArgumentMatrix);
			}

		}


		if (Pivot == 0 && Matrix::isZeroCol(ArgumentMatrix.getCol(PivotColumnNum), PivotPos) == false) {

			int RowUnderPivotIndex = FirstNonZeroInCol(ArgumentMatrix.getCol(PivotColumnNum), PivotPos);
			vec temp = ArgumentMatrix.matrix[RowUnderPivotIndex];
			ArgumentMatrix.matrix[RowUnderPivotIndex] = ArgumentMatrix.matrix[PivotPos];
			ArgumentMatrix.matrix[PivotPos] = temp;
			ArgumentMatrix.print(); std::cout << '\n';
			return Gauss(ArgumentMatrix);



		}
		
		if (abs(Pivot) > 0) {

			for (int i = 0; i < ArgumentMatrix.rowsize - 1 - PivotPos; i++) {

				vec RowUnderPivot = ArgumentMatrix.getRow(MatrixRowSize - 1);
				double Multipiler = RowUnderPivot[PivotColumnNum] / Pivot;
				vec SubtractorRow = Matrix::rowConstantMul(PivotRow, Multipiler);
				vec FinalRow = Matrix::subtRow(RowUnderPivot, SubtractorRow);
				ArgumentMatrix.matrix[MatrixRowSize - 1] = FinalRow;
				MatrixRowSize--;

				ArgumentMatrix.print(); std::cout << '\n';
			}

			if (PivotColumnNum != ArgumentMatrix.columnsize - 2) {

				PivotRowNum++;
				PivotColumnNum++;
				Gauss(ArgumentMatrix);
			}
			else {
				return ArgumentMatrix;
			}

		}
		
		
	}
	else {
		return ArgumentMatrix;
	}
	


	


}

int main() {

	Matrix InfManyproblem = Matrix({ {1, 3, 1, 9},
								  {1, 1, -1, 1},
								  {3, 11, 5, 35},
								  {1, 1, -1, 1} },
		std::make_tuple(4, 4));

	Matrix NoSolProblem = Matrix({ {1, 2, 3}, {2, 4, 7} }, std::make_tuple(2, 3));

	Matrix UniqueSolProblem = Matrix({ {1, 2, 3, 14}, {0, 1, 2, 8}, {0, 0, 1, 3} },
		std::make_tuple(3, 4));

	Matrix zeroPivotProblem = Matrix({ {0, 2, 1, 5}, {1, -1, 3, 4}, {2, 1, 1, 6} },
		std::make_tuple(3, 4));

	Matrix zeroSecondPivot = Matrix(
		{ {2, 3, 4, 8, 10}, {0, 0, 1, 1, 20}, {0, 5, 6, 9, 30}, {0, 2, 7, 3, 40} },
		std::make_tuple(4, 5));

	Matrix test = Matrix({ {2,5,2,-38},{3,-2,4,17},{-6,1,-7,-12} }, std::make_tuple(3, 4));

	Matrix test2 = Matrix({ {1, 2, 3, 4},{2, 4, 5, 10},{3, 6, 7, 14} }, std::make_tuple(3, 4));

	Matrix test3 = Matrix({ {0, 2, 3, 4},{0, 4, 5, 10},{0, 6, 7, 14} }, std::make_tuple(3, 4));
	//Gauss(test3);

	/*std::cout << "\n================================\n";

	std::cout << "Test Case 1: Infinite Solutions\n";
	std::cout << "================================\n";
	InfManyproblem.print();
	std::cout << "\nAfter Gaussian Elimination:\n";
	std::cout << "----------------------------\n";
	Gauss(InfManyproblem).print();*/

	/*std::cout << "\n\n================================\n";
	std::cout << "Test Case 2: No Solution\n";
	std::cout << "================================\n";
	NoSolProblem.print();
	std::cout << "\nAfter Gaussian Elimination:\n";
	std::cout << "----------------------------\n";
	Gauss(NoSolProblem).print();

	std::cout << "\n\n================================\n";
	std::cout << "Test Case 3: Unique Solution\n";
	std::cout << "================================\n";
	UniqueSolProblem.print();
	std::cout << "\nAfter Gaussian Elimination:\n";
	std::cout << "----------------------------\n";
	Gauss(UniqueSolProblem).print();

	std::cout << "\n\n================================\n";
	std::cout << "Test Case 4: Zero Pivot\n";
	std::cout << "================================\n";
	zeroPivotProblem.print();
	std::cout << "\nAfter Gaussian Elimination:\n";
	std::cout << "----------------------------\n";
	Gauss(zeroPivotProblem).print();*/

	std::cout << "\n\n================================\n";
	std::cout << "Test Case 5: Moving Right\n";
	std::cout << "================================\n";
	test2.print();
	std::cout << "\nAfter Gaussian Elimination:\n";
	std::cout << "----------------------------\n";
	Gauss(test2).print();

	std::cout << "\n================================\n";

	
	



	/*auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000000; i++)
		Gauss(zeroPivotProblem);
	auto end = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl*/;
	
}