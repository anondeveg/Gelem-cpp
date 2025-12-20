#include "matrix.h"
#include <chrono>




static int FirstNonZeroInCol(const vec& Col, int PivotPos)
{
	auto it = std::find_if(Col.begin() + PivotPos, Col.end(), [](double i) { return std::abs(i) > 1e-9; });
	int index = std::distance(Col.begin(), it);

	return index;
}



int PivotRowNum = 0;
int PivotColumnNum = 0;

Matrix RowEchlon(Matrix& ArgumentMatrix, int PivotColumnNum, int PivotRowNum)
{

	double Pivot = ArgumentMatrix.matrix[PivotRowNum][PivotColumnNum];
	vec PivotColumn = ArgumentMatrix.getCol(PivotColumnNum);


	if ((PivotRowNum < ArgumentMatrix.rowsize - 1) && (PivotColumnNum < ArgumentMatrix.columnsize - 1))
	{
		if (Matrix::isZeroCol(PivotColumn, PivotRowNum + 1) && std::abs(Pivot) < 1e-9)
		{
			// Go Right

			PivotColumnNum += 1;
			return RowEchlon(ArgumentMatrix, PivotColumnNum, PivotRowNum);
		}
		else if (std::abs(Pivot) < 1e-9)
		{
			// Swap

			int RowUnderPivotIndex = FirstNonZeroInCol(PivotColumn, PivotRowNum);
			vec temp = ArgumentMatrix.matrix[RowUnderPivotIndex];
			ArgumentMatrix.matrix[RowUnderPivotIndex] = ArgumentMatrix.matrix[PivotRowNum];
			ArgumentMatrix.matrix[PivotRowNum] = temp;
			//ArgumentMatrix.print(); std::cout << '\n';
			return RowEchlon(ArgumentMatrix, PivotColumnNum, PivotRowNum);
		}
		else
		{
			// Eleminate

			vec PivotRow = ArgumentMatrix.getRow(PivotRowNum);

			for (int i = 0; i < ArgumentMatrix.rowsize - 1 - PivotRowNum; i++) {

				vec RowUnderPivot = ArgumentMatrix.getRow(i + 1 + PivotRowNum);
				double Multipiler = RowUnderPivot[PivotColumnNum] / Pivot;
				vec SubtractorRow = Matrix::rowConstantMul(PivotRow, Multipiler);
				vec FinalRow = Matrix::subtRow(RowUnderPivot, SubtractorRow);
				ArgumentMatrix.matrix[i + 1 + PivotRowNum] = FinalRow;

			}
			//ArgumentMatrix.print(); std::cout << '\n';
			PivotRowNum++;
			PivotColumnNum++;
			return RowEchlon(ArgumentMatrix, PivotColumnNum, PivotRowNum);
		}
	}
	else
	{
		return ArgumentMatrix;
	}
}




int main() {

	// -----------------------------------------------------------------TEST MATRICES--------------------------------------------------------------

	Matrix zeroSecondPivot = Matrix({ {2, 3, 4, 8, 10}, {0, 0, 1, 1, 20}, {0, 5, 6, 9, 30}, {0, 2, 7, 3, 40} }, std::make_tuple(4, 5));

	Matrix InfManyproblem = Matrix({ {1, 3, 1, 9}, {1, 1, -1, 1}, {3, 11, 5, 35}, {1, 1, -1, 1} }, std::make_tuple(4, 4));

	Matrix UniqueSolProblem = Matrix({ {1, 2, 3, 14}, {0, 1, 2, 8}, {0, 0, 1, 3} }, std::make_tuple(3, 4));

	Matrix zeroPivotProblem = Matrix({ {0, 2, 1, 5}, {1, -1, 3, 4}, {2, 1, 1, 6} }, std::make_tuple(3, 4));

	Matrix NoSolProblem = Matrix({ {1, 2, 3}, {2, 4, 7} }, std::make_tuple(2, 3));

	Matrix test = Matrix({ {2,5,2,-38},{3,-2,4,17},{-6,1,-7,-12} }, std::make_tuple(3, 4));

	Matrix test2 = Matrix({ {1, 2, 3, 4},{2, 4, 5, 10},{3, 6, 7, 14} }, std::make_tuple(3, 4));

	Matrix test3 = Matrix({ {0, 2, 3, 4},{0, 4, 5, 10},{0, 6, 7, 14} }, std::make_tuple(3, 4));

	// ---------------------------------------------------------------------------------------------------------------------------------------------


	auto start = std::chrono::high_resolution_clock::now();

	// ---------------------------------------------------------PRINTING TEST MATRICES BEFOUR AND AFTER RowEchlon-----------------------------------

	std::cout << "\n================================\n";

	std::cout << "Test Case 1: Infinite Solutions\n";
	std::cout << "================================\n";
	InfManyproblem.print();
	std::cout << "\nAfter Gaussian Elimination:\n";
	std::cout << "----------------------------\n";
	RowEchlon(InfManyproblem, PivotColumnNum, PivotRowNum).print();

	std::cout << "\n\n================================\n";
	std::cout << "Test Case 2: No Solution\n";
	std::cout << "================================\n";
	NoSolProblem.print();
	std::cout << "\nAfter Gaussian Elimination:\n";
	std::cout << "----------------------------\n";
	RowEchlon(NoSolProblem, PivotColumnNum, PivotRowNum).print();

	std::cout << "\n\n================================\n";
	std::cout << "Test Case 3: Unique Solution\n";
	std::cout << "================================\n";
	UniqueSolProblem.print();
	std::cout << "\nAfter Gaussian Elimination:\n";
	std::cout << "----------------------------\n";
	RowEchlon(UniqueSolProblem, PivotColumnNum, PivotRowNum).print();

	std::cout << "\n\n================================\n";
	std::cout << "Test Case 4: Zero Pivot\n";
	std::cout << "================================\n";
	zeroPivotProblem.print();
	std::cout << "\nAfter Gaussian Elimination:\n";
	std::cout << "----------------------------\n";
	RowEchlon(InfManyproblem, PivotColumnNum, PivotRowNum).print();

	std::cout << "\n\n================================\n";
	std::cout << "Test Case 5: Moving Right\n";
	std::cout << "================================\n";
	test2.print();
	std::cout << "\nAfter Gaussian Elimination:\n";
	std::cout << "----------------------------\n";
	RowEchlon(test2, PivotColumnNum, PivotRowNum).print();

	std::cout << "\n================================\n";

	// ---------------------------------------------------------------------------------------------------------------------------------------------



	//--------------------------MEASURING TIME OF EXCUTION----------------------------------

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;
}