#include <iostream>

using namespace std;

long long pow(int number, int pow) {
    long long result = 1;

    for(; pow > 0; pow--) 
    	result *= number;
    return result;
}

int main() {
    cout << pow(2, 5) << endl;
    return 0;
}
