#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define BUFFER 50
#define PRODUTORAS 3
#define CONSUMIDORAS 4

typedef struct elem{
    int value;
    struct elem *prox;
}Elem;

typedef struct blockingQueue{
    unsigned int sizeBuffer, statusBuffer;
    Elem *head, *last;
}BlockingQueue;

typedef struct{
    BlockingQueue *fb;
    int codigo;
}estructAux;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t produzir[PRODUTORAS];
pthread_cond_t consumir[CONSUMIDORAS];

BlockingQueue *newBlockingQueue(unsigned int SizeBuffer);
void putBlockingQueue(BlockingQueue *Q, int newValue);
int takeBlockingQueue(BlockingQueue *Q);
void * produtora(void * filaBloq);
void * consumidora(void * filaBloq);

int main(int argc, char* argv[]){


    pthread_exit(NULL);
}


BlockingQueue *newBlockingQueue(unsigned int SizeBuffer){
    BlockingQueue * fila = (BlockingQueue*)malloc(sizeof(BlockingQueue));
    Elem * sentinela = (Elem*)malloc(sizeof(Elem));
    fila->sizeBuffer = SizeBuffer;
    fila->statusBuffer = 0;
    fila->head = sentinela;
    fila->last = sentinela;

    return fila;    
}

void putBlockingQueue(BlockingQueue *Q, int newValue){
    Elem * newElem = (Elem*)malloc(sizeof(Elem));
    newElem->value = newValue;

    if(Q->head != Q->last){
        Q->last->prox = newElem;
        Q->last = newElem;
    }
    else{
        Q->head->prox = newElem;
        Q->last = newElem;
        Q->statusBuffer++;
    }
}

int takeBlockingQueue(BlockingQueue *Q){
    int val; 
    Elem * aux = Q->head->prox;
    Q->head->prox = aux->prox;
    val = aux->value;
    free(aux);
    return val;
}

void * produtora(void * aux){
    estructAux *filaBlock = (estructAux*)filaBloq;
    int threadId = filaBlock->codigo;
    BlockingQueue * aux = filaBlock->fb;
    
    pthread_cond_init(&produzir[threadId], NULL);
    while (filaBlock->fb->statusBuffer== BUFFER){
        pthread_cond_wait(&produzir[threadId], &mutex);
    }

    phthrea_mutex
    
    pthread_exit(NULL);
}