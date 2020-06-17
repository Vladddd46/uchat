#include <iostream>

static int mx_strcmp(const char *s1, const char *s2) {
    int counter = 0;

    while (*(s1 + counter) == *(s2 + counter)) {
        if (*(s1 + counter) == '\0' && *(s2 + counter) == '\0')
            return 0;
    counter++;
    }
    return s1[counter] - s2[counter];
}

static int mx_find_special(int* ages, char* command) {
	int result = *ages;
    int index = 0;
    
    if(!mx_strcmp(command, "min"))
        while(*(ages + index)) {
            if(result > *(ages + index))
            	result = *(ages + index);
            index++;
        }
    else if(!mx_strcmp(command, "max"))
        while(*(ages + index)) {
            if(result < *(ages + index))
            	result = *(ages + index);
            index++;
        }
    return result;
}

static int mx_get_avrg(int* ages) {
    int sum = 0;
    int count = 0;
    int avrg;

    while(*(ages + count)) {
    	sum += *(ages + count);
    	count++;
    }
    avrg = sum / count;
    return avrg;
}

int main() {
    int people;
    int* ages;
    int avrg;
    int min;
    int max;

    std::cout << "How many people visited gym? \nAnswer: ";
    std::cin >> people;
    ages = (int*)malloc(sizeof(int) * people);
    for(int i = 0; i < people; i++) {
        std::cout << "Write age of each visitor: ";
        std::cin >> *(ages + i);
    }
    avrg = mx_get_avrg(ages);
    min = mx_find_special(ages, (char*)"min");
    max = mx_find_special(ages, (char*)"max");
    std::cout << "Average age is - " << avrg;
    std::cout << "\nMin age is - " << min;
    std::cout << "\nMax age is - " << max;
    return 0;
}
