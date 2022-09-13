#include <iostream>


using namespace std;

#define TABLE_SIZE 13

#define PRIME 7
template <typename Obj>
class DoubleHash {

    Obj* hashTable;
    int curr_size;

public:
    //check if table is full
    bool isFull()
    {

        return (curr_size == TABLE_SIZE);
    }
    //first hash function
    int hash1(Obj key)
    {
        return (key % TABLE_SIZE);
    }
    //second hash function
    int hash2(Obj key)
    {
        return (PRIME - (key % PRIME));
    }
    //constructor
    DoubleHash()
    {
        hashTable = new Obj[TABLE_SIZE];
        curr_size = 0;
        for (int i = 0; i < TABLE_SIZE; i++)
            hashTable[i] = -1;
    }
    //insert function for hash table
    void insertHash(Obj key)
    {
        if (isFull())
            return;

        int index = hash1(key);

        if (hashTable[index] != -1) {
            int index2 = hash2(key);
            int i = 1;
            while (1) {
                int newIndex = (index + i * index2) % TABLE_SIZE;

                if (hashTable[newIndex] == -1) {
                    hashTable[newIndex] = key;
                    break;
                }
                i++;
            }
        }

        else
            hashTable[index] = key;
        curr_size++;
    }
    //search function for table
    void search(Obj key)
    {
        int index1 = hash1(key);
        int index2 = hash2(key);
        int i = 0;
        while (hashTable[(index1 + i * index2) % TABLE_SIZE] != key) {
            if (hashTable[(index1 + i * index2) % TABLE_SIZE] == -1) {
                cout << key << " does not exist" << endl;
                return;
            }
            i++;
        }
        cout << key << " found" << endl;
    }

    void displayHash()
    {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (hashTable[i] != -1)
                cout << i << " --> "
                << hashTable[i] << endl;
            else
                cout << i << endl;
        }
    }
};

//int main()
//{
//
//    DoubleHash<int>* h;  
//    for (int i = 0; i < 20; i++) {
//        h->insertHash(i);
//    }
//    h->search(36); 
//    h->search(100);   
//    return 0;
//}