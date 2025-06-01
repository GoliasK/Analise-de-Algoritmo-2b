#include <iostream>
#include <climits>
#include <vector>
using namespace std;

#define SIZE 7
#define INF INT_MAX


string names[SIZE] = {"x", "v", "z", "r", "s", "t", "u"};

int minimumDistance(int distance[], bool visited[]) {
    int min = INF, min_index;
    for (int i = 0; i < SIZE; i++) {
        if (!visited[i] && distance[i] <= min) {
            min = distance[i];
            min_index = i;
        }
    }
    return min_index;
}

void printPath(int parent[], int j) {
    if (parent[j] == -1)
        return;
    printPath(parent, parent[j]);
    cout << " -> " << names[j];
}

void dijkstra(int graph[SIZE][SIZE], int src, int dest) {
    int distance[SIZE];
    bool visited[SIZE];
    int parent[SIZE];

    for (int i = 0; i < SIZE; i++) {
        distance[i] = INF;
        visited[i] = false;
        parent[i] = -1;
    }

    distance[src] = 0;

    for (int count = 0; count < SIZE - 1; count++) {
        int u = minimumDistance(distance, visited);
        visited[u] = true;

        for (int v = 0; v < SIZE; v++) {
            if (!visited[v] && graph[u][v] && distance[u] + graph[u][v] < distance[v]) {
                parent[v] = u;
                distance[v] = distance[u] + graph[u][v];
            }
        }
    }

    cout << "Menor custo de " << names[src] << " até " << names[dest] << ": " << distance[dest] << endl;
    cout << "Caminho: " << names[src];
    printPath(parent, dest);
    cout << endl;
}

int main() {
    int graph[SIZE][SIZE] = {
        // x   v   z   r   s   t   u
        { 0, 30, 12,  0,  0,  0,  0 },  // x
        {30,  0, 35,  17,  0,  0, 15 },  // v
        {12, 35,  0, 25,  20,  0,  0 },  // z
        { 0,  17, 25,  0,  7, 0,  15 },  // r
        { 0,  0,  20,  7,  0,  12,  10 },  // s
        { 0,  0,  0, 0,  12,  0,  5 },  // t
        { 0, 15,  0,  15,  10,  5,  0 }   // u
    };

    dijkstra(graph, 0, 5); 
    return 0;
}