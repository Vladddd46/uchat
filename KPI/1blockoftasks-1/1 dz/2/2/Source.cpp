#include <iostream>
#include <math.h>

using namespace std;

int main() {
	double number;
	double power;
	double product = 1;

	cout << "Chislo:" << endl;
	cin >> number;
	cout << "Stepen:" << endl;
	cin >> power;

	if (power != 0) {
		for (int i = 0; i < abs(power); i++) {
			product *= number;
		}
		if (power < 0) {
			product = 1 / product;
		}
	}
	cout << "Proizvidenie:" << product << endl;
	system("wait");
}
