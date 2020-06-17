#include <iostream>
using namespace std;
int main() {

	int min;
	int sum = 0;
	int user_size;
	int product = 1;
	cout << "Intput array size-";
	cin >> user_size;
	int **arr = new int*[user_size];
	cout << "Input array-";
	for (int i = 0; i < user_size; i++) {
		arr[i] = new int[user_size];
		for (int j = 0; j < user_size; j++) {
			cin >> arr[i][j];
		}
	}
	min = arr[0][0];
	for (int i = 0; i < user_size; i++) {
		for (int j = 0; j < user_size; j++) {
			if (arr[i][j] > 0) {
				sum += arr[i][j];	
			}
			if (min > arr[i][j]) {
				min = arr[i][j];
			}
		}
	}
	product = min * sum;
	cout << "Dob=" << product << endl;
	for (int i = 0; i < user_size; i++) {
		delete[]arr[i];
	}
	system("pause");
}