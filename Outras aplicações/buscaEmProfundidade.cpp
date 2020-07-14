#include<bits/stdc++.h> 
using namespace std; 
  
// Graph class represents a directed graph 
// using adjacency list representation 
class Graph 
{ 
    int V;    // No. of vertices 
  
    // Pointer to an array containing 
    // adjacency lists 
    list<int> *adj; 
  
    // A recursive function used by DFS 
    void DFSUtil(int v, bool visited[]); 
public: 
    Graph(int V);   // Constructor 
  
    // function to add an edge to graph 
    void addEdge(int v, int w); 
  
    // DFS traversal of the vertices 
    // reachable from v 
    void DFS(int v); 
}; 
  
Graph::Graph(int V) 
{ 
    this->V = V; 
    adj = new list<int>[V]; 
} 
  
void Graph::addEdge(int v, int w) 
{ 
    adj[v].push_front(w); // Add w to v?s list. 
} 
  
void Graph::DFSUtil(int v, bool visited[]) 
{ 
    // Mark the current node as visited and 
    // print it 
    visited[v] = true; 
     
  
    // Recur for all the vertices adjacent 
    // to this vertex 
    list<int>::iterator i; 
    for (i = adj[v].begin(); i != adj[v].end(); ++i) 
        if (!visited[*i]) 
            DFSUtil(*i, visited); 
        cout << v << endl;
} 
  
// DFS traversal of the vertices reachable from v. 
// It uses recursive DFSUtil() 
void Graph::DFS(int v) 
{ 
    // Mark all the vertices as not visited 
    bool *visited = new bool[V]; 
    for (int i = 0; i < V; i++) 
        visited[i] = false; 
  
    // Call the recursive helper function 
    // to print DFS traversal 
    DFSUtil(v, visited); 
} 
  
int main(){

    int v, ori, x, y;
    cin >> v;
    cin >> ori;
    Graph g(v);

    while(!(cin >> x >> y).eof()){
        g.addEdge(x, y);
    }
    g.DFS(ori);

    return 0;
}


// https://www.thehuxley.com/problem/2380?locale=pt_BR

// Input:
// Os dados de entrada do problema serão dados da seguinte maneira:

//     A primeira linha está a quantidade de vértices do grafo (inteiro).
//     A segunda linha está o vértice de origem da busca (inteiro).
//     As demais linhas representam as arestas do grafo. Considere que em cada linha, tem-se dois vértices para identificar cada aresta do grafo. 

// Por exemplo:


// 6

// 0

// 0 1

// 0 4

// 1 0

// 1 2

// 1 4

// 2 1

// 2 3

// 3 2

// 3 4

// 3 5

// 4 0

// 4 1

// 4 3

// 5 3

// Output:
// Ao final o seu programa deve apresentar a saída no seguinte formato:

//     A saída deve mostrar a sequência em que os vértices foram visitados. Cada vértice deve ser apresentado em uma linha diferente.


// Por exemplo:

// 5

// 1

// 2

// 3

// 4

// 0