#include <iostream>
#include <chrono>
#include <limits>
#include <regex>

using namespace std;

struct CircArrayQueue
{
    //core variables
    int back;
    int front;
    int length;
    int* Array;

    //member functions
    int peek();
    int size();
    void enQueue(int value);
    int deQueue();
    
    //Let's make a constructor. This will initialize our main array.
    CircArrayQueue(int size = 10)
    {
        
        //define a standard  size
        int number = 10;
        //increase as needed
        while (size > number) {
            number *= 2;
        }
        //set our other variables
        front = back = -1;
        length = size;
        //create the main array
        Array = new int[number];
    }
    //Time for a destructor
    ~CircArrayQueue() {
        delete[] Array;
    }
    //Gave up on the copy constructor
    /*CircArrayQueue& operator =(CircArrayQueue& newArray) {
        for (int i = 0; i < length; i++) {
            int num = this->deQueue();
            newArray.enQueue(num);  
        }
        return newArray;
    }*/

};

//First, I did the size function because it was easy. It just returns length. 
int CircArrayQueue::size()
{
    return length;
}

//enqueue adds a value to the "queue"
void CircArrayQueue::enQueue(int value)
{
    
    //check if the array is full here by using the mod function. This works because the array is circular, so even if front is double of length, it still works.
    if ((back == (front - 1) % (length - 1)) or (front == 0 and back == length - 1))
    {
        int* new_array = new int [length * 2];
        for (int x = 0; x < length; x++) {
            new_array[x] = Array[x];
        }
        length *= 2;
        Array = new_array;
        
    }
    //Check if it's empty
    else if (front == -1) 
    {
        front = 0;
        back = 0;
        Array[back] = value;
    }
    //Other cases
    else if (back == length - 1 and front != 0)
    {
        back = 0;
        Array[back] = value;
    }

    else
    {
        back++;
        Array[back] = value;
    }
}

int CircArrayQueue::peek()
{
    //Cant return anything if it's empty right?
    if (front == -1)
    {
        return NULL;
    }
    //But you can if it's not, so:
    return Array[front];
}
//time to remove stuff
int CircArrayQueue::deQueue()
{
    //can't remove from an empty array
    if (front == -1)
    {
        return NULL;
    }
    //set a number so we can return at the end
    int data = Array[front];
    Array[front] = -1;
    //Is it empty after we remove?
    if (front == back)
    {
        front = -1;
        back = -1;
    }
    //Is it just barely too full?
    else if (front == length - 1)
        front = 0;
    //Otherwise
    else
        front++;
    //return
    return data;
}


//--------------------------------------------------Now for the Linked List implementation ------------------------------------------------

//define the node
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
    
bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
int main()
{
    string response = "";
    cout << "Would you like to use a Circular Array? (Yes or No?)" << endl;
    cin >> response;
    if (response == "Yes") {
        string num = "";
        cout << "How big do you want your array to be?" << endl;
        cin >> num;

        if (!is_number(num)) {
            cout << "That is not a number!" << endl;
            return -1;
        }
        
        CircArrayQueue q(stoi(num));
        int x = 0;
        int value;

        while (x != 4) {
            cout << " Do you want to enqueue, dequeue, or peek?" << endl;
            cout << "Enter 1 for enqueue, 2 for dequeue, and 3 for peek. Enter 4 to quit." << endl;
            cin >> x;

            switch (x) {

                case(1):
                    cout << "Please enter the value you would like to add: ";
                    cin >> value;
                    q.enQueue(value);
                    cout << value << " has been added!" << endl;
                    break;
                case(2):
                    cout << "Deleting first value!" << endl;
                    cout << "The value that was deleted was " << q.deQueue() << "." << endl;
                    break;
                case(3):
                    cout << "The top value is: " << q.peek() << endl;
                case(4): 
                    break;
                default:
                    cout << "This is not a valid value!" << endl;
                    cout << "Please try again." << endl;
            }
        }
    }
    if (response == "No") {
        LinkedListQueue q;
        int x = 0;
        int value;

        while (x != 4) {
            cout << " Do you want to enqueue, dequeue, or peek?" << endl;
            cout << "Enter 1 for enqueue, 2 for dequeue, and 3 for peek. Enter 4 to quit." << endl;
            cin >> x;

            switch (x) {

            case(1):
                cout << "Please enter the value you would like to add: ";
                cin >> value;
                q.enQueue(value);
                cout << value << " has been added!" << endl;
                break;
            case(2):
                cout << "Deleting first value!" << endl;
                cout << "The value that was deleted was " << q.deQueue() << "." << endl;
                break;
            case(3):
                cout << "The top value is: " << q.peek() << endl;
            case(4):
                break;
            default:
                cout << "This is not a valid value!" << endl;
                cout << "Please try again." << endl;
            }
        }
    }
    
    else {
        cout << "Invalid Response";
        return -1;
    }
    return 0;
}