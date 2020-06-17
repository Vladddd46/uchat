//Найти факториал
#include <iostream>

using namespace std;

int main() {
	int n;
	int fact=1;
	
	do {
		cout << "Input num-";
		cin >> n;
	} while (n < 0 || n > 12);

	for (int i = 2; i <= n; i++) {
		fact *= i;
	}
	cout << "Factorial=" << fact << endl;
	return 0;
}