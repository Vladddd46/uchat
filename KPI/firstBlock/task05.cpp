#include <iostream>

using namespace std;

int** creating(int N) {
	int i;
	int** arr = new int* [N];

	for (i = 0; i < N; i++) {
		*(arr + i) = new int[N];
	}
	for (int j = 0; j < N; j++) {
		for (i = 0; i < N; i++) {
			*(*(arr + j) + i) = rand() % 10;
		}
	}
	return arr;
}

void getEachLineAvrg(int** arr, int n, int m) {
    int sum = 0;
    int divider = 10;

    for(int i = 0; i < n; i++) {
    	divider = 10;
    	for(int j = 0; j < m; j++) {
    		if(*(*(arr + j) + i) >= 0)
                sum += *(*(arr + j) + i);
            else
            	divider--;
    	}
    	cout << "Line " << i + 1 << " Avrg is - "<< sum / divider << endl;
        sum = 0;
    }
}

int main() {
    int **arr= creating(10);
    getEachLineAvrg(arr, 10, 10);
}