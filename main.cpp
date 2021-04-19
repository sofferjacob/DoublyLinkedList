#include <iostream>
#include <stdexcept>
#include "linked_list.h"
#include "util.h"

using namespace std;

int main() {
    LinkedList<string> list;
    bool keepLooping = true;
    while (keepLooping) {
        cout << "Doubly Linked List" << endl;
        cout << "Enter 'q' at any prompt to exit the program" << endl;
        cout << "Select an option:" << endl;
        cout << "1: Add element to the start of the list" << endl;
        cout << "2: Add element to the end of the list" << endl;
        cout << "3: Get size of list" << endl;
        cout << "4: Print list contents" << endl;
        cout << "5: Find an element in the list" << endl;
        cout << "6: Find and replace an element in the list" << endl;
        cout << "7: Find and delete an element in the list" << endl;
        cout << "8: Sort the list" << endl;
        cout << "9: Get an element at a specified index" << endl;
        cout << "10: Delete an element at a specified index" << endl;
        cout << "11: Update an element at a specified index" << endl;
        cout << "12: Duplicate every element in the list" << endl;
        cout << "13: Remove any duplicated elements from the list" << endl;
        cout << "14: Clear the list" << endl;
        cout << "15: Replace list contents with [4, 2, 81, 1, 9]" << endl;
        int option = getOption();
        if (option == -1) break;
        switch (option) {
        case 1: {
            string e = getString();
            list.addFirst(e);
            break;
        }
        case 2: {
            string e = getString();
            list.pushBack(e);
            break;
        }
        case 3: {
            cout << "Size: " << list.getSize() << endl;
            break;
        }
        case 4: {
            list.print(0, list.getSize() - 1);
            cout << endl;
            break;
        }
        case 5: {
            string e = getString();
            int i = list.indexOf(e);
            if (i == -1) {
                cout << "Element not found" << endl;
            }
            else {
                cout << "Element at index: " << i << endl;
            }
            break;
        }
        case 6: {
            cout << "Enter element to replace" << endl;
            string e = getString();
            cout << "Enter new element" << endl;
            string n = getString();
            try {
                list.updateElement(e, n);
                break;
            }
            catch (out_of_range e) {
                cout << "An error occured: " << e.what() << endl;
                cout << "No changes were made" << endl;
                break;
            }
            catch (...) {
                cout << "An unknown error occured, no changes were made" << endl;
                break;
            }
        }
        case 7: {
            cout << "Enter element to delete" << endl;
            string e = getString();
            bool success = list.deleteElement(e);
            if (!success) {
                cout << "Element not found, no changes were made" << endl;
            }
            break;
        }
        case 8: {
            cout << "Sorting list..." << endl;
            list.sort();
            cout << "List sorted successfully" << endl;
            break;
        }
        case 9: {
            cout << "Enter index" << endl;
            int i = getInt();
            if (i == -1) {
                keepLooping = false;
                break;
            }
            try {
                string e = list[i]->getData();
                cout << "Element at " << i << ": " << e << endl;
                break;
            }
            catch (out_of_range e) {
                cout << "An error occured: " << e.what() << endl;
                break;
            }
            catch (...) {
                cout << "An unknown error occured, no changes were made" << endl;
                break;
            }
        }
        case 10: {
            cout << "Enter index" << endl;
            int i = getInt();
            if (i == -1) {
                keepLooping = false;
                break;
            }
            try {
                list.deleteAt(i);
                break;
            }
            catch (out_of_range e) {
                cout << "An error occured: " << e.what() << endl;
                cout << "No changes were made." << endl;
                break;
            }
            catch (...) {
                cout << "An unknown error occured, no changes were made" << endl;
                break;
            }
        }
        case 11: {
            cout << "Enter index of element to update" << endl;
            int i = getInt();
            if (i == -1) {
                keepLooping = false;
                break;
            }
            cout << "Enter new element" << endl;
            string e = getString();
            try {
                list.updateAt(e, i);
                break;
            }
            catch (out_of_range e) {
                cout << "An error occured: " << e.what() << endl;
                cout << "No changes were made." << endl;
                break;
            }
            catch (...) {
                cout << "An unknown error occured, no changes were made" << endl;
                break;
            }
        }
        case 12: {
            list.duplicate();
            break;
        }
        case 13: {
            list.removeDuplicates();
            break;
        }
        case 14: {
            list.clear();
            break;
        }
        case 15: {
            LinkedList<string> otherList;
            otherList.pushBack("4");
            otherList.pushBack("2");
            otherList.pushBack("81");
            otherList.pushBack("1");
            otherList.pushBack("9");
            list = otherList;
            break;
        }
        }
    }
}