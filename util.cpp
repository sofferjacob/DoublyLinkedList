/*
Jacobo Soffer Levy
A01028653
Definition of utility functions.
Modified: 04/04/21
*/
#include <algorithm> 
#include <iostream>
#include "util.h"

using namespace std;

bool validNumber(string& str) {
    for (int i = 0; i < str.length(); i++) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}

int getOption() {
    cout << "Selection: " << endl;
    string input;
    getline(cin, input);
    trim(input);
    if (input.length() == 1 && input[0] == 'q') {
        return -1;
    }
    if (!validNumber(input) || input.length() == 0) {
        cout << "Invalid selection, please enter a valid number" << endl;
        return getOption();
    }
    int selection = stoi(input);
    if (selection < 1 || selection > 15) {
        cout << "Invalid selection, please enter a valid option" << endl;
        return getOption();
    }
    return selection;
}

// Returns a positive integer
int getInt() {
    cout << "Index: " << endl;
    string input;
    getline(cin, input);
    trim(input);
    if (input.length() == 1 && input[0] == 'q') {
        return -1;
    }
    if (!validNumber(input) || input.length() == 0) {
        cout << "Invalid selection, please enter a valid number" << endl;
        return getInt();
    }
    int selection = stoi(input);
    if (selection < 0) {
        cout << "Invalid selection, please enter a valid option" << endl;
        return getInt();
    }
    return selection;
}

string getString() {
    cout << "Element: " << endl;
    string input;
    getline(cin, input);
    trim(input);
    if (input.length() == 0) {
        cout << "Invalid input, please try again." << endl;
        return getString();
    }
    return input;
}

inline void leftTrim(string& str) {
    str.erase(str.begin(), find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !isspace(ch);
        }));
}

inline void rightTrim(string& str) {
    str.erase(find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !isspace(ch);
        }).base(), str.end());
}

inline void trim(string& str) {
    leftTrim(str);
    rightTrim(str);
}