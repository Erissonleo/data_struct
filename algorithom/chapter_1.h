#ifndef __CHAPTER_1__
#define __CHAPTER_1__

template<typename T>
void mySwap(T& num1, T& num2) {
	T tmp = num2;
	num2 = num1;
	num1 = tmp;
}


void bubbleSort(int A[], int n) {
	bool sorted = false;
	while (!sorted) {
		sorted = true;
		for (int i = 1; i < n; i++) {
			if (A[i - 1] > A[i]) {
				mySwap(A[i - 1], A[i]);
				sorted = false;
			}
		}
	}
	n--;
}




#endif
