// https://www.thehuxley.com/problem/3110?locale=pt_BR

// Input:
// Primeiramente irão vir dois inteiros V e A (1 <= V,A <= 100) , indicando o número de vértices e de arestas do grafo.
// Nas próximas A linhas virão 3 inteiros S,D,C  (1 <= S,D,C <= 100), indicando os dois vértices que compõem aquela aresta e o custo para passar por ela.


// Output:
// Primeiramente deverá ser impresso primeiramente o par de vértices Ri e Rj cujo ambos possuam a cor vermelha e a distância entre eles seja a maior possível, sempre respeitando a observação 3 da descrição.
// Em seguida deverá ser impresso primeiramente o par de vértices Bi e Bj cujo ambos possuam a cor azul e a distância entre eles seja a maior possível, sempre respeitando a observação 3 da descrição.


#include <bits/stdc++.h> 
using namespace std;   
#define INF 99999
#define red true
#define blue false

struct par{int a; int b;};

void printSolution(int **dist, int V); //so para ver o resultado
int **aloca(int v); //alocacao dinamica
void cores(bool *color, int s, int d); //registrar cores

void printSol(int **graph, int v, bool *color){
    int maiorAzul=0, maiorVer=0;
    struct par azul, ver;
    for(int i=0; i<v; i++){
        for(int j=0; j<v; j++){
            if(color[i]==color[j] && i!=j){
                if(color[i]){
                    if(graph[i][j]>maiorVer){
                        maiorVer = graph[i][j];
                        ver.a = i+1; ver.b = j+1;
                    }
                }
                else{
                    if(graph[i][j]>maiorAzul){
                        maiorAzul = graph[i][j];
                        azul.a = i+1; azul.b = j+1;
                    }
                }
            }
        }
    }
    cout << ver.a << " " << ver.b << endl;
    cout << azul.a << " " << azul.b << endl;
}

void floydWarshall (int **graph, int V, bool *color){
    int i, j, k;
    int **dist;
    dist = aloca(V);
    
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    for (k = 0; k < V; k++){
        for (i = 0; i < V; i++){
            for (j = 0; j < V; j++){          
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    printSol(dist, V, color); 
}

    
int main(){

    int **graph;
    bool *color;
    int i, v, a, s, d, c;

    cin >> v >> a;
    graph = aloca(v);
    color = new bool[v];
    for(i=0; i<v; i++) color[i]=red;

    for(i=0; i<a; i++){
        cin >> s >> d >> c;
        graph[s-1][d-1] = c;
        graph[d-1][s-1] = c;
        cores(color, s, d);
    }
    floydWarshall(graph, v, color);

    delete[] graph;
    delete[] color;

    return 0;  
}

int **aloca(int v){
    int **ptr;
    ptr = new int*[v];
    for(int i=0; i<v; i++){
        ptr[i] = new int[v];
        for(int j=0; j<v; j++){
            if(i==j)
                ptr[i][j] = 0;
            else
                ptr[i][j] = INF;
        }
    }
    return ptr;
}

void cores(bool *color, int s, int d){
    if(d%2)
        color[s-1] = !color[s-1];
    if(s%2)
        color[d-1] = !color[d-1];
}

void printSolution(int **dist, int V){
    cout<<"The following matrix shows the shortest distances between every pair of vertices" << endl;
    for (int i = 0; i < V; i++){
        for (int j = 0; j < V; j++){
            if (dist[i][j] == INF)
                cout<<"INF"<<"     ";
            else
                cout<<dist[i][j]<<"     ";
        }
        cout<<endl;
    }
}