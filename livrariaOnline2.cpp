// https://iudex.io/problem/5ced5e6eea17180001c6ac4a/statement

// Dando prosseguimento à modernização de suas operações, a livraria online precisa agora otimizar o seu processo de entrega de encomendas.

// A livraria expandiu as suas operações para V localidades, numeradas de 0 a V-1, em cada uma das quais possui um armazém. A livraria comercializa B títulos, numerados de 0 a B-1, sendo que os armazéns possuem estoques limitados de cada título, podendo inclusive não ter alguns títulos em estoque. Os clientes podem fazer pedidos de qualquer uma das V localidades. Cada pedido é composto de um ou mais títulos, cada um com uma respectiva quantidade. Um pedido pode ser enviado por um armazém apenas se puder ser atendido integralmente, ou seja, todos os títulos do pedido devem estar em estoque no armazém, em quantidade igual ou superior à encomendada.

// Para determinar de qual armazém uma encomenda deve ser despachada, além da disponibilidade em estoque dos itens solicitados, o sistema deve escolher o armazém que resulta no menor custo de envio. As entregas são efetuadas por caminhões que trafegam pelas estradas que interligam as diferentes localidades. O primeiro fator a ser levado em conta é a distância percorrida nas estradas da origem ao destino da encomenda. Entretanto, além da distância, o sistema de logística leva em conta outros fatores como condições climatéricas, tráfego, tarifas de pedágio, etc. Assim, além da distância D[X][Y] cada trecho de estrada entre duas localidades consecutivas X e Y possui um coeficiente W[X][Y] entre 0 e 100, sendo o custo do trecho X-Y calculado como

// C[X][Y] =  ( D[X][Y] * ( 100 + W[X][Y] ) ) / 100.

// As condições das estradas são monitoradas e os coeficientes W[I][J] podem sofrer ajustes a qualquer tempo.
// Nota:

// Os custos , distâncias e coeficientes devem ser armazenados em inteiros de 32 bits.


// Input:
// A entrada inicia com uma linha com dois inteiros

// V E B

// onde V indica a quantidade de localidades e E o número de estradas que interligam essas localidades e B a quantidade de livros comercializados pela livraria.

// Seguem-se E linhas, cada uma representando um trecho de estrada na forma

// X Y D[X][Y] W[X][Y]

// onde

//     X Y indicam duas localidades ligadas por uma estrada
//     D[X][Y] indica a distância (comprimento) da estrada de X a Y
//     W[X][Y] indica o coeficiente de ajuste de custo da estrada de X a Y, conforme explicado acima. Cada estrada é de sentido duplo e só será especificada uma vez.

// Em seguida temos V linhas especificando o estoque inicial de cada armazém

// Q[0][0] Q[0][1] ... Q[0][B-1]
// Q[1][0] Q[1][1] ... Q[1][B-1]
// ...
// Q[V-1][0] Q[V-1][1] ... Q[V-1][B-1]

// sendo Q[X][I]>=0 o estoque inicial do título I no armazém X.

// Seguem-se várias linhas, cada uma contendo uma operação numa das formas a seguir

// ORD T M I[0] Q[0] I[1] Q[1] ... I[M-1] Q[M-1]

// indica um pedido efetuado para ser entregue na localidade T, constituído de M itens I[0]..I[M-1], com suas respectivas quantidades Q[0]..Q[M-1].

// UPD X Y W

// indica a atualização do coeficiente da estrada que liga as localidades X e Y para W

// STK X I Q

// indica uma reposição de estoque de Q exemplares do título I no armazém da localidade X.

// A entrada termina com uma linha

// END


// Output:
// Para cada linha ORD T ... o programa deve imprimir uma linha

// S=X[0] X[1] ... X[R-1]=T C[S][T]

// onde X[0]..X[R-1] corresponde ao caminho de menor custo percorrido pela entrega da localidade do armazém de origem S=X[0] ao destino X[R-1]=T. C[S][T] indica o custo total do trajeto. Caso o pedido não possa ser atendido por nenhum armazém, deve ser impressa uma linha

// OOS


// OBS: RUNTIME ERROR AT CASES 5 and 6.


#include <iostream>
#include <string>
#include <list>
#include <bits/stdc++.h>

using namespace std;

typedef struct no{
    int weight;
    int node;
}no;

typedef struct pointer{
    int *d;
    int *f;
}pointer;

typedef struct mh{
    int d;
    int u;
}mh;

typedef struct storage{
    int item;
    int qor;
}storage;

bool ordem(mh *heap, int x, int y){
    bool result;
    if(heap[x].d < heap[y].d)
        result = true;
        else 
            if(heap[x].d == heap[y].d){
                if(heap[x].u < heap[y].u)
                    result = true;
            }    
            else 
                result = false;
    return result;
}

mh *bubbleUp(mh *heap, int i){
    int p = (i-1)/2;
    mh aux;
    while(i>0 && ordem(heap, i, p)){
        aux = heap[i];
        heap[i] = heap[p];
        heap[p] = aux;
        i = p;
        p = (i-1)/2;
    }
    return heap;
}

void heapify(mh *heap, int i, int heapsize){
    int l = (2*i) + 1;
    int r = (2*i) + 2;
    int m = i;
    mh aux;
    if(l<heapsize && ordem(heap, l, m))
        m = l;
    if(r<heapsize && ordem(heap, r, m))
        m = r;
    if(m != i){
        aux = heap[i];
        heap[i] = heap[m];
        heap[m] = aux;
        heapify(heap, m, heapsize);
    }
}

mh *doubleArray(mh *heap, int arraySize){
    mh *aux = new mh[2*arraySize];
    for(int i=0; i<arraySize; i++){
        aux[i] = heap[i];
    }
    return aux;
}

mh *minHeapInsert(mh *heap, mh v, int &heapsize, int &arraySize){
    int i = heapsize;
    if(heapsize == arraySize){
        heap = doubleArray(heap, arraySize);
        arraySize *= 2;
    }
    heap[i] = v;
    heapsize += 1;
    heap = bubbleUp(heap, i);
    return heap;
}

mh minHeapExtract(mh *heap, int &heapsize){
    mh aux;
    mh r = heap[0];
    aux = heap[0];
    heap[0] = heap[heapsize-1];
    heap[heapsize-1] = aux;
    heapsize -= 1;
    heapify(heap, 0, heapsize);
    return r;
}

pointer dijkstra(list<no> *g, int s, int v){
    int i, u, heapsize=0;
    int *d = new int[v];
    int *f = new int[v];
    int arraySize = v;
    list<no> :: iterator e;
    mh aux, aux2;
    pointer gen;
    mh *heap = new mh[arraySize];
    for(i=0; i<v; i++){
        d[i] = 0x3f3f3f;
        f[i] = -1;
    }
    d[s] = 0;
    f[s] = s;   
    aux.d = 0;
    aux.u = s;
    heap = minHeapInsert(heap, aux, heapsize, arraySize);
    for(i=0; i<v; i++)
    {
        aux = minHeapExtract(heap, heapsize);
        u = aux.u;
        e = g[u].begin();
        while(e != g[u].end()){
            if(d[e->node] > d[aux.u] + e->weight){
                d[e->node] = d[aux.u] + e->weight;
                f[e->node] = aux.u;
                aux2.d = d[e->node];
                aux2.u = e->node;
                heap = minHeapInsert(heap, aux2, heapsize, arraySize);
            }
            ++e;
        }
    }
    gen.d = d;
    gen.f = f;
    return gen;
}

bool checkOrder(int *q, storage *order, int x, int m){
    int i;
    bool result=true;
    for(i=0; i<m && result==true; i++){
        if(q[order[i].item] < order[i].qor)
            result = false;
    }
    if(result == true){
        for(i=0; i<m; i++){
            q[order[i].item] -= order[i].qor;
        }
    }
    return result;
}

int main(){

    int i, j, k, l=1, v, e, b, x, y, t, m, cond=0, stop=0;
    string op;
    no aux;
    pointer shortPath;

    cin >> v >> e >> b;

    list<no> *c = new list<no>[v];
    list<no> :: iterator cur;
    storage *order = new storage[b];
    int **d = new int*[v];
    int **w = new int*[v];
    int **q = new int*[v];
    int *sp = new int[v];
    
    for(i=0; i<v; i++){
        d[i] = new int[v];
        w[i] = new int[v];
        q[i] = new int[b];
    }

    for(i=0; i<e; i++){
        cin >> x >> y;
        cin >> d[x][y] >> w[x][y];
        d[y][x] = d[x][y];
        w[y][x] = w[x][y];
        aux.node = y;
        aux.weight = (d[x][y] * (100 + w[x][y]))/100;
        c[x].push_back(aux);
        aux.node = x;
        c[y].push_back(aux);
    }

    for(i=0; i<v; i++){
        for(j=0; j<b; j++){
            cin >> q[i][j];
        }
    }

    do{
        cond = 0;
        cin >> op;
        if(op == "END")
            stop=1;
            else if(op == "ORD"){
                cin >> t >> m;
                for(i=0; i<m; i++){
                    cin >> order[i].item >> order[i].qor;
                }
                shortPath = dijkstra(c, t, v);
                for(i=0; i<v; i++){
                    sp[i] = shortPath.d[i];
                }
                sort(sp, sp+v);
        
                for(i=0; i<v && cond==0; i++){
                    k=0;
                    for(j=0; k<l; j++){
                        if(sp[i] == shortPath.d[j]){
                            k++;
                            if(k==l)
                                j--;
                        }
                    }
                    if(i+1 != v){
                        if(sp[i] == sp[i+1])
                            l++;
                        else 
                            l=1;
                    }
                    if(checkOrder(q[j], order, j, m)){
                        cond = 1;
                        cout << j << " ";
                        while(j != t){
                            j = shortPath.f[j];
                            cout << j << " ";
                        }
                        cout << sp[i] << endl;
                        l=1;
                    }
                    else
                        if(i+1 == v)
                            cout << "OOS" << endl;
                }



            }
            else if(op == "UPD"){
                cin >> x >> y >> t;
                w[x][y] = t;
                w[y][x] = t;
                for(cur = c[x].begin(); cur->node!=y; ++cur){}
                cur->weight = (d[x][y] * (100 + w[x][y]))/100;

                for(cur = c[y].begin(); cur->node!=x; ++cur){}
                cur->weight = (d[y][x] * (100 + w[y][x]))/100;
            }
            else if(op == "STK"){
                cin >> x >> y >> t;
                q[x][y] += t;
            }
    }while(stop==0);

    return 0;
}