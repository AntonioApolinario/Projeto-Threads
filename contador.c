#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdbool.h>
#include<unistd.h>

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

    for(t=0; t<NUM_THREADS; t++){
        pthread_join(threads[t], NULL);
    }

    pthread_exit(NULL);
}

void *incrementar(void * idThread){
    int idT = *((int*)idThread), i, s;    
    while(true){
        //cancelation point da thread
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        usleep(0.001);
        //fim do cancelation point da thread
        pthread_mutex_lock(&oMutex);        
        contador++;
        if(contador==1000000){
            for(i=0; i<NUM_THREADS; i++){
                if(i!=idT){                    
                    pthread_cancel(threads[i]);
                }
            }
            break;
        }
        //Se descomentar a linha abaixo, é mostrado a execução no contador
        //printf("Thread %d Contador = %d\n", idT, contador);      
        pthread_mutex_unlock(&oMutex);
    }
    pthread_mutex_unlock(&oMutex);
    printf("Thread %d concluiu, contador = %d\n", idT, contador);
    pthread_exit(NULL);
}