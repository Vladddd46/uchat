#include <iostream>

using namespace std;

long long pow(int number, int pow) {
    long long result = 1;

    for(; pow > 0; pow--) result *= number;
    return result;
}

int numberLength(int number) {
    int result = 0;

    if(number == 0) result = 1;
    while(number != 0) {
        number /= 10;
        result++;
    }
    return result;
}

int multiplyDigits(int number) {
	int result = 1;
    int length = numberLength(number);

    for(int i = 1; i <= length; i++) {
    	result *= number % 10;
    	number /= 10;
    }
    return result;    
}

int sumDigits(int number) {
    int result = 0;
    int length = numberLength(number);

    for(int i = 1; i <= length; i++) {
    	result += number % 10;
    	number /= 10;
    }
    return result; 
}

int main() {
    cout << multiplyDigits(143) << endl;
    cout << sumDigits(143) << endl;
}
