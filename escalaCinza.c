#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define PATH_COLOR "imagem.ppm"
#define PATH_CINZA "cinza.ppm"
#define NUM_THREADS 4
FILE *colorida, *cinza;

int main(int argc, char *argv[]){
    char formato[2];
    int largura, altura;
    
    colorida = fopen(PATH_COLOR, "r");
    cinza = fopen(PATH_CINZA, "w");

    fscanf(colorida, "%s\n", formato);
    fprintf(cinza, "%s\n", formato);

    fscanf(colorida, "%d %d\n", &largura, &altura);
    fprintf(cinza, "%d %d\n", largura, altura);

    /* while(colorida =! EOF){

    } */
    return 0;
}

/* void * calculaCinza(void * idThread){
    int idT = *((int*) idThread), r, g, b;

    fscanf(colorida, %d %d %d, &r, &g, &b);

} */