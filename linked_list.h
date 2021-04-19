/*
Jacobo Soffer Levy
A01028653
Doubly Linked List
implementation.
Modified: 19/04/21
*/
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <functional>
#include <stdexcept>
#include <iostream>
#include <set>
#include "node.h"

template<class T>
class Queue;

template<class T>
class LinkedList {
public:
    LinkedList();
    ~LinkedList();
    // Returns the size of the list
    int getSize();
    // Deletes the list's elements and resets it.
    void clear();
    // Adds an element to the begging of the list
    void addFirst(T);
    // Adds an element to the end of the list
    void pushBack(T);
    // Deletes an element at the specified index
    bool deleteAt(int);
    // Deletes the first ocurrence of the element
    // passed as an argument. Returns true if element
    // was found.
    bool deleteElement(T);
    // Updates an element at the specified index
    void updateAt(T, int);
    // Updates the first occurrence of element "e"
    // with element "n". Throws out_of_range if
    // element is not found.
    void updateElement(T e, T n);
    // Returns the index of the element
    // provided as an argument. Returns -1
    // if the element wasn't found.
    int indexOf(T);
    // Prints the entire list
    void print(int, int);
    // Sorts the list (in place) using Merge Sort
    void sort();
    // Performs an operation on the node at the specified index
    void opAt(std::function<void(Node<T>*)>, int);
    // Executes a function on every node of the list (or on every node starting from the 'from' parameter
    // Function should return -1 to break.
    void forEach(std::function<int(Node<T>*, int)> f, int from = 0);
    // Returns the first node in the list
    Node<T>* getFirst();
    // Returns the last node in the list
    Node<T>* getLast();
    // Duplicates every element in the list
    void duplicate();
    // Removes any duplicated value from the list
    void removeDuplicates();
    // Retrieves a node from the list. Returns the node at the specified index.
    Node<T>* at(int);
    // same as at
    Node<T>* operator[](int);
    // Updates the contents of this list with
    // the contents of other list.
    void operator=(LinkedList<T>& other);
private:
    // Pounter to the first node on the list
    Node<T>* head;
    // Pointer to the last node on the list
    Node<T>* tail;
    // Size of the list
    int size;
    // Auziliary method used in sort()
    Node<T>* merge(Node<T>*, Node<T>*);
};

template<class T>
LinkedList<T>::LinkedList() {
    head = tail = nullptr;
    size = 0;
}

template<class T>
int LinkedList<T>::getSize() {
    return size;
}

template<class T>
void LinkedList<T>::pushBack(T data) {
    if (head == nullptr) {
        head = new Node<T>(data, nullptr, nullptr);
        tail = head;
        size += 1;
        return;
    }
    Node<T>* node = new Node<T>(data, tail, nullptr);
    tail->setNext(node);
    tail = node;
    size++;
}

template<class T>
void LinkedList<T>::addFirst(T data) {
    if (head == nullptr) {
        head = new Node<T>(data, nullptr, nullptr);
        tail = head;
        size += 1;
        return;
    }
    Node<T>* node = new Node<T>(data, nullptr, head);
    head->setPrev(node);
    head = node;
    size++;
}


template<class T>
void LinkedList<T>::opAt(std::function<void(Node<T>*)> f, int i) {
    if (i >= size) {
        throw std::out_of_range("Index out of range");
    }
    if (i == 0) {
        f(head);
        return;
    }
    if (i == size - 1) {
        f(tail);
        return;
    }
    Node<T>* result;
    if (i < (size - 1) / 2) {
        result = head;
        for (int j = 0; j < i; j++) {
            result = result->getNext();
        }
    }
    result = tail;
    for (int j = size - 1; j > i; j--) {
        result = result->getPrev();
    }
    f(result);
}

template<class T>
void LinkedList<T>::forEach(std::function<int(Node<T>*, int)> f, int from) {
    if (from >= size) {
        throw std::out_of_range("Index out of range");
    }
    Node<T>* result;
    if (from < (size - 1) / 2) {
        result = at(from);
        for (int j = from; j < size; j++) {
            int res = f(result, j);
            if (res == -1) break;
            result = result->getNext();
        }
        return;
    }
    result = tail;
    for (int j = size - 1; j > from - 1; j--) {
        int res = f(result, j);
        if (res == -1) break;
        result = result->getPrev();
    }
}

template<class T>
Node<T>* LinkedList<T>::at(int i) {
    if (i >= size) {
        throw std::out_of_range("Index out of range");
    }
    if (i == 0) {
        return head;
    }
    if (i == size - 1) {
        return tail;
    }
    Node<T>* result;
    if (i < (size - 1) / 2) {
        result = head;
        for (int j = 0; j < i; j++) {
            result = result->getNext();
        }
    }
    result = tail;
    for (int j = size - 1; j > i; j--) {
        result = result->getPrev();
    }
    return result;
}

template<class T>
Node<T>* LinkedList<T>::getFirst() {
    return head;
}

template<class T>
Node<T>* LinkedList<T>::getLast() {
    return tail;
}

template<class T>
Node<T>* LinkedList<T>::operator[](int i) {
    return at(i);
}

template<class T>
void LinkedList<T>::updateAt(T newElement, int i) {
    *at(i) = newElement;
}

template<class T>
void LinkedList<T>::updateElement(T e, T n) {
    bool found = false;
    forEach([this, e, n, &found](Node<T>* node, int i) {
        if (node->getData() == e) {
            *node = n;
            found = true;
            return -1;
        }
        return 0;
        });
    if (!found) {
        throw std::out_of_range("Element to update not found");
    }
}

template<class T>
int LinkedList<T>::indexOf(T element) {
    int index = -1;
    forEach([element, &index](Node<T>* e, int i) {
        if (e->getData() == element) {
            index = i;
            return -1;
        }
        return 0;
        });
    return index;
}

template<class T>
bool LinkedList<T>::deleteAt(int i) {
    if (size == 1 && i == 0) {
        delete head;
        size--;
        clear();
        return true;
    }
    opAt([this, i](Node<T>* e) {
        Node<T>* prev = e->getPrev();
        Node<T>* next = e->getNext();
        if (prev != nullptr) {
            prev->setNext(next);
        }
        else {
            // Change head
            head = next;
            head->setPrev(nullptr);
        }
        if (next != nullptr) {
            next->setPrev(prev);
        }
        else {
            tail = prev;
            tail->setNext(nullptr);
        }
        size--;
        delete e;
        }, i);
    return true;
}

template<class T>
bool LinkedList<T>::deleteElement(T element) {
    bool found = false;
    forEach([this, &found, &element](Node<T>* e, int i) {
        if (e->getData() == element) {
            found = true;
            Node<T>* prev = e->getPrev();
            Node<T>* next = e->getNext();
            if (prev != nullptr) {
                prev->setNext(next);
            }
            else {
                head = next;
                head->setPrev(nullptr);
            }
            if (next != nullptr) {
                next->setPrev(prev);
            }
            else {
                tail = prev;
                tail->setNext(nullptr);
            }
            size--;
            delete e;
            return -1;
        }
        return 0;
        });
    return found;
}

template<class T>
void LinkedList<T>::duplicate() {
    int lastI = size - 1;
    forEach([this, lastI](Node<T>* e, int i) {
        if (i > lastI) return -1;
        pushBack(e->getData());
        return 0;
        });
}

template<class T>
void LinkedList<T>::removeDuplicates() {
    // O(n^2)
    forEach([this](Node<T>* n, int i) {
        forEach([this, n, i](Node<T>* e, int j) {
            if (e->getData() == n->getData()) {
                deleteAt(j);
            }
            return 0;
            }, i + 1);
        return 0;
        });
}

template<class T>
Node<T>* LinkedList<T>::merge(Node<T>* l1, Node<T>* l2) {
    // Doubly Linked list simulation
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    while (l1 != nullptr && l2 != nullptr) {
        T l1Data = l1->getData();
        T l2Data = l2->getData();
        if ((l1Data) > (l2Data)) {
            // Move it to a tmp variable
            Node<T>* tmp = l2;
            l2 = l2->getNext();
            tmp->setNext(nullptr);
            if (head == nullptr) {
                tmp->setPrev(nullptr);
                head = tmp;
                tail = tmp;
            }
            else {
                tmp->setPrev(tail);
                tail->setNext(tmp);
                tail = tmp;
            }
        }
        else {
            // Move it to a tmp variable
            Node<T>* tmp = l1;
            l1 = l1->getNext();
            tmp->setNext(nullptr);
            if (head == nullptr) {
                tmp->setPrev(nullptr);
                head = tmp;
                tail = tmp;
            }
            else {
                tmp->setPrev(tail);
                tail->setNext(tmp);
                tail = tmp;
            }
        }
    }
    while (l1 != nullptr) {
        Node<T>* tmp = l1;
        l1 = l1->getNext();
        tmp->setNext(nullptr);
        tmp->setPrev(tail);
        tail->setNext(tmp);
        tail = tmp;
    }
    while (l2 != nullptr) {
        Node<T>* tmp = l2;
        l2 = l2->getNext();
        tmp->setNext(nullptr);
        tmp->setPrev(tail);
        tail->setNext(tmp);
        tail = tmp;
    }
    return head;
}

template<class T>
void LinkedList<T>::sort() {
    // Here we need to queues
    // The first to store all the nodes w/next and prev
    // pointers. The second one to remove them. If we were
    // to remove them directly in the first one, the list would break.
    Queue<Node<T>*> nodes;
    Queue<Node<T>*> queue;
    forEach([this, &nodes](Node<T>* e, int i) {
        nodes.push(e);
        return 0;
        });
    while (!nodes.isEmpty()) {
        Node<T>* e = nodes.poll();
        e->setNext(nullptr);
        e->setPrev(nullptr);
        queue.push(e);
    }
    while (queue.size() > 1) {
        Node<T>* l1 = queue.poll();
        Node<T>* l2 = queue.poll();
        Node<T>* res = merge(l1, l2);
        if (res == nullptr) continue;
        queue.push(res);
    }
    // Set the new head and tail
    Node<T>* newHead = queue.poll();
    this->head = newHead;
    Node<T>* newTail = head;
    while (newTail->getNext() != nullptr) {
        newTail = newTail->getNext();
    }
    this->tail = newTail;
}

template<class T>
void LinkedList<T>::print(int from, int to) {
    for (int i = from; i <= to; i++) {
        std::cout << (at(i)->getData()) << " ";
    }
}

template<class T>
void LinkedList<T>::clear() {
    // Free the memory
    Node<T>* current = head;
    for (int i = 0; i < size; i++) {
        Node<T>* temp = current;
        current = temp->getNext();
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template<class T>
void LinkedList<T>::operator=(LinkedList<T>& other) {
    clear();
    // We create new nodes instead of using the ones
    // from other for memory safety
    other.forEach([this](Node<T>* n, int i) {
        pushBack(n->getData());
        return 0;
        });
}

template<class T>
LinkedList<T>::~LinkedList() {
    clear();
}

template<class T>
class Queue {
public:
    Queue();
    // Adds an element to the queue
    void push(T data);
    // Removes an element from the queue
    T poll();
    bool isEmpty();
    // Returns the size of the queue
    int size();
private:
    LinkedList<T> queue;
};


template<class T>
Queue<T>::Queue() {}

template<class T>
void Queue<T>::push(T data) {
    queue.addFirst(data);
}

template<class T>
T Queue<T>::poll() {
    if (isEmpty()) {
        throw std::out_of_range("Queue is empty");
    }
    T e = queue[queue.getSize() - 1]->getData();
    queue.deleteAt(queue.getSize() - 1);
    return e;
}

template<class T>
bool Queue<T>::isEmpty() {
    return queue.getSize() == 0;
}

template<class T>
int Queue<T>::size() {
    return queue.getSize();
}

#endif