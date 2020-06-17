#include <iostream>
using namespace std;
int main() {
	int user_size1;
	int user_size2;
	cout << "Intput array lines-";
	cin >> user_size1;
	cout << "Intput array columns-";
	cin >> user_size2;
	cout << "Input array-";
	int **arr = new int*[user_size1];
	for (int i = 0; i < user_size1; i++) {
		arr[i] = new int[user_size2];
		for (int j = 0; j < user_size2; j++) {
			cin >> arr[i][j];
		}
	}
	//ввод масива

	cout << endl << endl;

	for (int i = 0; i < user_size1; i++) {
		for (int j = 0; j < user_size2; j++) {
			cout.setf(ios::left);
			cout.width(5);
			cout << arr[i][j]<<"  ";
		}
		cout << endl;
	}
	//вывод масива пользователя

	for (int i = 0; i < user_size1; i++) {
		arr[i][user_size2 - 1] = 0;
		for (int j = 0; j < user_size2-1; j++) {
			arr[i][user_size2 - 1] += arr[i][j];
		}
	}

	cout << endl << endl;

	for (int i = 0; i < user_size1; i++) {
		for (int j = 0; j < user_size2; j++) {
			cout.setf(ios::left);
			cout.width(5);
			cout << arr[i][j] << "  ";
		}
		cout << endl;
	}
	//вывод конечного масива 

	cout << endl << endl;
	for (int i = 0; i < user_size1; i++) {
		delete[]arr[i];
	}
	system("pause");
}