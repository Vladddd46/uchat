#include <iostream>
#include <time.h>

using namespace std;

void createRadomIntArr(int *arr, const int size) {
    time(NULL);
    for(int i = 0; i < size; i++) {
        *(arr + i) = rand() % 10;
    }
}

void printArr(int *arr, const int size) {
    for (int i = 0; i < size; i++) {
        cout << *(arr + i) << "  ";
    }
    cout << endl;
}

static int countElementsMoreFive(int *arr, const int size) {
    int counter = 0;


    for(int i = 0; i < size; i++) {
    	if(*(arr + i) > 5) {
    		counter++;
    	}
    }
    return counter;
}

int* deleteArrElementMoreFive(int *arr, const int size) {
	int countNumberToDelete = countElementsMoreFive(arr, size);
	int* arrNew = new int[size - countNumberToDelete];
	int indexNewArr = 0;

    for(int i = 0; i < size; i++) {
    	if(*(arr + i) <= 5) {
            *(arrNew + indexNewArr) = *(arr + i);
            indexNewArr++;
        }
    }
    return arrNew;
}

static void printBoolStatus(bool status) {
    if(status) {
    	cout << "True" << endl;
    }
    else {
    	cout << "False" << endl;
    }
}

bool checkThreeEvenNUmberInRow(int *arr, const int size) {
	bool status = false;
	int row = 0;

	for(int i = 0; i < size; i++) {
		if(row == 3) {
			status = true;
			break;
		}
        else if(!(*(arr + i) & 1)) {
        	row++;
        }
        else {
        	row = 0;
        }
	}
    return status;
}

void swapEachFiveElements(int *arr, const int size) {
    int counterToFive = 0;

    for(int i = 0; i < size; i++) {
    	counterToFive++;
    	if(counterToFive == 5 && i < size - 1) {
    		int swapNumber = *(arr + i);

            *(arr + i) = *(arr + i + 1);
            *(arr + i + 1) = swapNumber;
            counterToFive = 0;
    	}
    }
}

int main() {
    int *arr;
    int size;
    int newSize;
    int *newArr;

    cout << "Enter size of array: ";
    cin >> size;
    arr = new int[size];
    createRadomIntArr(arr, size);
    cout << "Generated array" << endl;
    printArr(arr, size);
    cout << "Delete all elements > 5" << endl;
    newSize = size - countElementsMoreFive(arr, size);
    newArr = deleteArrElementMoreFive(arr, size);
    printArr(newArr, newSize);
    cout << "I checked is it 3 even numbers in a row. Status is" << endl;
    printBoolStatus(checkThreeEvenNUmberInRow(arr, size));
    cout << "I swaped each 5 number in array" << endl;
    swapEachFiveElements(arr, size);
    printArr(arr, size);
    return 0;
}
