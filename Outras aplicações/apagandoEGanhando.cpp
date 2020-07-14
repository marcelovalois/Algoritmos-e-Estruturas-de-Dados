// https://www.thehuxley.com/problem/653?locale=pt_BR

// Input: 
// A entrada contém vários casos de teste. A primeira linha de cada caso de teste contém dois inteiros N e D (1 <= D < N <= 10^5), indicando a quantidade de dígitos do número que o apresentador escreveu na lousa e quantos dígitos devem ser apagados. A linha seguinte contém o número escrito pelo apresentador, que não contém zeros à esquerda.
// O final da entrada é indicado por uma linha que contém apenas dois zeros, separados por um espaço em branco.


// Output:
// Para cada caso de teste da entrada seu programa deve imprimir uma única linha na saída,contendo o maior prêmio que Juliano pode ganhar.


#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(); ios::sync_with_stdio(0);

    int n, m, erased;
    bool flag=true;
    char ent;
    string result;
    stack<char> pilha;

    while(1){
        erased=0; result=""; flag = true;

        cin >> n >> m;
        if(!n && !m)
            break;
        
        for(int i=0; i<n; i++){
            cin >> ent;
            if(flag){
                pilha.push(ent);
                flag = false;
            }
            else{
                while(pilha.size() && ent > pilha.top() && erased<m){
                    erased++;
                    pilha.pop();
                }
                if(pilha.size()+1 <= (n-m)) pilha.push(ent);
            }
        }
        while(pilha.size()){
            result += pilha.top();
            pilha.pop();
        }
        for(int i=(n-m)-1; i>=0; i--)
            cout << result[i];
        cout << endl;
    }
    return 0;
}