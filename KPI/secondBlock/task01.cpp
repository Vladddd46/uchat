#include <iostream>

int main() {
    double var;
    double count = 0;
    double suma = 0;
    double avrg;

    while(var != 0) {
    	std::cout << "\rEnter new number: ";
    	std::cin >> var;
    	count++;
    	suma += var;
    }
    count--;
    avrg = suma / count;
    std::cout << "\nCount - " << count << "\nSuma - " << suma;
    std::cout << "\nAverage - " << avrg;
    return 0;
}
