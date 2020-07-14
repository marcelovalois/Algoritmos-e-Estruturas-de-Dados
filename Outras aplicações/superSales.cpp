// https://www.thehuxley.com/problem/1021?locale=pt_BR

// Input:
// A entrada consiste de T casos de teste (1 ≤ T ≤ 1000), que é inserido na primeira linha do arquivo de entrada. 
// Cadacaso de teste começa com uma linha contendo um único inteiro N que indica o número de objetos (1 ≤ N ≤ 1000). 
// Então as N linhas sequintes, cada uma contém dois inteiros: P e W. O primeiro inteiro (1 ≤ P ≤ 100) corresponde ao preço do objeto.
// O segundo inteiro (1 ≤ W ≤ 30) corresponde ao peso daquele objeto. 
// A próxima linha contem um inteiro (1 ≤ G ≤ 100), que é onúmero de pessoas no nosso grupo. 
// As próximas G linhas contem o peso máximo (1 ≤ MW ≤ 30) que cada i-ésima pessoa da famíliaconsegue carregar (1 ≤ i ≤ G).


// Output:
// Para cada caso de teste seu programa tem que determinar um inteiro. Imprima o valor máximo que a gente consegue comprarcom aquela família.


#include <stdio.h> 
  
// A utility function that returns maximum of two integers 
int max(int a, int b) { return (a > b)? a : b; } 
  
// Returns the maximum value that can be put in a knapsack of capacity W 
int knapSack(int W, int wt[], int val[], int n) 
{ 
   int i, w; 
   int K[n+1][W+1]; 
  
   // Build table K[][] in bottom up manner 
   for (i = 0; i <= n; i++) 
   { 
       for (w = 0; w <= W; w++) 
       { 
           if (i==0 || w==0) 
               K[i][w] = 0; 
           else if (wt[i-1] <= w) 
                 K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]); 
           else
                 K[i][w] = K[i-1][w]; 
       } 
   } 
   return K[n][W]; 
} 

int main(){

    int t, i, j, aux;
    scanf("%d", &t);
    for(i=0; i<t; i++){
        int n, val[2000], wt[2000], pessoas[200], g, count=0;
        scanf("%d", &n);
        for(j=0; j<n; j++){
            scanf("%d %d", &val[j], &wt[j]);
        }
        scanf("%d", &g);
        for(j=0; j<g; j++){
            scanf("%d", &pessoas[j]);
        }
        aux = j;
        for(j=0; j<aux; j++){
            count += knapSack(pessoas[j], wt, val, n);
        }
        printf("%d\n", count);
    }

    return 0;
}