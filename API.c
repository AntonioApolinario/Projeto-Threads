#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdbool.h>

//Variáveis globais
#define NTHREADS 3
int contador = 0;

pthread_t incrementador[NTHREADS];

pthread_mutex_t oMutex = PTHREAD_MUTEX_INITIALIZER;

//A função de thread que ira incrementar o contador
void *thread(void *idThread);


int main(int argc, char *argv[]){

    int *codigoThread[NTHREADS], i;
    
    
    for(i=0; i<NTHREADS; i++){
        codigoThread[i] = (int*)malloc(sizeof(int));
        *codigoThread[i] = i;
        pthread_create(&incrementador[i], NULL, thread, (void*)codigoThread[i]);
    }

    for(i=0; i<NTHREADS; i++){
        pthread_join(incrementador[i], NULL);
    }
    
    pthread_exit(NULL);
    return 0;
}


void *thread(void *idThread){
    int i, id = *((int*)idThread), codigo;
    while(true){
        pthread_mutex_lock(&oMutex);
        contador++;
        //printf("Thread %d contador= %d\n", id, contador);
        if(contador == 1000000){
            for(i=0; i<NTHREADS; i++){
                if(i != id){
                    codigo = pthread_cancel(incrementador[i]);
                    printf("Codigo do cancelamento %d da thread %d\n", codigo, i);
                }
            }
            break;        
        }
        pthread_mutex_unlock(&oMutex);
    }
    pthread_mutex_unlock(&oMutex);
    printf("Thread %d concluiu\n", id);
    pthread_exit(NULL);
    printf("Fechou\n");
}