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
	int m = A.length();
	int n = B.length();

	//Length of each current subsequence
	int len1 = 0;
	int len2 = 0;

	//L - Data Structure made up of subsequences
	//Simple parallelization
	string** L = new string * [m + 1];
	for (int i = 0; i < m + 1; i++)
	{
		L[i] = new string[n + 1];
	}

	////Locks? L[0][0], L[1][0], L[0][1] are our initial cases

	////Threadex.
	////TODO launch 3 threads?
	///*std::thread th1(insertintosl, &list, 5000);
	//std::thread th2(insertintosl, &list, 5000);
	//std::thread th3(searchskiplist, &list);*/

	//Step 1. Find the amount of hyperplanes/diagonals
	int largerDim = max(m, n);
	int smallerDim = min(m, n);
	int numDiagonals = largerDim + smallerDim - 1;

	//Step 2. Loop through each diagonal in serial. This allows no need for locks since it needs to go throught the diagonals in order.
	for (int i = 0; i < numDiagonals; i++)
	{
		//Step 3. Parallel_for through coordinates on the current diagonal
		parallel_for(blocked_range2d<int, int>(0, m, 0, n), [=](const blocked_range<int>& r) {
			});

	}

	/////* Careful of i-1, j-1 < 0! */
	////parallel_for(blocked_range2d<int, int>(0, m, 0, n), [=](const blocked_range<int>& r) {
	////	
	////}
	//for (int i = 0; i < m + 1; i++) {
	//	for (int j = 0; j < n + 1; j++) {
	//		if (i <= 0 || j <= 0) {
	//			L[i][j] = "";
	//		}
	//		else if (A[i - 1] == B[j - 1]) {
	//			/* L[i,j] = L(A_i, B_j) */
	//			L[i][j] = L[i - 1][j - 1] + "" + A[i - 1]; // Concatenate A[i] to L[i-1,j-1]
	//		}
	//		else {
	//			len1 = L[i][j - 1].length();
	//			len2 = L[i - 1][j].length();
	//			if (len1 > len2)
	//				L[i][j] = L[i][j - 1];
	//			else
	//				L[i][j] = L[i - 1][j];
	//		}
	//		cout << L[i][j] << "\n";
	//	}
	//}
	//return L[m][n];
}


int main(int argc, char* argv[])
{
	char A[] = "ABXTC";
	char B[] = "AGXT";

	cout << "Enter File: ";
	string fileName;
	cin >> fileName;

	auto start = std::chrono::high_resolution_clock::now();
	string LCSRes1 = serialLCS(A, B);
	auto finish = std::chrono::high_resolution_clock::now();	chrono::duration<double> elapsed = finish - start;
	cout << "Result in " << elapsed.count() << "s\n";
	cout << "LCS: " << LCSRes1;
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
