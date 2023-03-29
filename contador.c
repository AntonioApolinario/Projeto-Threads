#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define NUM_THREADS 30
pthread_t threads[NUM_THREADS];

pthread_mutex_t oMutex = PTHREAD_MUTEX_INITIALIZER;

long contador = 0;

void *incrementar(void * idThread);

int main(int argc, char *argv[])
{
    int *codigoThread[NUM_THREADS], t;    

    for(t=0; t<NUM_THREADS; t++){
        codigoThread[t] = (int*)malloc(sizeof(int));
        *codigoThread[t] = t;
        pthread_create(&threads[t], NULL, incrementar, (void*)codigoThread[t]);
    }

    pthread_exit(NULL);
}

void *incrementar(void * idThread)
{
    int idT = *((int*)idThread), i;
    for(i=0; i < 1000000; i++)
    {
        pthread_mutex_lock(&oMutex);
        contador++;
        if(contador == 1000000)
        {
            printf("Thread %d conclui, contador = %ld\n", idT, contador);
            exit(0);
        }
        pthread_mutex_unlock(&oMutex);
    }    
    pthread_exit(NULL);
}