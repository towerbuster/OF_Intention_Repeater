#include <iostream>
#include <string>

using namespace std;

void custom_copy(char* c1, char* c2) {
    int i = 0;
    
    // Copy
    for (i = 0; i < strlen(c1); i++) {
        c2[i] = c1[i];
    }
    c2[i] = 0;
    cout << (char*)c2 << "\r";

    // Delete
    for (i = 0; i < strlen(c1); i++) {
        c2[i] = 0;
    }
    c2[i] = 0;
    cout << (char*)c2 << "\r";
}

int main()
{
    string intention;
    string target;

    cout << "Intention ? ";
    getline(cin, intention);

    cout << "Target ? ";
    getline(cin, target);

    char * intention_from = (char *) intention.c_str();
    char* intention_to = new char[strlen(intention_from) + 1];

    char* target_from = (char*)target.c_str();
    char* target_to = new char[strlen(target_from) + 1];

    while (true) {
        custom_copy(intention_from, intention_to);
        custom_copy(target_from, target_to);
    }
}

