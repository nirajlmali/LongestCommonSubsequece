// HW5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <tbb/tbb.h>

using namespace std;
using namespace tbb;

string serialLCS(string A, string B) {
	//Size of each
	int m = A.length();
	int n = B.length();

	//Length of each current subsequence
	int len1 = 0;
	int len2 = 0;

	//L - Data Structure made up of subsequences
	string** L = new string*[m + 1];
	for (int i = 0; i < m + 1; i++)
	{
		L[i] = new string[n + 1];
	}

	/* Careful of i-1, j-1 < 0! */
	for (int i = 0; i < m + 1; i++) {
		for (int j = 0; j < n + 1; j++) {
			if (i <= 0 || j <= 0) {
				L[i][j] = "";
			}
			else if (A[i - 1] == B[j - 1]) {
				/* L[i,j] = L(A_i, B_j) */
				L[i][j] = L[i - 1][j - 1] + "" +  A[i - 1]; // Concatenate A[i] to L[i-1,j-1]
			}
			else {
				len1 = L[i][j - 1].length();
				len2 = L[i - 1][j].length();
				if (len1 > len2)
					L[i][j] = L[i][j - 1];
				else
					L[i][j] = L[i - 1][j];
			}
		}
	}
	return L[m][n];
}

//Parallelized
void parallelLCS(string A, string B) {
	//Size of each
	int rows = A.length();
	int cols = B.length();

	//Length of each current subsequence
	int len1 = 0;
	int len2 = 0;

	//L - Data Structure made up of subsequences
	//Simple parallelization
	string** L = new string * [rows + 1];
	for (int i = 0; i < rows + 1; i++)
	{
		L[i] = new string[cols + 1];
	}

	//int i & j defined
	int i = 0;
	int j = 0;


	//Step 1. Find the amount of hyperplanes/diagonals
	int largerDim = max(rows + 1, cols + 1);
	int smallerDim = min(rows + 1, cols + 1);
	int numDiagonals = largerDim + smallerDim - 1;
	int midDiagonal = numDiagonals + 1;
	cout << numDiagonals << "  diagonals\n";
	cout << numDiagonals / 2 << " diagonals middle\n";

	////Step 2. Loop through each diagonal in serial. This allows no need for locks since it needs to go throught the diagonals in order. Upper Diagonal
	for (int d = 0; d < midDiagonal; d++)
	{
	//	//Step 3. Parallel_for through coordinates on the current diagonal; 3 cases: We are have not reached the last row or column, we've reached that area, we are past that area
		//		i. IF: Not in last row or column, set the curRow = numDiagonals - curCol, curCol iterate OR flip it, need to figure out if it's row or col
		if (d < smallerDim) {
			parallel_for(blocked_range<int>(0, d), [&](const blocked_range<int>& r) {
				for (auto b = r.begin(); b < r.end(); b++)
				{
					i = d - b;
					j = b;
					cout << "i = " << i << ", j = " << j << "\n";
				}
			});
		}
		//		ii. IF: In the last row or column, whichever one we've maxed out at first fix that one. Then the other value should be the iterator
		else if (d < largerDim) {
			parallel_for(blocked_range<int>(0, smallerDim), [&](const blocked_range<int>& r) {
				for (auto b = r.begin(); b < r.end(); b++)
				{
					i = b;
					j = smallerDim + (d - smallerDim);
					cout << "i = " << i << ", j = " << j << "\n";
				}
				});
		}
		//		iii. IF: In last row AND column, then iterate down...
		else{
			parallel_for(blocked_range<int>(0, smallerDim), [&](const blocked_range<int>& r) {
				for (auto b = r.begin(); b < r.end(); b++)
				{
					i = b;
					j = smallerDim + (d - smallerDim);
					cout << "i = " << i << ", j = " << j << "\n";
				}
				});
		}
	}
	//cout << L[m][n];
}


int main(int argc, char* argv[])
{
	char A[] = "ABXTC";
	char B[] = "AGXTC";

	/*cout << "Enter File: ";
	string fileName;
	cin >> fileName;*/

	/*auto start = std::chrono::high_resolution_clock::now();
	string LCSRes1 = serialLCS(A, B);
	auto finish = std::chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = finish - start;
	cout << "Result in " << elapsed.count() << "s\n";
	cout << "LCS: " << LCSRes1;*/

	auto start = std::chrono::high_resolution_clock::now();
	parallelLCS(A, B);
	auto finish = std::chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = finish - start;
	cout << "Result in " << elapsed.count() << "s\n";
	//cout << "LCS: " << LCSRes1;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
