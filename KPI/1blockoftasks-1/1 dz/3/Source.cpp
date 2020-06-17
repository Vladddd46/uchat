//Найти суму и произведение цифр
#include <iostream>

using namespace std;

int main() {
	int sum = 0;
	int num;
	int product = 1;

	cout << "Input number-" ;
	cin >> num;

    if(num < 0) {
    	num *= -1;
    }
    if(num == 0) {
		product = 0;
	}
	while ( num > 0 ) {//отрывает цифру от числа
		int temp;
		temp = num % 10;
		product *= temp;
		sum += temp;
		num /= 10;
	}

	cout << "Sum=" << sum << endl << "Dob=" << product	 << endl;
	system("wait");
	return 0;
}