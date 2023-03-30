#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdbool.h>

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
pthread_cond_t fill = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

BlockingQueue *newBlockingQueue(unsigned int SizeBuffer);
void putBlockingQueue(BlockingQueue *Q, int newValue);
int takeBlockingQueue(BlockingQueue *Q);
void * produtora(void * filaBloq);
void * consumidora(void * filaBloq);

int main(int argc, char* argv[]){
    int i;
    BlockingQueue *filaBloq = newBlockingQueue(BUFFER);
    pthread_t threadProduz[PRODUTORAS];
    pthread_t threadConsome[CONSUMIDORAS];

    estructAux *filaBlockEndIdP[PRODUTORAS];
    estructAux *filaBlockEndIdC[CONSUMIDORAS];


    for(i=0; i<PRODUTORAS; i++){
        filaBlockEndIdP[i] = (estructAux*)malloc(sizeof(estructAux));
        filaBlockEndIdP[i]->codigo = i;
        filaBlockEndIdP[i]->fb = filaBloq;
        pthread_create(&threadProduz[i], NULL, produtora, (void*) filaBlockEndIdP[i]);
    }

    for(i=0; i<CONSUMIDORAS; i++){
        filaBlockEndIdC[i] = (estructAux*)malloc(sizeof(estructAux));
        filaBlockEndIdC[i]->codigo = i;
        filaBlockEndIdC[i]->fb = filaBloq;
        pthread_create(&threadConsome[i], NULL, consumidora, (void*) filaBlockEndIdC[i]);
    }
    
}


BlockingQueue *newBlockingQueue(unsigned int SizeBuffer){
    BlockingQueue * fila = (BlockingQueue*)malloc(sizeof(BlockingQueue));
    Elem * sentinela = (Elem*)malloc(sizeof(Elem));
    fila->sizeBuffer = SizeBuffer;
    fila->statusBuffer = 0;
    fila->head = sentinela;
    fila->last = NULL;

    return fila;    
}

void putBlockingQueue(BlockingQueue *Q, int newValue){
    Elem * newElem = (Elem*)malloc(sizeof(Elem));
    newElem->value = newValue;
    newElem->prox = NULL;
    
    if(Q->head != Q->last){
        Q->last->prox = newElem;
        Q->last = newElem;
        printf("foi aqui\n");
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
    estructAux *filaBlock = (estructAux*)aux;
    int threadId = filaBlock->codigo;
    int x;
    //Elem *cursor;     

    while(true){
        pthread_mutex_lock(&mutex);
        while(filaBlock->fb->statusBuffer == BUFFER){
            pthread_cond_wait(&empty, &mutex);
        }

        pthread_cond_init(&produzir[threadId], NULL);
        while (filaBlock->fb->statusBuffer == BUFFER){
            pthread_cond_wait(&produzir[threadId], &mutex);
        }
        x = rand()%100;

        putBlockingQueue(filaBlock->fb, x);
        printf("foi aqui\n");
        //cursor = filaBlock->fb->head->prox;
        

        /* while(cursor->prox != NULL){
            printf("Valor %d, ", cursor->value);
            cursor =  cursor->prox;
        }
         */
        if(threadId +1 == PRODUTORAS)
            pthread_cond_signal(&produzir[0]);
        else{
            pthread_cond_signal(&produzir[threadId+1]);
        }

        pthread_cond_destroy(&produzir[threadId]);

        if(filaBlock->fb->statusBuffer == 0)
            pthread_cond_signal(&fill);
        
        pthread_mutex_unlock(&mutex);
        printf("Deu certo %d\n", x);
    }
}





void * consumidora(void * aux){
    estructAux *filaBlock = (estructAux*)aux;
    int threadId = filaBlock->codigo;
    int x;

    while(true){
        pthread_mutex_lock(&mutex);
        while(filaBlock->fb->statusBuffer != 0){
            pthread_cond_wait(&fill, &mutex);
        }

        pthread_cond_init(&consumir[threadId], NULL);
        while (filaBlock->fb->statusBuffer != 0){
            pthread_cond_wait(&consumir[threadId], &mutex);
        }
        printf("E pra colocar algo aqui\n");

        putBlockingQueue(filaBlock->fb, x);
        
        if(threadId +1 == CONSUMIDORAS)
            pthread_cond_signal(&consumir[0]);
        else{
            pthread_cond_signal(&consumir[threadId+1]);
        }

        pthread_cond_destroy(&consumir[threadId]);

        if(filaBlock->fb->statusBuffer == BUFFER)
            pthread_cond_signal(&empty);
        
        pthread_mutex_unlock(&mutex);
    }
}