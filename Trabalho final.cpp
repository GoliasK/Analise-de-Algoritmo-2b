/*
Trabalho II - Análise de Algoritmos
Aluno(s): Ronaldo Pereira Avansini - 2165578
          MarcoS Paulo
          Diego
*/

// ======================================================
// Exercícios 1 e 2: Lista de Adjacência + Busca em Largura
// ======================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <map>
#include <climits>

using namespace std;

class Grafo {
private:
    unordered_map<string, vector<string>> adj;

public:
    void carregarDeArquivo(const string& nomeArquivo) {
        adj.clear(); // Garante que não mistura grafos
        ifstream arquivo(nomeArquivo);
        if (!arquivo.is_open()) {
            cerr << "Erro ao abrir o arquivo: " << nomeArquivo << endl;
            exit(1);
        }

        string linha;
        while (getline(arquivo, linha)) {
            stringstream ss(linha);
            string u, v;
            if (getline(ss, u, ';') && getline(ss, v, ';')) {
                u.erase(remove(u.begin(), u.end(), '\r'), u.end());
                v.erase(remove(v.begin(), v.end(), '\r'), v.end());

                adj[u].push_back(v);
                adj[v].push_back(u);
            }
        }

        arquivo.close();

        for (auto& par : adj) {
            sort(par.second.begin(), par.second.end());
        }
    }

    void buscaEmLargura(const string& inicio) {
        set<string> visitados;
        queue<string> fila;

        fila.push(inicio);
        visitados.insert(inicio);

        cout << "Ordem de visitação (BFS a partir de " << inicio << "): ";

        while (!fila.empty()) {
            string atual = fila.front();
            fila.pop();
            cout << atual << " ";

            for (const string& vizinho : adj[atual]) {
                if (visitados.find(vizinho) == visitados.end()) {
                    visitados.insert(vizinho);
                    fila.push(vizinho);
                }
            }
        }

        cout << endl;
    }
};

// ======================================================
// Exercício 3: Busca em Profundidade (DFS)
// ======================================================

map<char, vector<char>> adjDFS;
set<char> visited;
vector<char> visitOrder;

void dfs(char u) {
    visited.insert(u);
    visitOrder.push_back(u);
    sort(adjDFS[u].begin(), adjDFS[u].end());

    for (char v : adjDFS[u]) {
        if (visited.find(v) == visited.end()) {
            dfs(v);
        }
    }
}

// ======================================================
// Exercício 4: Dijkstra com matriz de adjacência
// ======================================================

#define SIZE 7
#define INF INT_MAX

string names[SIZE] = {"x", "v", "z", "r", "s", "t", "u"};

int minimumDistance(int distance[], bool visited[]) {
    int min = INF, min_index = -1;
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

// ======================================================
// Função Principal
// ======================================================

int main() {
    // Exercícios 1 e 2
    Grafo g;
    g.carregarDeArquivo("g1.txt");
    g.buscaEmLargura("b");
    g.carregarDeArquivo("g2.txt");
    g.buscaEmLargura("b");
    g.carregarDeArquivo("g3.txt");
    g.buscaEmLargura("b");

    cout << "\n==============================" << endl;

    // Exercício 3
    ifstream fin("g2.txt");
    if (!fin) {
        cerr << "Erro ao abrir arquivo g2.txt" << endl;
        return 1;
    }

    string linha;
    while (getline(fin, linha)) {
        stringstream ss(linha);
        char u, v, pontoEVirgula;
        ss >> u >> pontoEVirgula >> v;
        adjDFS[u].push_back(v);
        adjDFS[v].push_back(u);
    }
    fin.close();

    dfs('a');
    cout << "Ordem de visitação DFS a partir do vértice 'a': ";
    for (char c : visitOrder) {
        cout << c << " ";
    }
    cout << endl;

    cout << "\n==============================" << endl;

    // Exercício 4
    int graph[SIZE][SIZE] = {
        // x   v   z   r   s   t   u
        { 0, 30, 12,  0,  0,  0,  0 },  // x
        {30,  0, 35, 17,  0,  0, 15 },  // v
        {12, 35,  0, 25, 20,  0,  0 },  // z
        { 0, 17, 25,  0,  7,  0, 15 },  // r
        { 0,  0, 20,  7,  0, 12, 10 },  // s
        { 0,  0,  0,  0, 12,  0,  5 },  // t
        { 0, 15,  0, 15, 10,  5,  0 }   // u
    };

    dijkstra(graph, 0, 5); // x até t

    return 0;
}
