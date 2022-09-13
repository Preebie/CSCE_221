#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

template <typename Obj>

struct Heap
{
    vector<Obj> A;

    int find_parent(int i) {
        return (i - 1) / 2;
    }

    // return left child of `A[i]`
    int find_left(int i) {
        return (2 * i + 1);
    }

    int find_right(int i) {
        return (2 * i + 2);
    }
    void remove_finder(int i)
    {
        int left = find_left(i);
        int right = find_right(i);

        int smallest = i;

        if (left < size() && A[left] < A[i]) {
            smallest = left;
        }

        if (right < size() && A[right] < A[smallest]) {
            smallest = right;
        }

        if (smallest != i)
        {
            swap(A[i], A[smallest]);
            remove_finder(smallest);
        }
    }

    void heap_sort(int i)
    {
        if (i && A[find_parent(i)] > A[i])
        {
            swap(A[i], A[find_parent(i)]);

            heap_sort(find_parent(i));
        }
    }

    unsigned int size() {
        return A.size();
    }

    bool empty() {
        return size() == 0;
    }

    void insert(Obj key)
    {
        A.push_back(key);

        int index = size() - 1;
        heap_sort(index);
    }

    void remove()
    {
            if (size() == 0)
            {
                return;
            }

            A[0] = A.back();
            A.pop_back();

            remove_finder(0);
    }

    int root()
    {
            if (size() == 0)
            {
                return NULL;
            }

            return A.at(0);        
    }
};

//int main()
//{
//    srand(0);
//    Heap<int> pq;
//    for (int n = 0; n < 10; n++) {
//        pq.insert(rand());
//    }
//    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
//    for (int n = 0; n < 10; n++) {
//        pq.heap_sort(n);
//    }
//
//	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
//	chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
//
//	cout << "It took me " << time_span.count() << " seconds.";
//	cout << endl;
//
//    return 0;
//}

