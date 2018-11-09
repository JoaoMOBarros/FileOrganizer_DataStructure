#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000
#define MIN 1000

void geradorDeDatas();
int geradorDeNumerosAleatorios(int lower, int upper);

int main()
{
    int n;

    printf("Quantos registros deseja imprimir?: ");
    scanf("%d",&n);

    int *campo1 = (int*)malloc(n*sizeof(int));
    char **campo2 = (char**)malloc(n*sizeof(char*));
    char **campo3 = (char**)malloc(n*sizeof(char*));
    char **campo4 = (char**)malloc(n*sizeof(char*));

    char **campoaux = (char**)malloc(n*sizeof(char*));

    char vetorAux[20];

    srand(time(0));


    for (int i = 0; i<n; i++){
        campo2[i] = (char*)malloc(30*sizeof(char));
        campo3[i] = (char*)malloc(20*sizeof(char));
        campo4[i] = (char*)malloc(10*sizeof(char));
        campoaux[i] = (char*)malloc(12*sizeof(char));//usado para guardar os valores numericos

        sprintf(campoaux[i], "%d", i); //usada para criar um vetor de ints
    }

    for(int i = 0; i<n; i++){
        campo1[i] = geradorDeNumerosAleatorios(MIN, MAX)*1000;
        printf("%d \n", campo1[i]);
    }

    for(int i = 0; i<n; i++){
        strcpy(vetorAux, "Nome ");
        strcat(vetorAux, campoaux[i]);
        strcpy(campo2[i], vetorAux);
        printf("%s \n", campo2[i]);
    }

    for(int i = 0; i<n; i++){
        strcpy(vetorAux, "Area ");
        strcat(vetorAux, campoaux[i]);
        strcpy(campo2[i], vetorAux);
        printf("%s \n", campo2[i]);
    }

    for(int i =0; i<n; i++){
        strcpy(campo4[i],"");
        geradorDeDatas(campo4[i]);
        printf("%s \n", campo4[i]);
    }


    free(campo1);
    free(campo2);
    free(campo3);
    free(campo4);
    free(campoaux);



}

int geradorDeNumerosAleatorios(int lower, int upper){
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}


void geradorDeDatas(char *dataFinal){

    int dia = geradorDeNumerosAleatorios(1,28);
    int mes = geradorDeNumerosAleatorios(1,12);
    int ano = geradorDeNumerosAleatorios(1996, 2017);

    char vetorAux[12];


    sprintf(vetorAux,"%d/", dia);
    strcat(dataFinal, vetorAux);
    sprintf(vetorAux,"%d/", mes);
    strcat(dataFinal, vetorAux);

    sprintf(vetorAux,"%d", ano);
    strcat(dataFinal, vetorAux);
}
