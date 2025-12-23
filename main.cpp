#include "matrix.h"
#include <chrono>


int PivotCount = 0;

static int FirstNonZeroInCol(const vec& Col, int PivotPos)
{
	auto it = std::find_if(Col.begin() + PivotPos, Col.end(), [](double i) { return std::abs(i) > 1e-9; });
	int index = std::distance(Col.begin(), it);

	return index;
}


Matrix RowEchlon(Matrix& ArgumentMatrix, int PivotColumnNum, int PivotRowNum)
{

	double Pivot = ArgumentMatrix.matrix[PivotRowNum][PivotColumnNum];


	if ((PivotRowNum < ArgumentMatrix.rowsize - 1) && (PivotColumnNum < ArgumentMatrix.columnsize - 1)) // Are we in the allowed boundary ?
	{

		if (std::abs(Pivot) < 1e-9) // Is the pivot 0?
		{

			vec PivotColumn = ArgumentMatrix.getCol(PivotColumnNum);

			if (Matrix::isZeroCol(PivotColumn, PivotRowNum + 1))  // Is the entire row of the pivot zeros?
			{
				// Go Right

				PivotColumnNum += 1;
				return RowEchlon(ArgumentMatrix, PivotColumnNum, PivotRowNum);

			}
			else
			{
				// Swap

				int RowUnderPivotIndex = FirstNonZeroInCol(PivotColumn, PivotRowNum);
				vec temp = ArgumentMatrix.matrix[RowUnderPivotIndex];
				ArgumentMatrix.matrix[RowUnderPivotIndex] = ArgumentMatrix.matrix[PivotRowNum];
				ArgumentMatrix.matrix[PivotRowNum] = temp;

				return RowEchlon(ArgumentMatrix, PivotColumnNum, PivotRowNum);
			}

		}
		else
		{
			// Eleminate

			for (int i = 0; i < ArgumentMatrix.rowsize - 1 - PivotRowNum; i++)
			{
				double Multipiler = ArgumentMatrix.matrix[PivotRowNum + 1 + i][PivotColumnNum] / Pivot;

				for (int j = 0; j < ArgumentMatrix.columnsize; j++)
				{
					ArgumentMatrix.matrix[PivotRowNum + 1 + i][j] -= ArgumentMatrix.matrix[PivotRowNum][j] * Multipiler;
				}

			}
			PivotRowNum++;
			PivotColumnNum++;
			//PivotCount++;
			return RowEchlon(ArgumentMatrix, PivotColumnNum, PivotRowNum);
		}
	}
	else
	{
		return ArgumentMatrix;
	}
}


void Solution(Matrix RowEchlonMat)
{

	//----------------Finding if the matrix has a bad pivot---------------

	bool HasBadPivot = false;

	for (int i = 0; i < RowEchlonMat.rowsize - 1; i++)
	{
		bool IsZero = true;
		for (int j = 0; j < RowEchlonMat.columnsize - 1; j++)
		{
			if (RowEchlonMat.matrix[i][j] > 1e-9)
			{
				IsZero = false;
			}
		}

		if (IsZero == true && std::abs(RowEchlonMat.matrix[i][RowEchlonMat.columnsize - 1]) > 1e-9)
		{
			HasBadPivot = true;
			break;
		}
	}


	if (HasBadPivot == true)
	{

		std::cout << "THIS SYSTEM HAS NO SOLUTIONS!";

	}
	else
	{
		int VariableCount = RowEchlonMat.columnsize - 1;
		int PivotCount = 0;
		vec Pivots(RowEchlonMat.columnsize - 1);


		//-----------------------Finding and Counting Pivots------------------------------

		for (int i = 0; i < RowEchlonMat.rowsize; i++)
		{
			for (int j = 0; j < RowEchlonMat.columnsize - 1; j++)
			{
				if (std::abs(RowEchlonMat.matrix[i][j]) > 1e-9)
				{
					if (j == RowEchlonMat.columnsize - 1)
					{
						PivotCount++;
						break;
					}
					else
					{
						PivotCount++;
						Pivots[i] = RowEchlonMat.matrix[i][j];
						break;
					}

				}
			}
		}



		if (PivotCount == VariableCount)
		{


			vec VariableValues(RowEchlonMat.columnsize - 1);


			for (int i = RowEchlonMat.rowsize - 1; i >= 0; i--)
			{
				int RowSum = RowEchlonMat.matrix[i][RowEchlonMat.columnsize - 1];

				for (int j = i + 1; j < RowEchlonMat.columnsize - 1; j++)
				{

					RowSum -= RowEchlonMat.matrix[i][j] * VariableValues[j];
				}

				if (Pivots[RowEchlonMat.columnsize - 1 - i] > 1e-9)
				{

				}

				VariableValues[i] = RowSum / Pivots[i];


			}

			std::cout << "THIS SYSTEM HAS UNIQUE SOLUTIONS!";

		}
		else if (PivotCount < VariableCount)
		{
			std::cout << "THIS SYSTEM HAS INFINITE SOLUTIONS!";

		}
	}
}



int main()
{

	// -----------------------------------------------------------------TEST MATRICES--------------------------------------------------------------

	Matrix zeroSecondPivot = Matrix({ {2, 3, 4, 8, 10}, {0, 0, 1, 1, 20}, {0, 5, 6, 9, 30}, {0, 2, 7, 3, 40} }, std::make_tuple(4, 5));

	Matrix InfManyproblem = Matrix({ {1, 3, 1, 9}, {1, 1, -1, 1}, {3, 11, 5, 35}, {1, 1, -1, 1} }, std::make_tuple(4, 4));

	Matrix UniqueSolProblem = Matrix({ {1, 2, 3, 14}, {0, 1, 2, 8}, {0, 0, 1, 3} }, std::make_tuple(3, 4));

	Matrix zeroPivotProblem = Matrix({ {0, 2, 1, 5}, {1, -1, 3, 4}, {2, 1, 1, 6} }, std::make_tuple(3, 4));

	Matrix NoSolProblem = Matrix({ {1, 2, 3}, {2, 4, 7} }, std::make_tuple(2, 3));

	Matrix test = Matrix({ {2,5,2,-38},{3,-2,4,17},{-6,1,-7,-12} }, std::make_tuple(3, 4));

	Matrix test2 = Matrix({ {1, 2, 3, 4},{2, 4, 5, 10},{3, 6, 7, 14} }, std::make_tuple(3, 4));

	Matrix test3 = Matrix({ {0, 2, 3, 4},{0, 4, 5, 10},{0, 6, 7, 14} }, std::make_tuple(3, 4));

	Matrix test4 = Matrix({
		{45, 78, 23, 91, 12, 67, 34, 89, 56, 21, 43, },
		{23, 56, 89, 12, 45, 78, 34, 67, 90, 21, 54, },
		{67, 34, 92, 15, 58, 81, 29, 72, 45, 98, 26, },
		{89, 42, 15, 68, 31, 94, 47, 20, 73, 36, 99, },
		{12, 75, 48, 91, 34, 77, 50, 93, 36, 79, 52, },
		{34, 87, 50, 13, 66, 29, 82, 45, 98, 61, 24, },
		{56, 19, 72, 35, 88, 51, 14, 67, 30, 83, 46, },
		{78, 41, 94, 57, 20, 73, 46, 99, 62, 25, 88, },
		{90, 63, 36, 99, 72, 45, 18, 81, 54, 27, 90, },
		{22, 85, 58, 31, 94, 67, 40, 13, 86, 59, 32, },
		},
		std::make_tuple(10, 11));


	auto start = std::chrono::high_resolution_clock::now();

	// ----------------------------------------------PRINTING TEST MATRICES BEFOUR AND AFTER RowEchlon Function--------------------------------------

		/*std::cout << "\n================================\n";

		std::cout << "Test Case 1: Infinite Solutions\n";
		std::cout << "================================\n";
		InfManyproblem.print();
		std::cout << "\nAfter Gaussian Elimination:\n";
		std::cout << "----------------------------\n";
		RowEchlon(InfManyproblem, 0, 0).print();

		std::cout << "\n\n================================\n";
		std::cout << "Test Case 2: No Solution\n";
		std::cout << "================================\n";
		NoSolProblem.print();
		std::cout << "\nAfter Gaussian Elimination:\n";
		std::cout << "----------------------------\n";
		RowEchlon(NoSolProblem, 0, 0).print();*/

	std::cout << "\n\n================================\n";
	std::cout << "Test Case 3: Unique Solution\n";
	std::cout << "================================\n";
	test3.print();
	std::cout << "\nAfter Gaussian Elimination:\n";
	std::cout << "----------------------------\n";
	RowEchlon(test3, 0, 0).print();
	//Solution(RowEchlon(test4, 0, 0));

	std::cout << "\n\n================================\n";
	/*std::cout << "Test Case 4: Zero Pivot\n";
	std::cout << "================================\n";
	zeroPivotProblem.print();
	std::cout << "\nAfter Gaussian Elimination:\n";
	std::cout << "----------------------------\n";
	RowEchlon(InfManyproblem, 0, 0).print();

	std::cout << "\n\n================================\n";
	std::cout << "Test Case 5: Moving Right\n";
	std::cout << "================================\n";
	test2.print();
	std::cout << "\nAfter Gaussian Elimination:\n";
	std::cout << "----------------------------\n";
	RowEchlon(test2, 0, 0).print();

	std::cout << "\n================================\n";*/
	//std::cout << PivotCount << '\n';




//--------------------------MEASURING TIME OF EXCUTION----------------------------------

	/*auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 1000000; i++)
			RowEchlon(test2, 0, 0);
	auto end = std::chrono::high_resolution_clock::now();*/


	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;
}