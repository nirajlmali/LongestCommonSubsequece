// HW5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

void serialLCS(string A, string B) {
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

	//for (int i = 0; i < m; i++) {
	//	for (int j = 0; j < n; j++) {
	//		L[i][j] = 'A';
	//	}
	//}

	//for (int i = 0; i < m; i++) {
	//	for (int j = 0; j < n; j++) {
	//		cout << L[i][j];
	//	}
	//}

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
			cout << L[i][j] << "\n";
		}
	}
	cout << "Final Table";
	for (int i = 0; i < m + 1; i++) {
		for (int j = 0; j < n + 1; j++) {
			cout << L[i][j] << " ";
		}
		cout << "\n";
	}
}

int main()
{
	char A[] = "ABXTC";
	char B[] = "AGXT";
	serialLCS(A, B);
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
