// https://iudex.io/problem/5cd0b313ea17180001c6a94d/statement

// O serviço secreto de Algotham adotou um novo sistema de segurança para a comunicação entre os seus agentes. 
// A partir de agora cada agente possui um identificador numérico e um código gráfico (similar a um QR-code) na forma de uma 
// matriz bidimensional de NxN pixels, sendo cada pixel 0 (branco) ou 1 (preto). 
// Na realidade, esse código representa uma matriz de adjacências de um grafo (não-dirigido) de N vértices. 
// Os grafos são aleatórios, porém cada um deles possui exatamente um K-clique, ou seja, subconjunto de K vértices todos 
// interligados uns aos outros por um total K*(K-1)/2 arestas. Esse K-clique é um certificado do código e está disfarçado 
// em meio a várias outras arestas, não sendo trivial detectá-lo apenas olhando para o código.

// Dois agentes só poderão se comunicar entre si se seus códigos forem compatíveis. 
// Assim, antes de iniciar a comunicação, os agentes tentam estabelecer uma conexão através dos seus códigos que são 
// transmitidos por um canal exclusivo de satélite para a central de inteligência, onde são verificados. 
// O teste de compatibilidade é simples: dois códigos são compatíveis se, e somente se, eles possuem o mesmo certificado/K-clique.

// Input:
// A entrada inicia-se por uma linha com quatro inteiros

// A N K Q

// onde

//     A indica o número de agentes, ou seja, os IDs dos agentes variam de 0..A-1
//     N o número de vértices de cada grafo/código
//     K o tamanho do clique de cada grafo
//     Q indica a quantidade de tentativas de conexão a serem processadas.

// Em seguida temos Q tentativas de conexão entre agentes. A especificação de cada tentativa de conexão começa com uma linha

// X Y

// onde X e Y indicam os IDs dos agentes. Seguem-se as especificações dos códigos dos agentes X e Y, nessa ordem, sendo cada código normalmente representado por N-1 linhas

// E[1,0]
// E[2,0]E[2,1]
// E[3,0]E[3,1]E[3,2]
// ...
// E[N-1,0]  ...  E[N-1,N-2]

// onde

//     E[i][j]= valor do pixel da linha i coluna j. Esse valor será = 1, se existe uma aresta (i,j), ou 0 caso contrário.

// Ou seja, está representada apenas parte triangular inferior (abaixo da diagonal principal) da matriz de adjacências, sendo a matriz simétrica.
// Importante

//     Para economizar espaço, o código de um agente só será explicitamente colocado na entrada na primeira vez que ele for usado numa tentativa de conexão. Nas tentativas subsequentes, o mesmo código deve ser utilizado. Cada agente 0..A-1 aparecerá em pelo menos uma tentativa de conexão, porém normalmente em várias.

//     Encontrar o K-clique de um código é uma operação muito custosa e só deverá ser feita no máximo uma vez por agente. Caso contrário, a central demorará muito para responder e não haverá tempo para processar todas as tentativas de conexão. Entretanto, caso o certificado de um dos códigos seja conhecido, testar se outro código é compatível com ele é bem menos custoso. Mais simples ainda, se soubermos que um código X é compatível com um código Y, e que o código Y é compatível com Z, então saberemos que X é compatível com Z sem necessidade de conhecer seus códigos/certificados.


// Output:
// Para cada tentativa de conexão

// X Y

// deve ser impressa uma linha na forma

// FAIL

// se os certificados (K-cliques) C(X) e C(Y) dos códigos X e Y forem diferentes; OU

// SUCC C(X)

// se os certificados de X e Y forem idênticos. O certificado C(X) é impresso como a sequência dos vértices que formam o K-clique do código X em ordem crescente, separados por espaços.

#include <iostream>
#include <string>
using namespace std;

typedef struct ufind{
    int pai;
    int tam;
}ufind;

char ***buildMatrix(char ***code, int x, int n){
    int i, j;
    for(i=1; i<n; i++){
        for(j=0; j<i; j++){
            cin >> code[x][i][j];
        }
    }
    return code;
}

int **buildTeste(int **teste, int k, int n){
    int i=1, j, l, aux, stop, finish=0;
    for(j=0; j<k; j++)
        teste[0][j] = j;
    do{
        for(j=0; j<k; j++)
            teste[i][j] = teste[i-1][j];
        stop=0;
        aux=1;
        for(j = k-1; stop==0 && j>=0; j--){
            if(teste[i][j]+1 < n){
                teste[i][j] += 1;
                stop=1;
            }
            if(stop==1){
                for(l=1; l<aux; l++){
                    if(teste[i][j+l-1]+1 < n)
                        teste[i][j+l] = teste[i][j+l-1] + 1;
                    else{
                        stop=0;
                    }
                }
            }
            if(stop==0)
                aux++;
        }
        i++;

        if(aux==k+1)
            finish=1;

    }while(finish==0);

    return teste;
}

int *findClique(char **code, int *clique, int **teste, int k, int n){
    int i, j, found=0, aux, m, falso, stop, x=0;

    while(found==0){
        falso = 0;
        stop = 0;
        for(aux = k-1; aux>=0 && falso==0; aux--){
            i=teste[x][aux];
            for(m=1; m<=aux && falso==0; m++){
                j=teste[x][aux-m];
                if(code[i][j] == '0')
                    falso = 1;
            }
        }
        if(falso==1)
            x++;
        else 
            found = 1;

    }
    for(i=0; i<k; i++){
        clique[i] = teste[x][i];
    }
    return clique;
}

int find(ufind *dSet, int i){
    if(dSet[i].pai != i)
        dSet[i].pai = find(dSet, dSet[i].pai);
    return dSet[i].pai;
}

ufind *uniao(ufind *dSet, int x, int y){
    x = find(dSet, x);
    y = find(dSet, y);
    if(dSet[x].tam > dSet[y].tam)
        dSet[y].pai = x;
        else 
            if(dSet[x].tam < dSet[y].tam)
                dSet[x].pai = y;
                else{
                    dSet[y].pai = x;
                    dSet[x].tam += 1;
                }
    return dSet;
    
}

bool cliqueCompare(int *clique1, int *clique2, int k){
    bool result = true;
    for(int i=0; i<k; i++){
        if(clique1[i] != clique2[i]){
            i=k;
            result = false;
        }
    }
    return result;
}

int checkClique(char **code, int *clique1, int *clique2, int k, int n){
    int i, j, stop=0;
    for(i=k-1; i>0 && stop==0; i--){
        for(j=i-1; j>=0 && stop==0; j--){
            if(code[clique1[i]][clique1[j]] != '1')
                stop = 1;
        }
    }
    if(stop==0){
        for(i=0; i<k; i++)
            clique2[i] = clique1[i];
        return 1;
    }
    else 
        return 0;
}

int main(){

    int i, j, a, n, k, q, x=0, y=0, loop=0, out, gen = 1000000;

    cin >> a >> n >> k >> q;
    int *certif = new int[a];
    int *check = new int[a];
    int **clique = new int*[a];
    ufind *dSet = new ufind[a];
    char ***code = new char**[a];

    for(i=0; i<a; i++){
        certif[i] = 0;
        check[i] = 0;
        dSet[i].pai = i;
        dSet[i].tam = 0;
        clique[i] = new int[k];
        code[i] = new char*[n]; 
        for(j=0; j<n; j++){
            code[i][j] = new char[n];
        }
    }
    int **teste = new int*[gen];
    for(i=0; i<gen; i++)
        teste[i] = new int[k];
    
    teste = buildTeste(teste, k, n);

    while(loop<q){
        cin >> x >> y;
        out = 0;
        
        if(certif[x] == 0){
            code = buildMatrix(code, x, n);
            certif[x] = 1;
                
        }
        if(certif[y] == 0){
            code = buildMatrix(code, y, n);
            certif[y] = 1;
        }

        if(check[x] == 0){
            if(check[y] == 0){
                clique[x] = findClique(code[x], clique[x], teste, k, n);
                check[x] = 1;
            }
            else{
                check[x] = checkClique(code[x], clique[y], clique[x], k, n);
            }
        }
        if(check[y] == 0){
            check[y] = checkClique(code[y], clique[x], clique[y], k, n);
        }


        if(dSet[x].pai==x && dSet[y].pai==y){
            if(cliqueCompare(clique[x], clique[y], k)){
                dSet = uniao(dSet, x, y);
                out = 1;
            }
        }
        else if(dSet[x].pai!=x && dSet[y].pai!=y){
                x = find(dSet, x);
                y = find(dSet, y);
                if(x == y)
                    out = 1;
                    else{
                        if(cliqueCompare(clique[x], clique[y], k)){
                            dSet = uniao(dSet, x, y);
                            out = 1;
                        }
                    }
                    
            }
            else if(dSet[x].pai==x && dSet[y].pai!=y){
                    if(find(dSet, y) == x)
                        out = 1;
                        else{
                            if(cliqueCompare(clique[x], clique[y], k)){
                                dSet = uniao(dSet, x, y);
                                out = 1;
                            }
                        }     
                }
                else{
                    if(find(dSet, x) == y)
                        out = 1;
                        else{
                            if(cliqueCompare(clique[y], clique[x], k)){
                                dSet = uniao(dSet, y, x);
                                out = 1;
                            }
                        } 
                }
        
        if(out==1){
            cout << "SUCC ";
            for(i=0; i<k; i++){
                cout << clique[x][i];
                if(i+1 != k)
                    cout << " ";
            }
            cout << endl;
        }
        else{
            cout << "FAIL" << endl;
        }
        

        /*for(i=0; i<k; i++){
            cout << clique[x][i];
        }*/



        loop++;
    }





    return 0;
}