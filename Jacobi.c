#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define tam 2
#define NTHREADS 4

pthread_barrier_t barrier;

float A[tam][tam] = {{2.0,1.0},{5.0,7.0}};
float B[1][tam] = {11,13}
float X[tam] = [1, 1];

typedef struct
{
    int linha;
    int coluna;
}Coordenada;

void *threadCode(void *tid,void* linhaColuna){   
	
    Coordenada *coord = (Coordenada*)linhaColuna;
	int i,k;
    int x1[30],x2[30];
    int line = coord->linha;
    int column = coord->coluna;
    float *res = (float*)malloc(sizeof(float));
    *res = 0;
    int threadId = (*(int *)tid); 
	

	    for(i = 0; i < NTHREADS; i++)
        {
            x1[0]=1;
            x2[0]=1;
	   	    for(k=1;k<=30;k++)
            {
                x1[k] += 1/A[1][1] *(B[1]-A[1][2]*x2[k-1]);   
                x2[k] += 1/A[2][2] *(B[2]-A[2][1]*x1[k-1]);
                pthread_barrier_wait(&barrier);
            }			
            pthread_exit((void*)res);
    	}
  
}

int main() {
	
	pthread_t threads[THREADS]; 
    int *ids[THREADS];   
    int i;
	
	pthread_barrier_init(&barrier, NULL, 2);
	
	for(i = 0; i < NTHREADS; i++) 
    {
		ids[i] =(int *) malloc(sizeof(int)); 
		*ids[i] = i;
  	    pthread_create(&threads[i],NULL,threadCode,(void *) ids[i]);  
    }
  
    for(i = 0; i < NTHREADS; i++)
    {
        pthread_join(threads[i],NULL);
    }
  
    pthread_barrier_destroy(&barrier);
    
    pthread_exit(NULL);
  
    return 0;
  
}