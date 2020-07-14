// https://iudex.io/problem/5c782bb112c2940001b3cf8d

// A fabricante de telefones In Tell decidiu desenvolver um sistema de controle para sua linha de montagem. 
// Essa linha de montagem é composta de M esteiras, numeradas 0..M-1, por onde circulam os aparelhos em fabricação, 
// cada um dos quais possui um identificador (ID) único. 
// Inicialmente, cada aparelho é colocado ao final da esteira 0 - esteira principal - e dessa esteira, eles devem ser 
// redistribuídos para as outras M-1 esteiras da linha de produção. Cada esteira possui, associada a si, uma pilha de reparos, 
// destinada aos produtos defeituosos que não podem seguir normalmente na linha de produção. 
// Cada uma das pilhas de reparo está sob os cuidados de um técnico responsável pelo reparo dos itens defeituosos. 
// Uma vez reparado, o item deve ser recolocado na sua respectiva esteira. Caso o reparo seja inviável, o item deve ser descartado. 
// Dessa forma, o sistema deve responder aos seguintes eventos.

//     NEW I : adiciona um novo aparelho de identificador I ao final da esteira principal.
//     MOV B : move o produto da frente da esteira principal paro o final da esteira B.
//     DEF B : indica que o produto da frente da esteira B está com defeito e deve ser colocado na respectiva pilha de itens a serem reparados.
//     FIX B : indica que o produto no topo da pilha de reparos B foi reparado e deve ser recolocado no final da esteira B.
//     TSH B : indica que o item no topo da pilha B não pode ser reparado e deve ser descartado.
//     RDY B : indica que o produto da frente da esteira B já está pronto e deve ser retirado da linha de montagem e registrado no sistema para expedição.

// Input:
// A primeira linha contém um inteiro 

// M

// indicando o número de esteiras da linha de produção, sendo a esteira 0 a esteira principal.
// Em seguida, temos várias linhas, cada uma contendo um evento num dos formatos descritos acima.
// A entrada termina com uma linha contendo o evento

// END


// Output:
// Para cada evento RDY, deve ser impressa uma linha

// I OK

// onde I representa o ID do aparelho fabricado.
// Para cada evento TSH, deve ser impressa uma linha

// I BAD

// onde I representa o ID do item descartado.




#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int value;
    struct node *next;
}node;

node *createNode(int x){
    node *aux = (node *)malloc(sizeof(node));
    aux -> value = x;
    aux -> next = NULL;
    return aux;
}

node *inserirPilha(node *head, int value){
    node *cur = head;
    if(head -> next == NULL)
        head -> next = createNode(value);
        else{
            node *aux = cur -> next;
            cur -> next = createNode(value);
            cur = cur -> next;
            cur -> next = aux;
        }
    return head;
}

node *removerPilha(node *head){
    node *aux = head -> next;
    if(aux -> next == NULL)
        head -> next = NULL;
        else
            head -> next = aux -> next;
        free(aux);
        return head;
}

node *inserirFila(node *tail, int value){
    tail -> next = createNode(value);
    tail = tail -> next;
    return tail;
}

node *removerFila(node *tail, node *head){
    node *aux = head -> next;
    head -> next = aux -> next;
    free(aux);
    if(head->next != NULL){
        return tail;
        }
        else
            return head;
}

int main(){

    int m, i, event, parada=0;
    char evento[5];

    scanf("%d", &m);

    node **esteira_head = (node **)malloc(m*sizeof(node*));
    if(esteira_head==NULL) exit(1);
    node **esteira_tail = (node **)malloc(m*sizeof(node*));
    if(esteira_tail==NULL) exit(1);
    node **pilha_head = (node **)malloc(m*sizeof(node*));

    for(i=0; i<m; i++){
        esteira_head[i] = createNode(-1);
        esteira_tail[i] = esteira_head[i];
        pilha_head[i] = createNode(-1);
    }
    
    do{
        scanf("%s", evento);
        if(strcmp("END", evento)==0)
            parada=1;
            else
                scanf("%d", &event);

        if(strcmp("NEW", evento)==0){
            esteira_tail[0] = inserirFila(esteira_tail[0], event);
        }
            else if(strcmp("MOV", evento)==0){
                esteira_tail[event] = inserirFila(esteira_tail[event], esteira_head[0] -> next -> value);
                esteira_tail[0] = removerFila(esteira_tail[0], esteira_head[0]);
            }
                else if(strcmp("DEF", evento)==0){
                  //  printf("Topo da principal antes %d\n", esteira_head[0]-> next -> value);
                    pilha_head[event] = inserirPilha(pilha_head[event], esteira_head[event] -> next -> value);
                    esteira_tail[event] = removerFila(esteira_tail[event], esteira_head[event]);
                   // printf("Topo da principal depois %d\n", esteira_head[0]-> next -> value);
                   // printf("Topo da pilha %d\n", pilha_head[event] -> next -> value);
                }
                    else if(strcmp("FIX", evento)==0){
                      // printf("Topo da pilha %d\n", pilha_head[event] -> next -> value);
                       // printf("Segundo da pilha %d\n", pilha_head[event]-> next -> next -> value);
                       // printf("Rabo da principal antes %d\n", esteira_tail[0] -> value);
                        esteira_tail[event] = inserirFila(esteira_tail[event], pilha_head[event] -> next -> value);
                        pilha_head[event] = removerPilha(pilha_head[event]);
                       // printf("Topo da pilha depois %d\n", pilha_head[event] -> next -> value);
                       // printf("Rabo da principal depois %d\n", esteira_tail[0] -> value);
                    }
                        else if(strcmp("TSH", evento)==0){
                            printf("%d BAD\n", pilha_head[event] -> next -> value);
                            pilha_head[event] = removerPilha(pilha_head[event]);
                        }
                            else if(strcmp("RDY", evento)==0){
                                printf("%d OK\n", esteira_head[event]-> next -> value);
                                esteira_tail[event] = removerFila(esteira_tail[event], esteira_head[event]);
                            }
    }while(parada==0);

    return 0;
}
