#include <iostream>

using namespace std;

long long factorial(int number) {
    long long result = 1;

    if(number < 20)
        for(; number > 0; number--) 
        	result *= number;
    else
    	cout << "Too high number!" << endl;
    return result;
}

int main() {
    cout << factorial(21) << endl;
    return 0;
}
