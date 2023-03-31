#define _XOPEM_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define tam 2
#define NTHREADS 4

pthread_barrier_t barrier;

float A[tam][tam] = {{2.0,1.0},{5.0,7.0}};
float B[tam] = {11,13};
float X[tam] = {1, 1};

typedef struct
{
    int linha;
    int coluna;
    int Tid;
}Coordenada;

void *threadCode(void *tid){   
	
    Coordenada coord = *(Coordenada*)tid;
	int i,k;
    int x1[30],x2[30];
    int line = coord.linha;
    int column = coord.coluna;
    float *res = (float*)malloc(sizeof(float));
    *res = 0;
    int threadId = (coord.Tid); 
	

	    for(i = 0; i < NTHREADS; i++)
        {
            x1[0]=1;
            x2[0]=1;
	   	    for(k=1;k<=30;k++)
            {
                x1[k] += (1/A[1][1]) * (B[1] - A[1][2]*x2[k-1]);   
                x2[k] += (1/A[2][2]) * (B[2] - A[2][1]*x1[k-1]);
                pthread_barrier_wait(&barrier);
            }			
            pthread_exit((void*)res);
    	}
  
}

int main() {
	
	pthread_t threads[NTHREADS]; 
    Coordenada *ids[NTHREADS];   
    int i;
	
	pthread_barrier_init(&barrier, NULL, 2);
	
	for(i = 0; i < NTHREADS; i++) 
    {
		ids[i] = malloc(sizeof(Coordenada)); 
		ids[i]->Tid = i;
        ids[i]->coluna = i;
        ids[i]->linha = i;
  	    pthread_create(&threads[i],NULL,threadCode,(void *) ids[i]);  
    }
  
    for(i = 0; i < NTHREADS; i++)
    {
        float result
        pthread_join(threads[i],(void*)result);
        printf(%f,result);
    }
  
    pthread_barrier_destroy(&barrier);
    
    pthread_exit(NULL);
  
    return 0;
  
}
