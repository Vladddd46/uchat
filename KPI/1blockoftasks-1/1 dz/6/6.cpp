#include <iostream>
#include <time.h>
using namespace std;

int main() {
    int a, b;

    cout << "Enter length of matrix - ";
    cin >> a;
    cout << "Enter hight of matrix - "; 
    cin >> b;

    float *avg;
    int **mas;
    avg = new float[a];
    mas = new int *[a];
    int n = 0;

    for (int i = 0; i < a; i++) {
        *(mas + i) = new int[b];
    }

    time(NULL);
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            *(*(mas + i) + j) = rand() % 10 - 5;
            cout << *(*(mas + i) + j) << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < a; i++) {
        *(avg + i) = 0;
        for (int j = 0; j < b; j++) {
            if (*(*(mas + i) + j) > 0) {
                *(avg + i) += *(*(mas + i) + j);
                n++;
            }
        }
        *(avg + i) = *(avg + i) / n;
        n = 0;
    }
    for (int i = 0; i < a; i++) {
        cout << *(avg + i) << endl;
    }
    for (int i = 0; i < a; i++) {
        delete[] *(mas + i);
    }
    system("wait");
    return 0;

}