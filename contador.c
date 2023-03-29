#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdbool.h>

#define NUM_THREADS 3
pthread_t threads[NUM_THREADS];

pthread_mutex_t oMutex = PTHREAD_MUTEX_INITIALIZER;

int contador = 0;

void *incrementar(void * idThread);

int main(int argc, char *argv[]){
    int *codigoThread[NUM_THREADS], t;    

    for(t=0; t<NUM_THREADS; t++){
        codigoThread[t] = (int*)malloc(sizeof(int));
        *codigoThread[t] = t;
        pthread_create(&threads[t], NULL, incrementar, (void*)codigoThread[t]);
    }

    pthread_exit(NULL);
}

void *incrementar(void * idThread){
    int idT = *((int*)idThread), i;
    while(true){
        pthread_mutex_lock(&oMutex);
        contador++;
        if(contador==1000000){
            for(i=0; i<NUM_THREADS; i++){
                if(i!=idT){                    
                    pthread_cancel(threads[i]);
                    printf("To aqui %d\n", i);
                }
            }
            exit (0);
        }
        printf("Thread %d Contador = %d\n", idT, contador);      
        pthread_mutex_unlock(&oMutex);
    }
    printf("Contador = %d\n", contador);
    pthread_mutex_unlock(&oMutex);
    printf("Thread %d concluiu, contador = %d\n", idT, contador);
    pthread_exit(NULL);
}