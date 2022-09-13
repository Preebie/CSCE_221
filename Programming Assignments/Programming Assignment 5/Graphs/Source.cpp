#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
//class
class Graph {
//the private stuff to have somewhere to store values
private:
    int countVertex;
    int adjMatrix[100][100];

public:
    //constructor
    Graph(int vertex, int edge)
    {
        countVertex = vertex;
        //set values in array
        for (int i = 0; i < countVertex; ++i) {
            for (int j = 0; j < countVertex; ++j) {
                adjMatrix[i][j] = 0;
            }
        }
    }
    
    //add an edge to the graph
    void addEdge(int v, int w)
    {
        //make sure the vertex can be added in the first place
        if ((v >= countVertex) || (w > countVertex)) {
            cout << "This is not a vertex";
            return;
        }
        //make sure it's not already there
        if (v == w) {
            return;
        }
        //add edges and vertices
        else {
            adjMatrix[w][v] = 1;
            adjMatrix[v][w] = 1;
        }
    }
    void checkEdge(int v, int w)
    {
        //just check if it's there
        if ((v >= countVertex) || (w > countVertex)) {
            cout << "This is not a vertex";
        }
        else {
            cout << "This is a vertex";
        }

    }
    //add vertex in a similar fashion
    void addVertex()
    {
        //increment the vertex
        countVertex++;
        //actually add the vertex
        for (int i = 0; i < countVertex; ++i) {
            adjMatrix[i][countVertex - 1] = 0;
            adjMatrix[countVertex - 1][i] = 0;
        }
    }
    void removeVertex(int v)
    {
        //check if the vertex is there
        if (v > countVertex) {
            cout << "\nVertex not present!";
            return;
        }
        //remove it if it is
        else {

            while (v < countVertex) {
                for (int i = 0; i < countVertex; ++i) {
                    adjMatrix[i][v] = adjMatrix[i][v + 1];
                }

                for (int i = 0; i < countVertex; ++i) {
                    adjMatrix[v][i] = adjMatrix[v + 1][i];
                }
                v++;
            }
            //don't forget to delete a vertex. seriously, it wastes like three hours if you do because your bfs collapses
            countVertex--;
        }
    }
    //remove the edges now
    void removeEdge(int v, int w)
    {
        //make sure it's there first off
        if ((v < 0) || (v >= countVertex)) {
            cout << "This is not a vertex";
        }
        if ((w < 0) || (w >= countVertex)) {
            cout << "This is not a vertex";
        }

        if (v == w) {
            cout << "Vertex already in graph";
        }
        //now remove it
        else {
            adjMatrix[w][v] = 0;
            adjMatrix[v][w] = 0;
        }
    }
    //dfs algorithm
    void DFS(int initialValue, vector<bool>& visited)
    {
        visited[initialValue] = true;

        for (int i = 0; i < countVertex; i++) {

            if (adjMatrix[initialValue][i] == 1 && (!visited[i])) {
                DFS(i, visited);
            }
        }
    }
    //bfs algorithm
    void BFS(int initialValue)
    {
        vector<int> checker;
        vector<bool> visited(countVertex, false);

        checker.push_back(initialValue);

        visited[initialValue] = true;

        int visitIndex;
        while (checker.empty() != true) {
            visitIndex = checker[0];

            checker.erase(checker.begin());

            for (int i = 0; i < countVertex; i++) {
                if (adjMatrix[visitIndex][i] == 1 && (!visited[i])) {

                    checker.push_back(i);

                    visited[i] = true;
                }
            }
        }
    }
};
//int main()
//{
//    srand(0);
//    Graph G(100, 100);
//
//    for (int n = 0; n < 100; n++) {
//        for (int k = 0; k < 100; k++) 
//            G.addEdge(n, k);
//    }
//    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
//    G.BFS(0);
//    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
//	chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
//
//	cout << "It took me " << time_span.count() << " seconds.";
//	cout << endl;
//
//}