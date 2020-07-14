// https://www.thehuxley.com/problem/242

// Input:
// A entrada contém vários casos de teste. A primeira linha de entrada contém um inteiro N indicando a quantidade de casos de teste. Cada caso de teste é composto por duas linhas. A primeira linha contém um valor M (1 ≤ M ≤ 100) que indica a quantidade de endereços-base na tabela (normalmente um número primo) seguido por um espaço e um valor C (1 ≤ C ≤ 200) que indica a quantidade de chaves a serem armazenadas. A segunda linha contém cada uma das chaves (com valor entre 1 e 200), separadas por um espaço em branco.

// É importante considerar que nessa tabela específica, uma mesma chave poderá ser inserida várias vezes. O elemento duplicado deve ser inserido no final da lista.


// Output:
// A saída deverá ser impressa conforme os exemplos fornecidos abaixo, onde a quantidade de linhas de cada caso de teste é determinada pelo valor de M. Uma linha em branco deverá separar dois conjuntos de saída.


#include <bits/stdc++.h>
using namespace std;

void printTable(vector<int> ht[], int m){
    vector<int>::iterator it;
    for(int i=0; i<m; i++){
        cout << i << " -> ";
        for(it=ht[i].begin(); it!=ht[i].end(); it++){
            cout << *it << " -> ";
        }
        cout << "\\" << endl;
    }
    cout << endl;
}

int main(){

    int c, n, m, key, val;

    cin >> n;
    for(int l=0; l<n; l++){
        cin >> m >> c;
        vector<int> hashtable[m];
        for(int i=0; i<c; i++){
            cin >> val;
            key = val % m;
            hashtable[key].push_back(val);
        }
        printTable(hashtable, m);
    }


    return 0;
}
