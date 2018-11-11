#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100000
#define MIN 1000

void geradorDeDatas();
int geradorDeNumerosAleatorios(int lower, int upper);
void criarRegistro(int n, int *campo1, char **campo2, char **campo3, char **campo4);
void criarBinario(int n, int *campo1, char **campo2, char **campo3, char **campo4);
void mostrarRegistros(int n, int *campo1, char **campo2, char **campo3, char **campo4);

typedef struct reg{

    int campo1;
    char campo2[30];
    char campo3[20];
    char campo4[10];

}REGISTRO;// Caso sobre um tempo, seria interessante juntarmos todos os campos em formator de REGISTRO atraves de uma struct

int main()
{
    int n;

    printf("Quantos registros deseja imprimir?: ");
    scanf("%d",&n);

    int *campo1 = (int*)malloc(n*sizeof(int)); // Aqui são feitas as definições de cada vetor dinamicamente
    char **campo2 = (char**)malloc(n*sizeof(char*)); //Como strings não existem em C, vamos precisar usar um vetor de chars, e para liga-los, precisaremos de um segundo ponteiro
    char **campo3 = (char**)malloc(n*sizeof(char*)); //Por essa razão as variaveis do tipo char vem com ponteiro duplo
    char **campo4 = (char**)malloc(n*sizeof(char*));

    srand(time(0));

    criarRegistro(n, campo1, campo2, campo3, campo4);

    criarBinario(n, campo1, campo2, campo3, campo4);

    free(campo1);
    free(campo2);
    free(campo3);
    free(campo4);

    return  0;
}

int geradorDeNumerosAleatorios(int lower, int upper){
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

void criarRegistro(int n, int *campo1, char **campo2, char **campo3, char **campo4){

    char vetorAux[30]; // Essa linha é a próxima são campos que foram usados para auxi

     for (int i = 0; i<n; i++){
        campo2[i] = (char*)malloc(30*sizeof(char));//nessa segunda alocação de memoria faz com que cada celula do char* ganhe os espaço certo para as strings
        campo3[i] = (char*)malloc(20*sizeof(char));
        campo4[i] = (char*)malloc(10*sizeof(char));

    }

    for(int i = 0; i<n; i++){ //Geração do campo1 (valor de mercado), onde gera um valor aleatorio correspondente num intervalo de 1000000 e 100000000
        if(i<0.7*n){
            campo1[i] = geradorDeNumerosAleatorios(MIN, MAX)*1000;
        }
        else{ //todos os elses servirão para configurar as repetições esperadas
            campo1[i] = campo1[geradorDeNumerosAleatorios(0, 0.7*n)];
        }
    }

    for(int i = 0; i<n; i++){
        if(i<0.75*n){
            sprintf(vetorAux, "Nome_%d", i);//essa função serve para se escrever dentro de uma string
            strcpy(campo2[i], vetorAux); //essa aqui acopla o resultado da segunda string no final da primeira
        }
        else{
            strcpy(campo2[i], campo2[geradorDeNumerosAleatorios(0,0.75*n)]);
        }
    }

    for(int i = 0; i<n; i++){
        if(i<0.80*n){
            sprintf(vetorAux, "Area_%d", i);
            strcpy(campo3[i], vetorAux);
        }
        else{
            strcpy(campo3[i], campo3[geradorDeNumerosAleatorios(0,0.8*n)]);
        }
    }

    for(int i =0; i<n; i++){
        if(i<0.85*n){
            strcpy(campo4[i],"");
            geradorDeDatas(campo4[i]);
        }
        else{
            strcpy(campo4[i],campo4[geradorDeNumerosAleatorios(0,0.85*n)]);
        }
    }

    mostrarRegistros(n, campo1, campo2, campo3, campo4);

}

void criarBinario(int n, int *campo1, char **campo2, char **campo3, char **campo4){
     FILE *binaryFile2;
     binaryFile2 = fopen("file2.bin", "wb");

    if (binaryFile2 == NULL){
        printf("Unable to open the file");
    }
    else{
        for(int i = 0;i<n;i++){
            fwrite(&campo1[i], sizeof(int),1,binaryFile2);
            fwrite(campo2[i], 30,1,binaryFile2);
            fwrite(campo3[i], 20,1,binaryFile2);
            fwrite(campo4[i], 10,1,binaryFile2);

            printf("%d ", i);
        }
    }

    fclose(binaryFile2);
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

void mostrarRegistros(int n, int *campo1, char **campo2, char **campo3, char **campo4){
    for(int i = 0; i<n; i++){
        printf("%d ", campo1[i]);
        printf("%s ", campo2[i]);
        printf("%s ", campo3[i]);
        printf("%s \n", campo4[i]);
    }
}
