#include "uchat.h"

bool isPrime(long long int prime) {
    long long int n = (long long int)sqrt((double)prime);

    for(long long int i = 2; i <= n; i++)
        if(prime % i == 0)
            return false;

    return true;
}

long int bcd(long long int n1, long long int n2){
    while(n1 > 0) {
        long int temp;

        temp = n1;
        n1 = n2 % n1;
        n2 = temp;
    }

    return n2;
}

long long int getE(long long int n) {
    long long int e;

    for (e = 2; e < n; e++)
        if(bcd(e, n) == 1)
            return e;

    return -1;
}

long long int getD(long long int e, long long int el) {
    long long int r = 1;

    do {
        r += el;
    }while (r % e != 0);

    return r / e;;
}

long long int modexp(long long int base, long long int e, long long int mod) {
    unsigned long long res = 1;

    while (e != 0) {
        if ((e & 1) != 0)
            res = (1ll * res * base) % mod;

        base = (1ll * base * base) % mod;
        e >>= 1;
    }

    return res;
}

int numberOfDigits(long long int n) {
    int count = 0;
    while (n != 0) {
        n = n / 10;
        count++;
    }
    return count;
}

int mx_get_num_by_index(char* str, int index) {
    char* part_str = mx_strnew(10);
    int num1 = 0;
    int counter = 0;
    int ind = 0;

    for(; counter < index; ind++) {
        if(*(str + ind) == '-') {
            counter++;
        }
    }
    for(int i = 0; *(str + ind) != '-' && *(str + ind) != '\0'; ind++, i++) {
        *(part_str + i) = *(str + ind);
    }
    num1 = atoi(part_str);
    return num1;
} 

int count_string_size(char* str) {
    int counter = 0;

    for(int i = 0; str[i]; i++) {
        if(*(str + i) == '-') {
            counter++;
        }
    }
    counter--;
    return counter;
}

char* mx_rsa_decode_password(char* str) {
    unsigned long int num1 = mx_get_num_by_index(str, 0), num2 = mx_get_num_by_index(str, 1);

    long long int el = (num1 - 1) * (num2 - 1);
    long long int multiplyNums = num1 * num2;
    char* descrypt = mx_strnew(100);

    long long int e = getE(el);
    long long int d = getD(e, el);

    for(int i = 0; i < count_string_size(str); i++) {
        *(descrypt + i) = modexp(mx_get_num_by_index(str, i + 2), d, multiplyNums);
    }

    return descrypt;
}
