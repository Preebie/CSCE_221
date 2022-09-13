#include<iostream>
#include <vector>
#include <chrono>

using namespace std;

//next graph is the adjacency list one
class GraphList
{
    //declare the number of vertices again
    int countVertex;    

    //container for the values
    vector<int>* adjMatrix;
public:
    //add a vertex, just like last time
    void addVertex()
    {
        countVertex++;
        int i;

        for (i = 0; i < countVertex; ++i) {
            adjMatrix[i][countVertex - 1] = 0;
            adjMatrix[countVertex - 1][i] = 0;
        }
    }
    //same as before
    void removeVertex(int v)
    {
        if (v > countVertex) {
            cout << "\nVertex not present!";
            return;
        }
        else {
            int i;

            while (v < countVertex) {
                for (i = 0; i < countVertex; ++i) {
                    adjMatrix[i][v] = adjMatrix[i][v + 1];
                }

                for (i = 0; i < countVertex; ++i) {
                    adjMatrix[v][i] = adjMatrix[v + 1][i];
                }
                v++;
            }

            countVertex--;
        }
    }
    //again this is the same as before
    void removeEdge(int v, int w)
    {
        if ((v < 0) || (v >= countVertex)) {
            cout << "This is not a vertex";
        }
        if ((w < 0) || (w >= countVertex)) {
            cout << "This is not a vertex";
        }

        if (v == w) {
            cout << "Vertex already in graph";
        }

        else {
            adjMatrix[w][v] = 0;
            adjMatrix[v][w] = 0;
        }
    }
    //constructor
    GraphList(int countVertex)
    {
        this->countVertex = countVertex;
        adjMatrix = new vector<int>[countVertex];
    }

    void addEdge(int v, int w)
    {
        // Add w to v’s vector.
        adjMatrix[v].push_back(w); 
    }

    void BFS(int s)
    {
        //all the vertices start unchecked
        bool* checked = new bool[countVertex];
        for (int i = 0; i < countVertex; i++)
            checked[i] = false;

        //create a queue
        vector<int> queue;

        //the current node is now checked and it is in the queue
        checked[s] = true;
        queue.push_back(s);

        //the iterator will find what we need for the later for loop
        vector<int>::iterator i;
        
        while (!queue.empty())
        {
            //dequeue all vertices
            s = queue.front();
            queue.erase(queue.begin());

            for (i = adjMatrix[s].begin(); i != adjMatrix[s].end(); ++i)
            {
                if (!checked[*i])
                {
                    checked[*i] = true;
                    queue.push_back(*i);
                }
            }
        }
    }
    void DFS(int initialValue, vector<bool>& visited)
    {
        visited[initialValue] = true;

        for (int i = 0; i < countVertex; i++) {

            if (adjMatrix[initialValue][i] == 1 && (!visited[i])) {
                DFS(i, visited);
            }
        }
    }


};


int main()
{
    GraphList g(100);
    for(int n = 0; n < 100; n++)
        for(int k = 0; k < 100; k++)
            g.addEdge(n, k);
    
        chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
        g.BFS(0);
        chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    	chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    
    	cout << "It took me " << time_span.count() << " seconds.";
    	cout << endl;

    return 0;
}