#include <iostream>

int main() {
    int odd = 0;
    int even = 0;
    int number;
    int checker;
    int divider = 10;

    std::cout << "Enter number: ";
    std::cin >> number;
    while(number / divider != 0)
    	divider *= 10;
    divider /= 10;
    while(divider > 0) {
    	if((number / divider) % 2 != 0)
    		even++;
    	else
    		odd++;
    	number -= divider * (number / divider);
    	divider /= 10;
    }
    std::cout << "\nEven - " << even << ",  Odd - " << odd;
    return 0;
}
