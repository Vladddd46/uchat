#include <iostream>

using namespace std;

struct symbolStack {
	char letter;

	symbolStack* next;
	symbolStack(): next(NULL) {}
};

char* getUserString() {
	char* input;

	cout << "Enter string to fill stack: ";
    cin >> input;
    return input;
}

symbolStack* fillList(symbolStack* list) {
	char *word = getUserString();
    int len = strlen(word);
	symbolStack* head = list;

    for(int i = 0; i < len; i++) {
        list -> letter = *(word + i);
        list -> next = new symbolStack;
        list = list -> next;
    }
    return head;
}

void printList(symbolStack* list) {
	symbolStack* listCopy = list;

    while(list) {
    	if(list -> letter) {
    	    if(list -> letter == 'a') {
                cout << list -> letter << " - Look! I found 'a' symbol here" << endl;
    	    }
    	    else {
                cout << list -> letter << endl;
    	    }
    	}
    	else {
    		cout << "NULL" << endl;
    	}
        list = list -> next;
    }
}

int main() {
    symbolStack *list;

    list = fillList(list);
    printList(list);
    return 0;
}
