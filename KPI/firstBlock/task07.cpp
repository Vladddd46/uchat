#include <iostream>

using namespace std;

int** creating(int N) {
	int i;
	int** arr = new int* [N];

	for (i = 0; i < N; i++) {
		arr[i] = new int[N];
	}
	for (int j = 0; j < N; j++) {
		for (i = 0; i < N; i++) {
			*(*(arr + j) + i) = rand() % 10;
		}
	}
	return arr;
}

int diagonalMultiply(int** arr, int n) {
    int result = 1;

	for(int i = 0; i < n; i++) {
		if(*(*(arr + i) + i) != 0)
            result *= *(*(arr + i) + i);
	}
	return result;
}

int main() {
    int **arr= creating(10);
    cout << "Multiply of non NULL diagonal numbers is - " << diagonalMultiply(arr, 10) << endl;
	return 0;
}