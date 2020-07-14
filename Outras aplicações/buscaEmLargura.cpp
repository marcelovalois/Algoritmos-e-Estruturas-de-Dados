#include<iostream> 
#include <list> 
  
using namespace std; 
  
// This class represents a directed graph using 
// adjacency list representation 
class Graph 
{ 
    int V;    // No. of vertices 
  
    // Pointer to an array containing adjacency 
    // lists 
    list<int> *adj;    
public: 
    Graph(int V);  // Constructor 
  
    // function to add an edge to graph 
    void addEdge(int v, int w);  
  
    // prints BFS traversal from a given source s 
    void BFS(int s);   
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
  
void Graph::BFS(int s) 
{ 
    // Mark all the vertices as not visited 
    bool *visited = new bool[V]; 
    for(int i = 0; i < V; i++) 
        visited[i] = false; 
  
    // Create a queue for BFS 
    list<int> queue; 
  
    // Mark the current node as visited and enqueue it 
    visited[s] = true; 
    queue.push_back(s); 
  
    // 'i' will be used to get all adjacent 
    // vertices of a vertex 
    list<int>::iterator i; 
  
    while(!queue.empty()) 
    { 
        // Dequeue a vertex from queue and print it 
        s = queue.front(); 
        cout << s << endl; 
        queue.pop_front(); 
  
        // Get all adjacent vertices of the dequeued 
        // vertex s. If a adjacent has not been visited,  
        // then mark it visited and enqueue it 
        for (i = adj[s].begin(); i != adj[s].end(); ++i) 
        { 
            if (!visited[*i]) 
            { 
                visited[*i] = true; 
                queue.push_back(*i); 
            } 
        } 
    } 
} 
  
// Driver program to test methods of graph class 
int main(){ 
    int v, ori, x, y;
    cin >> v;
    cin >> ori;
    Graph g(v);

    while(!(cin >> x >> y).eof()){
        g.addEdge(x, y);
    }
    g.BFS(ori);
  
    return 0; 
} 


// https://www.thehuxley.com/problem/2379?locale=pt_BR

// Input:
//     A primeira linha está a quantidade de vértices do grafo de entrada (inteiro).
//     A segunda linha está o vértice de origem da busca (inteiro).
//     As demais linhas representam as arestas do grafo. Em cada linha, tem-se dois vértices para identificar cada aresta do grafo. 

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
//     A saída deve mostrar a sequência em que os vértices foram visitados.


// Por exemplo:


// 0

// 4

// 1

// 3

// 2

// 5