#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
template<typename Obj>
//make a node for the hash table to use
class HashNode
{
public:
    Obj key;
    HashNode(Obj key)
    {
        this->key = key;
    }
};
template<typename Obj>
class LinearHashTable
{
    HashNode<Obj>** arr;
    int capacity;
    int size;
    HashNode<Obj>* dummy;

public:
    //constructor
    LinearHashTable(int amount)
    {
        capacity = amount;
        size = 0;
        arr = new HashNode<Obj>*[capacity];
        for (int i = 0; i < capacity; i++)
            arr[i] = NULL;
        dummy = new HashNode<Obj>(-1);
    }
    //hash function
    int hashFunction(int key)
    {
        return key % capacity;
    }
    //insert function
    void insert(Obj key)
    {
        HashNode<Obj>* temp = new HashNode<Obj>(key);
        int hashIndex = hashFunction(key);
        while (arr[hashIndex] != NULL && arr[hashIndex]->key != key
            && arr[hashIndex]->key != -1)
        {
            hashIndex++;
            hashIndex %= capacity;
        }
        if (arr[hashIndex] == NULL || arr[hashIndex]->key == -1)
            size++;
        arr[hashIndex] = temp;
    }
    //search function
    Obj search(int key)
    {
        int hashIndex = hashFunction(key);
        int counter = 0;
        while (arr[hashIndex] != NULL)
        {
            int counter = 0;
            if (counter++ > capacity)  
                return NULL;
            if (arr[hashIndex]->key == key)
                return arr[hashIndex]->key;
            hashIndex++;
            hashIndex %= capacity;
        }
        return NULL;
    }
    //return the size
    int sizeofMap()
    {
        return size;
    }
    //check if the table is empty
    bool isEmpty()
    {
        return size == 0;
    }

};

//int main()
//{
    ////chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    ////LinearHashTable<int>* h = new LinearHashTable<int>(20000);
    ////for (int i = 0; i < 10000; i++) {
    ////    h->insert(i);
    ////}
    ////chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    ////chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

    ////std::cout << "It took me " << time_span.count() << " seconds.";
    ////std::cout << std::endl;

    ////return 0;
//}