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

void transformMatrix(int** arr) {
	int sum = 0;

    for(int i = 0; i < 10; i++) {
    	sum = 0;
    	for(int j = 0; j < 10; j++) {
            if(j != 9) {
            	sum += *(*(arr + j) + i);
            }
            else {
            	*(*(arr + j) + i) = sum;
            }
    	}
    }
}

void printMatrix(int** arr) {
    for(int i = 0; i < 10; i++) {
    	for(int j = 0; j < 10; j++) {
    		cout << *(*(arr + j) + i) << "  ";
    	}
    	cout << endl;
    }
}

int main() {
    int **arr= creating(10);

    transformMatrix(arr);
    printMatrix(arr);
	return 0;
}