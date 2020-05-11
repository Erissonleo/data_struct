#include "chapter2_vector.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
	MyVector<int> ivec({ 1,2,3,4,5,6 });
	MyVector<int> iv = { 1,2,3,4,5,6,7,8 };
	cout << ivec.size() << endl;
	cout << iv.size() << endl;
}