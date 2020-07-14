// https://iudex.io/problem/5cb71fc5d41a630001c83e0c/statement

// As recentes vitórias da aliança rebelde rompeu com os anos de dominação inconteste do Império, trazendo ainda mais apoio popular aos rebeldes, o que não pode ser tolerado pelo imperador. O alto comando do Império deseja aplicar uma série de reformas em seu exército, o que inclui a reorganização de suas forças especiais para melhor eficácia em operações.

// As forças especiais do Império são compostas por um conjunto de S esquadrões, numerados de 0 a S-1. Oi-esimo esquadrão possui Q[i] membros associados. Cada agente das forças especiais possui um número identificador ID, um tempo de serviço T e um ranking R que corresponde ao seu desempenho em simulações e missões recentes. Para o imperador, interessa a vitória e a minimização de suas perdas, então é necessário que os agentes designados para cada missão sejam os mais adequados em função da sua experiência (tempo de serviço) e ranking, conforme o objetivo de cada esquadrão.

// Cada esquadrão possui, portanto, um critério para classificar/priorizar seus agentes, dentre quatro possíveis, numerados de 0 a 3 e descritos a seguir.

//     critério 0: menor tempo de serviço e, em caso de empate, maior ranking
//     critério 1: maior tempo de serviço e, em caso de empate, menor ranking
//     critério 2: menor ranking e, em caso de empate, maior tempo de serviço
//     critério 3: maior ranking e, em caso de empate, menor tempo de serviço

// Em qualquer dos critérios, caso haja empate no tempo de serviço e ranking, a prioridade vai para o menor ID.

// Por exemplo, suponha um esquadrão destinado a missões simples adequadas para o treinamento de soldados jovens e com baixo ranking. Nesse caso, o critério 1 seria o adequado.

// Devido a atual mudança no equilíbrio de poder, o Império está recrutando agentes para suas forças especiais, realizando mais treinos e reavaliando as atribuições de cada esquadrão, podendo haver a qualquer momento a chegada de um novo integrante, mudança de desempenho de um agente ou mudança do critério prioridade para um esquadrão. Cada mudança de prioridade é precedida de trocas de integrantes entre esquadrões diferentes.


// Input:
// A entrada inicia com um inteiro

// S

// representando o número de esquadrões.

// Seguem-se S linhas com o formato:

// Q[i] P[i] ID[0] T[0] R[0] ... ID[Q[i]-1] T[Q[i]-1] R[Q[i]-1]

// onde

//     Q[i] é o numero de agentes no esquadrão i
//     P[i] é um número de 0 a 3 que indica o critério de prioridade o esquadrão i
//     ID[j] T[j] R[j] indicam respectivamente o identificador, o tempo de serviço, e o ranking do j-ésimo agente do esquadrão, para j=0..Q[i]-1

// Logo após, seguem-se varias linhas, numa das formas abaixo.

//     ADD i ID T R: Adiciona um novo agente com identificador ID, tempo de serviço T e ranking R ao esquadrão i.
//     UPD ID T R: Atualiza o tempo de serviço e/ou ranking do agente com identificador ID para um T e R, respectivamente.
//     MOV i j: Move o agente com maior prioridade do esquadrão i para o esquadrão j.
//     CHG i j Q P: Move os Q<=size(i) agentes de maior prioridade do esquadrão i para o esquadrão j e, em seguida, atualiza o critério de prioridade do esquadrão i para P.
//     KIA ID: Remove o agente com identificador ID do seu respectivo esquadrão.

// A entrada termina com uma linha:

// END


// Output:
// Para cada linha ADD, UPD, CHG, MOV e KIA o programa deverá imprimir as saídas a seguir.

//     ADD i ID T R: imprime uma linha

// IDi Ti Ri

// representando o respectivamente o identificador, o tempo de serviço e o ranking do soldado de maior prioridade do esquadrão i após a inserção.

//     UPD ID T R ou KIA ID: imprime uma linha

// IDr Tr Rr

// representando o respectivamente o identificador, o tempo de serviço e o ranking do soldado de maior prioridade do esquadrão do agente de identificador ID após a atualização/remoção.

//     MOV i j ou CHG i j Q R: imprime uma linha

// IDi Ti Ri IDj Tj Rj

// representando respectivamente o identificador, o tempo de serviço e o ranking do soldado de maior prioridade dos esquadrões i e j após a operação.

// NOTA: Caso um esquadrão não possua mais agentes após um KIA, MOV ou CHG, deve-se imprimir -1 -1 -1 no lugar do identificador, tempo de serviço e ranking do (inexistente) agente de maior prioridade.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct agent{
    int id;
    int t;
    int r;
}agent;

typedef struct position{
    int i;
    int j;
}position;

int ordem(int criterio, agent new, agent cur){
    int result=0;
    if(criterio==0){
        if(new.t < cur.t)
            result=1;
        else if(new.t == cur.t){
            if(new.r > cur.r)
                result=1;
            else if(new.r == cur.r){
                if(new.id < cur.id)
                    result=1;
            }
        }
    }
    if(criterio==1){
        if(new.t > cur.t)
            result=1;
        else if(new.t == cur.t){
            if(new.r < cur.r)
                result=1;
            else if(new.r == cur.r){
                if(new.id < cur.id)
                    result=1;
            }
        }
    }
    if(criterio==2){
        if(new.r < cur.r)
            result=1;
        else if(new.r == cur.r){
            if(new.t > cur.t)
                result=1;
            else if(new.t == cur.t){
                if(new.id < cur.id)
                    result=1;
            }
        }
    }
    if(criterio==3){
        if(new.r > cur.r)
            result=1;
        else if(new.r == cur.r){
            if(new.t < cur.t)
                result=1;
            else if(new.t == cur.t){
                if(new.id < cur.id)
                    result=1;
            }
        }
    }
    return result;
}

agent *bubbleUp(agent *heap, int criterio, int i, position *pos){
    int p, order;
    agent aux;
    p = (i-1)/2;
    order = ordem(criterio, heap[i], heap[p]);
    while(i>0 && order==1){
        aux = heap[i];
        heap[i] = heap[p];
        heap[p] = aux; 
        pos[heap[i].id].j = i;
        pos[heap[p].id].j = p;
        i = p;
        p = (i-1)/2;
        order = ordem(criterio, heap[i], heap[p]);
    }
    return heap;
}

agent *heapInsert(agent *heap, int heapsize, int *arraySize, int criterio, agent aux, position *pos){
    int i;
    if(*arraySize==heapsize){
        heap = (agent *)realloc(heap, *arraySize*2*sizeof(agent));
        *arraySize *= 2;
    }
    i = heapsize;
    heap[i].id = aux.id;
    heap[i].t = aux.t;
    heap[i].r = aux.r;
    pos[aux.id].j = i;
    heap = bubbleUp(heap, criterio, i, pos);
    return heap;
}

void heapify(agent *heap, int i, int heapsize, int criterio, position *pos){
    int l=(2*i)+1 , r=(2*i)+2 , m=i, relOrdem;
    agent aux;

    relOrdem = ordem(criterio, heap[l], heap[m]);
    if(l<heapsize && relOrdem==1)
        m = l;
    relOrdem = ordem(criterio, heap[r], heap[m]);
    if(r<heapsize && relOrdem==1)
        m = r;
    if(m!=i){
        aux = heap[i];
        heap[i] = heap[m];
        heap[m] = aux;
        pos[heap[i].id].j = i;
        pos[heap[m].id].j = m;
        heapify(heap, m, heapsize, criterio, pos);
    }
}

void buildHeap(agent *heap, int heapsize, int criterio, position *pos){
    int i;
    for(i=(heapsize/2)-1; i>=0; i--){
        heapify(heap, i, heapsize, criterio, pos);
    }
}

agent heapExtract(agent *heap, int i, int heapsize, int criterio, position *pos){
    agent r;
    r = heap[i];
    heap[i] = heap[(heapsize-1)];
    heap[(heapsize-1)] = r;
    heapsize -= 1;
    pos[heap[i].id].j = i;
    heapify(heap, i, heapsize, criterio, pos);
    return r;
}


int main(){

    int stop=0, s, i, j, *p, *q, *arraySize, t, x, y;
    agent **agente, storage;
    position *agentPos;
    char op[5];

    scanf("%d", &s);
    q = (int *)malloc(s*sizeof(int));
    p = (int *)malloc(s*sizeof(int));
    arraySize = (int *)malloc(s*sizeof(int));
    agente = (agent **)malloc(s*sizeof(agent*));
    agentPos = (position *)malloc(1000000*sizeof(position));

    for (i=0; i<s; i++){
        scanf("%d %d", &q[i], &p[i]);
        agente[i] = (agent *)malloc(1000000*sizeof(agent));
        arraySize[i] = 1000000;
        for(j=0; j<q[i]; j++){
            scanf("%d %d %d", &agente[i][j].id, &agente[i][j].t, &agente[i][j].r);
            agentPos[agente[i][j].id].i = i;
            agentPos[agente[i][j].id].j = j;
        }
        buildHeap(agente[i], q[i], p[i], agentPos);
    }
    do{
        scanf("%s", op);
        if(strcmp("END", op)==0){
            stop=1;
        }
        else{
           if(strcmp("ADD", op)==0){
                scanf("%d %d %d %d", &i, &storage.id, &storage.t, &storage.r);
                agentPos[storage.id].i = i;
                agente[i] = heapInsert(agente[i], q[i], &arraySize[i], p[i], storage, agentPos);
                q[i] += 1;
                printf("%d %d %d\n", agente[i][0].id, agente[i][0].t, agente[i][0].r);
            }
            if(strcmp("UPD", op)==0){
                scanf("%d %d %d", &storage.id, &storage.t, &storage.r);
                i = agentPos[storage.id].i;
                j = agentPos[storage.id].j;
                agente[i][j].t = storage.t;
                agente[i][j].r = storage.r;
                heapify(agente[i], j, q[i], p[i], agentPos);
                agente[i] = bubbleUp(agente[i], p[i], j, agentPos);
                printf("%d %d %d\n", agente[i][0].id, agente[i][0].t, agente[i][0].r);
            }
            if(strcmp("MOV", op)==0){
                scanf("%d %d", &i, &j);
                storage = heapExtract(agente[i], 0, q[i], p[i], agentPos);
                q[i] -= 1;
                agentPos[storage.id].i = j;
                agente[j] = heapInsert(agente[j], q[j], &arraySize[j], p[j], storage, agentPos); 
                q[j] += 1;
                if(q[i]<=0)
                    printf("%d %d %d ", -1, -1, -1);
                    else
                        printf("%d %d %d ", agente[i][0].id, agente[i][0].t, agente[i][0].r);
                if(q[j]<=0)
                    printf("%d %d %d\n", -1, -1, -1);
                    else
                        printf("%d %d %d\n", agente[j][0].id, agente[j][0].t, agente[j][0].r);
            }
            if(strcmp("CHG", op)==0){
                scanf("%d %d %d %d", &i, &j, &x, &y);
                for(t=0; t<x; t++){
                    storage = heapExtract(agente[i], 0, q[i], p[i], agentPos);
                    q[i] -= 1;
                    agentPos[storage.id].i = j;
                    agente[j] = heapInsert(agente[j], q[j], &arraySize[j], p[j], storage, agentPos);
                    q[j] += 1;
                }
                if(p[i]!=y){
                p[i] = y;
                buildHeap(agente[i], q[i], p[i], agentPos);
                }

                if(q[i]<=0)
                    printf("%d %d %d ", -1, -1, -1);
                    else
                        printf("%d %d %d ", agente[i][0].id, agente[i][0].t, agente[i][0].r);
                if(q[j]<=0)
                    printf("%d %d %d\n", -1, -1, -1);
                    else
                        printf("%d %d %d\n", agente[j][0].id, agente[j][0].t, agente[j][0].r);

            }
            if(strcmp("KIA", op)==0){
                scanf("%d", &storage.id);
                i = agentPos[storage.id].i;
                j = agentPos[storage.id].j;
                storage = heapExtract(agente[i], j, q[i], p[i], agentPos);
                q[i] -= 1;
                agentPos[storage.id].i = j;
                agente[i] = bubbleUp(agente[i], p[i], j, agentPos);
                if(q[i]<=0)
                    printf("%d %d %d\n", -1, -1, -1);
                    else
                        printf("%d %d %d\n", agente[i][0].id, agente[i][0].t, agente[i][0].r);
            }


        }
        /*for(i=0; i<s; i++){
            for(j=0; j<q[i]; j++){
                printf("%d %d %d\n", agente[i][j].id, agente[i][j].t, agente[i][j].r);
            }
            printf("\n");
        }*/
    }while(stop==0);

    return 0;
}