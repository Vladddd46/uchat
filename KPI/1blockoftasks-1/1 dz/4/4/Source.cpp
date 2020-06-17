//Найти количесво элементов в заданом масиве отличающихся от мин на 5
#include <iostream>

using namespace std;

int main() {
	int min;
	int quantity=0;
	int userSize;

	cout << "Input array size- ";
	cin >> userSize;
	int arr[userSize];

	for (int i = 0; i < userSize; i++) {
		cout << "Input " << i + 1 << " element of array - ";
		cin >> arr[i];
		// cout << endl;
	}
	min = arr[0];
	for (int i = 1; i < userSize; i++) {
		if (arr[i] < min) {
			min = arr[i];
		}
	}
	for (int i = 0; i < userSize; i++) {
		if (arr[i] == min + 5) {
			quantity++;
		}
	}
	cout << "Quantity=" << quantity << endl	;
	system("wait");
	return 0;
}