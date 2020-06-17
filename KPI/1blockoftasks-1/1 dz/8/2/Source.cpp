#include <iostream>
using namespace std;
int main() {
	int user_size;
	int product = 1;
	cout << "Input size:";
	do {
		cin >> user_size;//размер больше 0
	} while (user_size <= 0);
	int **arr = new int*[user_size];
	cout << "Input array:" << endl;

	for (int i = 0; i < user_size; i++) {
		arr[i] = new int[user_size];
		for (int j = 0; j < user_size; j++) {
			cin >> arr[i][j];
		}
	}
	for (int i = 0; i < user_size; i++) {

		if (arr[i][i] != 0) {
			product *= arr[i][i];
		}

		if (arr[i][user_size - i - 1] != 0) {
			product *= arr[i][user_size - i - 1];
		}

	}
	if (user_size % 2 == 1) {
		if (arr[user_size / 2][user_size / 2] != 0) {
			product /= arr[user_size / 2][user_size / 2];
		}
	}
	cout << endl << "Product=" << product << endl;
	for (int i = 0; i < user_size; i++) {
		delete[]arr[i];
	}
	system("pause");
}