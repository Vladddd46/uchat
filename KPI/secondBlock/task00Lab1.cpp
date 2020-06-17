#include <iostream>
#include <math.h>

static double mx_pow(double x, double n) {
	double result = 1;

	if(n > 0)
        for(int i = 0; i < n; i++)
            result *= x;
    else if(n < 0) {
    	for(int i = 0; i > n; i--)
    		result *= x;
    	result = 1 / result;
    }
    return result;
}


int main() {
    double result = 0;
    double result_eps = 0;
    double *arr = (double*)malloc(sizeof(double) * 41);
    int index = 0;
    int eps;
    int n;
    double x;
    double *arr_funcion = (double*)malloc(sizeof(double) * 41);
    double function_value;
    double diff = 100;
    double x_diff;
    int iterations = 0;

    std::cout << "Enter epsilon value: ";
    std::cin >> eps;
    for(x = -1; x <= 1; x += 0.05) {
        for(n = 1; n <= 100; n++) {
            result += (mx_pow(x, (2 * n + 1))) / (2 * n + 1);
            function_value = log10((1 + x) / (1 - x));
            iterations++;
        }
        *(arr + index) = result;
        *(arr_funcion + index) = function_value;
        index++;
        result = 0;
    }
    for(double i = 0, j = -1; i < 41; i++, j += 0.05) {
        iterations++;
    	printf("X = %.2f", j);
    	printf(", Suma = %.8f  Function result = %.8f\n", *(arr + (int)i), 
         *(arr_funcion + (int)i));
    	if (*(arr_funcion + (int)i) - *(arr + (int)i) < diff) {
    		diff = *(arr_funcion + (int)i) - *(arr + (int)i);
    		x_diff = j;
    	}
    	result += *(arr + (int)i);
    }
    x = -1;
    while(result_eps >= eps && x <= 1) {
    	n = 0;
    	do {
            iterations++;
    		result_eps += (mx_pow(x, (2 * n + 1))) / (2 * n + 1);
            n++;
    	} while(result_eps >= eps && n <= 100);
    	x += 0.05;
    }
    printf("\nResult = %.8f \nResult with epsilon = %.8f",result, result_eps);
    printf("\nThe closest values beetween is - %.2f  at X = %.2f \n", diff, x_diff);
    printf("\nIterations - %d\n", iterations);
    free(arr_funcion);
    free(arr);
    return 0;
}
