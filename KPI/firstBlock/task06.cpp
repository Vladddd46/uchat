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
			*(*(arr + j) + i) = rand() % 20 - 10;
		}
	}
	return arr;
}

int minMultiplyNaturalSum(int** arr, int n) {
	int min = *(*(arr));
	int sum = 0;
	int result = 0;

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(*(*(arr + j) + i) < min) {
				min = *(*(arr + j) + i);
			}
			if(*(*(arr + j) + i) > 0) {
				sum += *(*(arr + j) + i);
			}
		}
	}
    result = sum * min;
    return result;
}

int main() {
    int **arr= creating(10);
    cout << "Min number multiply on sum is - " << minMultiplyNaturalSum(arr, 10) << endl;
    return 0;
}
