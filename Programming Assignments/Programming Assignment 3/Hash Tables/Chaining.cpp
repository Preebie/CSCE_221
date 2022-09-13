#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <chrono>
using namespace std;
//global variable to count characters
static int char_number = 0;

template <typename Obj>
class HashTable
{
    int List;    

    vector<Obj>* table;
public:
    //hash function
    int hashFunction(int x) {
        return (x % List);
    }
    //constructor
    HashTable(Obj b)
    {
        this->List = b;
        table = new vector<Obj>[List];
    }
    //insert function
    void insert(Obj key)
    {
        int index = hashFunction(key);
        table[index].push_back(key);
    }
    //seach function for hashtable
    Obj search(int key) {

        int hashIndex = hashFunction(key);

        while (HashTable[hashIndex] != NULL) {

            if (HashTable[hashIndex]->key == key)
                return HashTable[hashIndex];

            ++hashIndex;

            hashIndex %= List;
        }

        return NULL;
    }
};

//increment a number in the vector
void incrementer(char x, vector<double> &vect) {
    int m = (int)(x)-97;
    if ((int)(x) == 46) {
        m = 26;
    }
    vect[m]++;
}
//check if a character occurs in the text
void occurs(string str, char x, vector<double>& vect) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == x) {
            char_number++;
            incrementer(x, vect);
        }
    }
}
//function to create a random character
char getRandomChar(vector<double>& vect, int w = 64) {
    //checker variable
    double checker = 0;
    //random number generator
    double number = (rand() % w);
    number /= ((rand() % w) + 1);
    //index for where we're searching
    int index = 0;
    //while loop to randomly choose an index
    while (checker < number) {

        checker = checker + vect[index];

        index++;
        if (index == 27) {
            index = 0;
        }
    }
    //character to return, solve for a period
    char character = (char)(floor(index) + 97);

    if (character == '{') {
        character = '.';
    }

    return character;
}



int main()
{
    //srand(time(0));
    //chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    //string filename = "merchant.txt";
    //vector<double> CharDistribution(27);
    //ifstream ifs(filename);
    //
    //string str = "";
    //string line;
    //while (!ifs.eof()) {
    //    ifs >> line;
    //    str += line;
    //}
    //for (int i = 0; i < 26; i++) {
    //    occurs(str, (char)(i + 97), CharDistribution);
    //}
    //occurs(str, '.', CharDistribution);

    //for (int i = 0; i < 27; i++) {
    //    CharDistribution[i] /= char_number;
    //}
    //string k(str.length(), ' ');
    //for (int i = 0; i < str.length(); i++) {
    //    k[i] = getRandomChar(CharDistribution);
    //}
    //cout << k;
    //chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    //chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

    //std::cout << "It took me " << time_span.count() << " seconds.";
    //std::cout << std::endl;
    //return 0;


}