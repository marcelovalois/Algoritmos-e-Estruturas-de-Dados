// https://iudex.io/problem/5ca3b874d41a630001c83bbc

// Uma árvore de busca binária (BST) é uma árvore binária em que o valor de cada nó é maior do que os valores 
// de cada nó à sua esquerda, e menor ou igual aos valores de cada nó à sua direita.
// Neste exercício iremos praticar as operações sobre BSTs vistas em aula.

// Input:
// A entrada inicia com uma linha contendo um inteiro

// N

// correspondente à quantidade inicial de nós de uma BST T.
// Segue-se uma linha com N inteiros separados por espaços,

// P[0] P[1] ... P[N-1]

// correspondentes aos valores dos nós de T enumerados em pré-ordem.
// Em seguida, temos várias operações numa das formas a seguir:

//     SCH k : procura o valor k em T
//     INS k : insere o valor k em T
//     DEL k : remove o valor k de T

// A entrada termina com uma linha

// END


// Output:
// Inicialmente, deve ser impressa uma linha com um inteiro

// Hinit

// correposndente à altura inicial da árvore T com os N elementos em pré-ordem dados na entrada.
// Em seguida, para cada operação deve-se imprimir o seguinte.

//     SCH k : imprime a profundidade do primeiro nó encontrado (nó menos profundo) com valor k. Caso tal nó não exista, imprime -1.
//     INS k : imprime a profundidade da folha com valor k inserida.
//     DEL k : imprime a profundidade do nó removido com valor k, se houver. Caso contrário imprime -1. Esse valor é o mesmo valor que seria impresso por SCH k antes da remoção.

// Ao final, deve-se imprimir uma linha

// Hfinal

// correspondente à altura final da árvore T, após todas as operações.


// Notes:
//     A altura de uma BST é o número de nós do maior caminho da raiz até uma de suas folhas. A árvore vazia tem altura 0, a árvore com apenas um nó tem altura 1, e assim sucessivamente.
//     A profundidade de um nó é a sua distância até a raiz, ou seja o número de arestas no caminho da raiz até ele. A raiz tem profundidade 0, os seus filhos tem profundidade 1, os seus netos tem profundidade 2, e assim sucessivamente.






#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int val;
    struct node *left;
    struct node *right;
}node;

node *createNode(int x){
    node *aux = (node *)malloc(sizeof(node));
    aux -> val = x;
    aux -> left = NULL;
    aux -> right = NULL;
    return aux;
}

node *bstSearch(node *root, int *depth, int v){
    if(root==NULL){
        *depth = -1;
        return NULL;
    }
    if(v == root -> val)
        return root;
        else if(v < root -> val){
            *depth+=1;
            return bstSearch(root -> left, depth, v);
        }
            else{
                *depth+=1;
                return bstSearch(root -> right, depth, v);
            }
}

node *bstInsert(node *root, int *depth, int v){
    node *aux;
    if (root==NULL){
        aux = createNode(v);
        return aux;
    }
    else if(v < root -> val){
        *depth+=1;
        root -> left = bstInsert(root->left, depth, v);
        return root;
    }
    else{
        *depth+=1;
        root -> right = bstInsert(root->right, depth, v);
        return root;
    }
}

node *bstDeleteMin(node *root, int *v){
    node *ptr, *aux;
    if(root->left==NULL){
        *v = root -> val;
        ptr = root -> right;
        free(root);
        return ptr;
    }
    else{
        root -> left = bstDeleteMin(root->left, v);
        return root;
    }

}

node *bstDelete(node *root, int v){
    node *l, *r, *aux;
    int value;
    if(root==NULL)
        return NULL;
        else if(v < root->val){
            root -> left = bstDelete(root->left, v);
            return root;
        }
        else if(v > root->val){
            root -> right = bstDelete(root->right, v);
            return root;
        }
        else{
            if(root->left == NULL){
                r = root->right;
                free(root);
                return r;
            }
            else if(root->right == NULL){
                l = root->left;
                free(root);
                return l;
            }
            else{
                root -> right = bstDeleteMin(root->right, &value);
                root -> val = value;
                return root;
            }
        }
}

int height(node *root){
    int l=0, r=0;
    if (root==NULL)
        return 0;
        else{
        l = height(root->left);
        r = height(root->right);
        if(l>r)
            return 1+l;
            else
            return 1+r;
        }
}

int main(){

    int n, aux, parada=0, altura, profund;
    char op[5];
    node *search=NULL, *insert=NULL, *delet=NULL, *tree=NULL;


    scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("%d", &aux);
        tree = bstInsert(tree, &profund, aux);
    }
    altura = height(tree);
    printf("%d\n", altura);

    do{
        scanf("%s", op);
        if(strcmp("END", op)==0){
            parada=1;
            altura = height(tree);
            printf("%d\n", altura);
        }
            else
                scanf("%d", &aux);

        if(strcmp("SCH", op)==0){
            profund=0;
            search = bstSearch(tree, &profund, aux);
            printf("%d\n", profund);
        }
        else if(strcmp("INS", op)==0){
            profund=0;
            insert = bstInsert(tree, &profund, aux);
            printf("%d\n", profund);
        }
        else if(strcmp("DEL", op)==0){
            profund=0;
            search = bstSearch(tree, &profund, aux);
            printf("%d\n", profund);
            delet = bstDelete(tree, aux);
        }
    }while(parada==0);

    return 0;
}
