#include <iostream>
#include <string>
using namespace std;

typedef struct ufind{
    int pai;
    int alt;
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

int main(){

    int i, j, a, n, k, q, x=0, y=0, loop=0, gen = 1000000;

    cin >> a >> n >> k >> q;
    int *certif = new int[a];
    int **clique = new int*[a];
    ufind *dSet = new ufind[a];
    char ***code = new char**[a];

    for(i=0; i<a; i++){
        certif[i] = 0;
        dSet[i].pai = i;
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
        
        if(certif[x] == 0){
            code = buildMatrix(code, x, n);
            certif[x] = 1;
            clique[x] = findClique(code[x], clique[x], teste, k, n);
        }
        if(certif[y] == 0){
            //code = buildMatrix(code, y, n);
            certif[y] = 1;
            //clique[y] = findClique(code[y], teste, k, n);
        }

        /*for(i=0; i<k; i++){
            cout << clique[x][i];
        }*/



        loop++;
    }





    return 0;
}