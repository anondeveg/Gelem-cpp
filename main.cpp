#include "matrix.h"
#include <chrono>




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

	//---------------- Cleaning really small numbers -------------------

	for (int i = 0; i < RowEchlonMat.rowsize; i++) {

		for (int j = 0; j < RowEchlonMat.columnsize; j++) {

			if (std::abs(RowEchlonMat.matrix[i][j]) < 1e-9) {

				RowEchlonMat.matrix[i][j] = 0.0;
			}
		}
	}


	//--------------- Finding if the matrix has a bad pivot --------------

	bool HasBadPivot = false;

	for (int i = 0; i < RowEchlonMat.rowsize; i++)
	{
		bool IsZero = true;
		for (int j = 0; j < RowEchlonMat.columnsize - 1; j++)
		{
			if (std::abs(RowEchlonMat.matrix[i][j]) > 1e-9)
			{
				IsZero = false;
				break;
			}
		}

		if (IsZero == true && std::abs(RowEchlonMat.matrix[i][RowEchlonMat.columnsize - 1]) > 1e-9)
		{
			HasBadPivot = true;
			break;
		}
	}



	// ------------------------------------------ Finding the Solution ---------------------------------------------

	if (HasBadPivot == true)
	{

		std::cout << '\n' << '\n' << "THIS SYSTEM HAS NO SOLUTIONS!";

	}
	else
	{
		int VariableCount = RowEchlonMat.columnsize - 1;
		int PivotCount = 0;
		vec Pivots(RowEchlonMat.rowsize);


		//----------------------- Finding and Counting Pivots ------------------------------

		for (int i = 0; i < RowEchlonMat.rowsize; i++)
		{
			for (int j = 0; j < RowEchlonMat.columnsize - 1; j++)
			{
				if (std::abs(RowEchlonMat.matrix[i][j]) > 1e-9)
				{
					PivotCount++;
					Pivots[i] = RowEchlonMat.matrix[i][j];
					break;
				}

			}
		}




		if (PivotCount == VariableCount)
		{

			//--------------------- Back Substitution ------------------------

			vec VariableValues(RowEchlonMat.columnsize - 1);


			for (int i = VariableCount - 1; i >= 0; i--)
			{
				double RowSum = RowEchlonMat.matrix[i][RowEchlonMat.columnsize - 1];

				for (int j = i + 1; j < RowEchlonMat.columnsize - 1; j++)
				{

					RowSum -= RowEchlonMat.matrix[i][j] * VariableValues[j];
				}

				VariableValues[i] = RowSum / Pivots[i];


			}


			//-------------------- Printing the Solution -------------------------

			std::cout << '\n' << "THIS SYSTEM HAS UNIQUE SOLUTIONS!" << '\n';

			for (int i = 0; i < VariableValues.size(); i++)
			{
				std::cout << "X" << i + 1 << ": " << VariableValues[i] << "|" << '\t';

			}


		}
		else if (PivotCount < VariableCount)
		{
			std::cout << '\n' << '\n' << "THIS SYSTEM HAS INFINITE SOLUTIONS!";

		}
	}
}



int main()
{

	// ----------------------------------------------------------------- TEST MATRICES --------------------------------------------------------------

	Matrix zeroSecondPivot = Matrix({ {2, 3, 4, 8, 10}, {0, 0, 1, 1, 20}, {0, 5, 6, 9, 30}, {0, 2, 7, 3, 40} }, std::make_tuple(4, 5));

	Matrix InfManyproblem = Matrix({ {1, 3, 1, 9}, {1, 1, -1, 1}, {3, 11, 5, 35}, {1, 1, -1, 1} }, std::make_tuple(4, 4));

	Matrix UniqueSolProblem = Matrix({ {1, 2, 3, 14}, {0, 1, 2, 8}, {0, 0, 1, 3} }, std::make_tuple(3, 4));

	Matrix zeroPivotProblem = Matrix({ {0, 2, 1, 5}, {1, -1, 3, 4}, {2, 1, 1, 6} }, std::make_tuple(3, 4));

	Matrix NoSolProblem = Matrix({ {1, 2, 3}, {2, 4, 7} }, std::make_tuple(2, 3));

	Matrix test = Matrix({ {2,5,2,-38},{3,-2,4,17},{-6,1,-7,-12} }, std::make_tuple(3, 4));

	Matrix test2 = Matrix({ {1, 2, 3, 4},{2, 4, 5, 10},{3, 6, 7, 14} }, std::make_tuple(3, 4));

	Matrix test3 = Matrix({ {0, 2, 3, 4},{0, 4, 5, 10},{0, 6, 7, 14} }, std::make_tuple(3, 4));

	Matrix test4 = Matrix({
	{3, 5, 2, 1, 4, 6, 2, 8, 1, 9, 45},
	{2, 3, 1, 7, 5, 2, 8, 3, 1, 4, 30},
	{1, 9, 4, 2, 3, 5, 7, 6, 2, 1, 25},
	{5, 2, 6, 3, 1, 4, 2, 9, 5, 7, 40},
	{4, 1, 7, 5, 2, 8, 3, 6, 9, 2, 50},
	{6, 8, 3, 1, 9, 2, 5, 4, 7, 3, 35},
	{2, 5, 1, 8, 6, 3, 4, 9, 2, 1, 20},
	{9, 4, 2, 6, 3, 1, 8, 5, 7, 2, 55},
	{3, 7, 5, 2, 1, 9, 6, 4, 8, 3, 42},
	{8, 2, 9, 4, 5, 3, 1, 7, 6, 2, 48}
		}, std::make_tuple(10, 11));


	auto start = std::chrono::high_resolution_clock::now();


	// ---------------------------------------------- PRINTING TEST MATRICES BEFOUR AND AFTER RowEchlon Function --------------------------------------

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
	UniqueSolProblem.print();
	std::cout << "\n" << "\n" << "After Gaussian Elimination :" << " \n";
	std::cout << "----------------------------\n";
	RowEchlon(UniqueSolProblem, 0, 0).print();
	std::cout << "\n" << "\n" << "After Solving :" << " \n";
	std::cout << "----------------------------\n";

	Solution(RowEchlon(UniqueSolProblem, 0, 0));

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




//-------------------------- MEASURING TIME OF EXCUTION ----------------------------------

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;
}