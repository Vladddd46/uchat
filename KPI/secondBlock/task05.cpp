#include <iostream>

static double mx_func_result(double chislo) {
	double result = 0;

    result = 5 - ((chislo * chislo) / 2);
    return result;
}

static void mx_print_spaces(double chislo) {
	int checker = chislo;

    if(chislo < 0 && chislo - checker < 0)
    	std::cout << "  ";
    else if(chislo < 0)
        std::cout << "    ";
    else if(chislo - checker > 0)
    	std::cout << "   ";
    else
    	std::cout << "     ";
}

int main() {
    double *arr = (double*)malloc(sizeof(double) * 21);
    int index = 0;
    double chislo = -5;
    int result;

    for(; chislo <= 5; index++) {
    	*(arr + index) = chislo;
    	chislo += 0.5; 
    }
    for(index = 0; index < 21; index++) {
    	std::cout << "X = " << *(arr + index);
    	mx_print_spaces(*(arr + index));
    	result = mx_func_result(*(arr + index));
    	std::cout << "Y = " << result << "\n";
    }
    return 0;
}
