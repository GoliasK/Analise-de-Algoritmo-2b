//Exercicio 3 

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

// Lista de adjacência: vértice -> lista de vértices adjacentes
map<char, vector<char>> adj;

// Conjunto para marcar visitados
set<char> visited;

// Vetor para armazenar ordem de visitação
vector<char> visitOrder;

// DFS recursiva
void dfs(char u) {
    visited.insert(u);
    visitOrder.push_back(u);
    
    // Ordenar os adjacentes para garantir ordem lexicográfica
    sort(adj[u].begin(), adj[u].end());
    
    for (char v : adj[u]) {
        if (visited.find(v) == visited.end()) {
            dfs(v);
        }
    }
}

int main() {
    ifstream fin("g2.txt");
    if (!fin) {
        cerr << "Erro ao abrir arquivo g2.txt" << endl;
        return 1;
    }
    
    // Ler as arestas e montar lista de adjacência
    char u, v;
    while (fin >> u >> v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Assumindo grafo não direcionado
    }
    fin.close();
    
    // Executar DFS a partir do vértice 'a'
    dfs('a');
    
    // Exibir ordem de visitação
    cout << "Ordem de visitação DFS a partir do vértice 'a': ";
    for (char c : visitOrder) {
        cout << c << " ";
    }
    cout << endl;
    
    return 0;
}
