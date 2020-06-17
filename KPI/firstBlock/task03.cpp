#include <iostream>

using namespace std;

int minArrayNumber(int* arr) {
    int min = *arr;

    for(int arrIndex = 0; arrIndex < 6; arrIndex++)
    	if(*(arr + arrIndex) < min)
    		min = *(arr + arrIndex);
    return min;
}

int countMinDiffs(int* arr) {
	int min = minArrayNumber(arr);
	int result = 0;

	for(int arrIndex = 0; arrIndex < 6; arrIndex++)
    	if(*(arr + arrIndex) - min > 5 || min - *(arr + arrIndex) > 5)
    		result++;
    return result;
}

int main() {
	int arr[] = {32, -5, 3, 9, 12, 43};
    cout << countMinDiffs(arr) << endl;
    return 0;
}
