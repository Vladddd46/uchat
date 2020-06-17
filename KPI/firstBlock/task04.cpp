#include <iostream>

using namespace std;

bool checkRepeats(int* arr) {
    int sum = 1;

    for(int i = 0; i < 6 - 1; i++) {
        for(int j = i + 1; j < 6; j++) {
            if(*(arr + i) == *(arr + j)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
	int arr[] = {1, 2, 6, 3, 2, 5};
    if(checkRepeats(arr))
        cout << "Founded repeats" << endl;
    else
        cout << "All numbers are unique" << endl;
    return 0;
}
