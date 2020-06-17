#include <iostream>

using namespace std;

static bool findSameElements(int *arr, int user_size) {
    for (int i = 0; i < user_size-1; i++) {
		for (int j=i+1; j < user_size; j++) {
			if (arr[i] == arr[j]) {
				return true;
			}
		}
	}
	return false;
}

int main() {
	int user_size;
	bool mark=false;

	cout << "Input size-";
	cin >> user_size;

	int *arr = new int[user_size];

	for (int i = 0; i < user_size; i++) {
		cout << "Input array - ";
		cin >> *(arr + i);
	}

	mark = findSameElements(arr, user_size);

	if (mark) {
		cout << "Have the same elements"<<endl;
	}
	else {
		cout << "Haven't the same elements" << endl;
	}
	delete[]arr;
	system("wait");
	return 0;
}