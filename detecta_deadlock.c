#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define NUM_THREADS 4


//colunas A, B, C, D representam recursos
//linhas w, x, y, z representam processos
//                                  A  B  C  D
int processoUsandoRecurso[4][4] = {{0, 0, 1, 0},
                                   {1, 0, 0, 0},
                                   {0, 1, 0, 0},
                                   {0, 0, 0, 1}};


//Colunas = Recursos
//Linhas = Processos
//                                       w  x  y  z
int processoSolicitandoRecurso[4][4] = {{0, 1, 0, 0},
                                        {0, 0, 0, 1},
                                        {1, 0, 0, 0},
                                        {0, 1, 0, 0}};

void * verificaSolicitacaoProcesso(void * idProcesso);


int main(int argc, char * argv[]){
    int *idThread[NUM_THREADS] =  
    pthread_exit(NULL);
}


void * verificaSolicitacaoProcesso(void * idProcesso){
    int idP = *((int*) idProcesso), recurso;


}