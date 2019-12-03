// HW5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

void serialLCS(char A[], char B[]) {
	//Size of each
	int m = sizeof(A) / sizeof(A[0]);
	int n = sizeof(B) / sizeof(B[0]);

	//Length of each current subsequence
	int len1 = 0;
	int len2 = 0;

	//L - Data Structure made up of subsequences
	char *L[2];
	L[0] = A;
	L[1] = B;

	/* Careful of i-1, j-1 < 0! */
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (i <= 0 || j <= 0) {
				L[i, j] = 0;
			}
			else if (A[i] == B[j])
				/* L[i,j] = L(A_i, B_j) */
				L[i, j] = L[i - 1, j - 1] + A[i]; // Concatenate A[i] to L[i-1,j-1]
			else {
				len1 = sizeof(L[i, j - 1]);
				len2 = sizeof(L[i - 1, j]);
				if (len1 > len2)
					L[i, j] = L[i, j - 1];
				else
					L[i, j] = L[i - 1, j];
			}
		}
	}
	//cout << L;
}

int main()
{
    std::cout << "Hello World!\n";
	char A[] = "Hello";
	char B[] = "Hi yo";
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
