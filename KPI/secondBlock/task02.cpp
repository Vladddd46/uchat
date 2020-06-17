#include <iostream>

int main() {
	int suma = 0;
    int minRange;
    int maxRange;

    std::cout << "Enter min range: ";
    std::cin >> minRange;
    std::cout << "Enter max range: ";
    std::cin >> maxRange;
    for(int i = minRange; i <= maxRange; i++)
    	if(i % 2 != 0)
    		suma += i;
    std::cout << "Sum of even numbers in range [" 
    << minRange << ", " << maxRange << "] is = " << suma;
    return 0;
}
