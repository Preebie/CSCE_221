#include <iostream>
#include <chrono>
#include <limits>
#include <regex>

struct Node {
    int data;
    Node* _nextPtr;
    Node* _prevPtr;
};
//define the list
class LinkedListQueue {
public:
    Node* _headPtr;
    Node* _tailPtr;
    int _size;

    LinkedListQueue() {
        _headPtr = nullptr;
        _tailPtr = nullptr;
        _size = 0;
    }
    void enQueue(int newElement);
    int deQueue();
    int peek();
};
//enQueue with a value for what to enQueue
void LinkedListQueue::enQueue(int num) {

    Node* newNode = new Node();

    newNode->data = num;

    newNode->_nextPtr = nullptr;
    newNode->_prevPtr = nullptr;

    if (_headPtr == nullptr) {
        _headPtr = newNode;
        newNode->_nextPtr = _headPtr;
        newNode->_prevPtr = _headPtr;
    }
    else {
        _tailPtr = newNode;
        newNode->_nextPtr = _headPtr;
        newNode->_prevPtr = _tailPtr;
        _headPtr->_prevPtr = newNode;
    }
    _size++;
}
int LinkedListQueue::deQueue() {
    int x = 0;
    if (_headPtr != nullptr) {

        if (_headPtr->_nextPtr == _headPtr) {
            x = _headPtr->data;
            _headPtr = nullptr;

        }
        else {

            Node* temp = _headPtr;
            while (temp->_nextPtr->_nextPtr != _headPtr)
                temp = temp->_nextPtr;
            x = temp->data;
            Node* FinalNode = temp->_nextPtr;
            temp->_nextPtr = _headPtr;
            _headPtr->_prevPtr = temp;
            free(FinalNode);
        }
    }
    _size--;
    return x;
}
int LinkedListQueue::peek() {
    int x = 0;
    if (_headPtr != nullptr) {

        if (_headPtr->_nextPtr == _headPtr) {
            x = _headPtr->data;

        }
        else {

            x = _tailPtr->data;
        }
    }
    return x;
}
