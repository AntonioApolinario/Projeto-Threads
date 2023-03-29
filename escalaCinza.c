#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define PATH_COLOR "imagem.ppm" //caminho da imagem colorida
#define PATH_CINZA "cinza.ppm" //caminho da imagem em escala de cinza
#define NUM_THREADS 4

typedef struct{
    int r, g, b;
}pixel;

FILE *colorida, *cinza;

int main(int argc, char *argv[]){
    char formato[2];
    int largura, altura, cor255, i, **matrizCinza;
    pixel **matriz;
    
    colorida = fopen(PATH_COLOR, "r");
    cinza = fopen(PATH_CINZA, "w");

    fscanf(colorida, "%s\n", formato);
    fprintf(cinza, "%s\n", formato);

    fscanf(colorida, "%d %d\n", &largura, &altura);
    fprintf(cinza, "%d %d\n", largura, altura);

    fscanf(colorida, "%d\n", &cor255);
    fprintf(cinza, "%d\n", cor255);

    matriz =  malloc(altura * sizeof(pixel*));
    for(i=0; i<largura; i++){
        matriz[i] = malloc(largura * sizeof(pixel));
    }

    matrizCinza =  malloc(altura * sizeof(int*));
    for(i=0; i<largura; i++){
        matrizCinza[i] = malloc(largura * sizeof(int));
    }    

    /* while(colorida =! EOF){

    } */
    return 0;
}

/* void * calculaCinza(void * idThread){
    int idT = *((int*) idThread), r, g, b;

    fscanf(colorida, %d %d %d, &r, &g, &b);

} */