#include "chapter_1.h"
#include <iostream>

using namespace std;

int main() {
	int A[7] = { 5,2,7,4,6,3,1 };
	int length = sizeof(A) / sizeof(A[0]);
	bubbleSort(A, length);
	for (int i = 0; i < length; i++) {
		cout << A[i] << " ";
	}
	cout << endl;
}
