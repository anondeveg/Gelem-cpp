#include "matrix.h"
#include <chrono>


// the reverted commit 
using namespace std;

	auto it = std::find_if(Col.begin() + PivotPos, Col.end(), [](int i) { return i != 0; });
	int index = std::distance(Col.begin(), it);

	return index;
}

static Matrix Gauss(Matrix ArgumentMatrix) {

	int MatrixColumnSize = ArgumentMatrix.columnsize;


	for (int i = 0; i < ArgumentMatrix.columnsize - 1; i++) {

		int PivotRowNum = i;
		int PivotColumnNum = i;
		double Pivot = ArgumentMatrix.matrix[PivotRowNum][PivotColumnNum];
		int MatrixRowSize = ArgumentMatrix.rowsize - 1;

		vec PivotColumn = ArgumentMatrix.getCol(PivotColumnNum);
		auto it = std::find_if(PivotColumn.begin(), PivotColumn.end(), [Pivot](double i) { return i == Pivot; });
		int PivotPos = std::distance(PivotColumn.begin(), it);



		vec PivotRow = ArgumentMatrix.getRow(PivotPos);

		// 2
		for (int j = 0; j < ArgumentMatrix.rowsize - 1 - PivotPos; j++) {

			if (Matrix::isZeroCol(ArgumentMatrix.getCol(i))) {
				// Go RIGHT
				if (PivotColumnNum < MatrixColumnSize - 2) {

					PivotColumnNum += 1;
					PivotPos += 1;

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

					return Gauss(ArgumentMatrix);



				}
				else {

					if (MatrixRowSize != 0 && PivotRow != ArgumentMatrix.getRow(ArgumentMatrix.rowsize - 1)) {

						vec RowUnderPivot = ArgumentMatrix.getRow(MatrixRowSize);
						double Multipiler = RowUnderPivot[PivotPos] / Pivot;
						vec SubtractorRow = Matrix::rowConstantMul(PivotRow, Multipiler);
						vec FinalRow = Matrix::subtRow(RowUnderPivot, SubtractorRow);
						ArgumentMatrix.matrix[MatrixRowSize] = FinalRow;
						MatrixRowSize--;

						//ArgumentMatrix.print(); std::cout << '\n';


					}



				}



			}
		}


	}
	return ArgumentMatrix;
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
	std::cout << "\n================================\n";

	std::cout << "Test Case 1: Infinite Solutions\n";
	std::cout << "================================\n";
	InfManyproblem.print();
	std::cout << "\nAfter Gaussian Elimination:\n";
	std::cout << "----------------------------\n";
	Gauss(InfManyproblem).print();

	std::cout << "\n\n================================\n";
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
	Gauss(zeroPivotProblem).print();

	std::cout << "\n================================\n";

	/*auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000000; i++)
		Gauss(zeroPivotProblem);
	auto end = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl*/;
}



