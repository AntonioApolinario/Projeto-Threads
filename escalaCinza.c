
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define PATH_COLOR "imagem.ppm" //caminho da imagem colorida
#define PATH_CINZA "cinza.ppm" //caminho da imagem em escala de cinza
//#define NUM_THREADS 4

typedef struct{
    int red, greem, blue;
}pixel;

typedef struct{
    pixel ** mat;
    int width, linha;
}aux;

void * calculaCinza(void * idThread);

int main(int argc, char *argv[]){
    FILE *colorida, *cinza;
    char formato[2];
    int largura, altura, cor255, i, j;
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
    for(i=0; i<altura; i++){
        matriz[i] = malloc(largura * sizeof(pixel));
    }

    for(i=0; i<altura; i++){
        for(j=0; j<largura; j++){
            fscanf(colorida, "%d %d %d\n", &matriz[i][j].red, &matriz[i][j].greem, &matriz[i][j].blue);
        }
    }


    pthread_t threads[altura];
    aux * argumentoFunc[altura];

    for(i=0; i<altura; i++){

        argumentoFunc[i] = (aux*)malloc(sizeof(aux));
        argumentoFunc[i]->linha = i;
        argumentoFunc[i]->mat = matriz;
        argumentoFunc[i]->width = largura;
        pthread_create(&threads[i], NULL, calculaCinza, (void*)argumentoFunc[i]);
    }

    for(i=0; i<altura; i++){
        for(j=0; j<largura; j++){
            fprintf(cinza, "%d %d %d\n", matriz[i][j].red, matriz[i][j].greem, matriz[i][j].blue);
        }
    }
    /* for(i=0; i<10)
    free(matriz); */

    pthread_exit(NULL);
}

void * calculaCinza(void * idThread){
    aux idT = *((aux*) idThread);
    int linha = idT.linha, j, cinza;
    pixel *mat = idT.mat[linha];

    for(j=0; j< idT.width; j++){
        cinza = mat[j].red*0.3 + mat[j].greem*0.3 + mat[j].blue*0.3;
        mat[j].red = cinza;
        mat[j].greem = cinza;
        mat[j].blue = cinza;
    }
    
    pthread_exit(NULL);
}