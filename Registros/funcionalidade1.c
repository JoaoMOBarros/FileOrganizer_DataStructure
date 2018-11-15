#include "funcionalidade1.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MIN 1

#define MAX 50000

typedef struct reg{

    int campo1;
    char campo2[30];
    char campo3[20];
    char campo4[11];

}REGISTRO;// Caso sobre um tempo, seria interessante juntarmos todos os campos em formator de REGISTRO atraves de uma struct

int geradorDeNumerosAleatorios(int lower, int upper){
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;


void criarRegistro(int n, REGISTRO* reg){

    for(int i = 0; i<n; i++){ //Geração do campo1 (valor de mercado), onde gera um valor aleatorio correspondente num intervalo de 1000000 e 100000000
        if(i<0.7*n){
            reg[i].campo1 = geradorDeNumerosAleatorios(MIN, MAX);
        }
        else{ //todos os elses servirão para configurar as repetições esperadas
            reg[i].campo1 = reg[geradorDeNumerosAleatorios(0, 0.7*n)].campo1;
        }
    }

    for(int i = 0; i<n; i++){
        if(i<0.75*n){
            sprintf(reg[i].campo2, "Nome_%d", i);//essa função serve para se escrever dentro de uma string
        }
        else{
            strcpy(reg[i].campo2, reg[geradorDeNumerosAleatorios(0,0.75*n)].campo2);
        }
    }

    for(int i = 0; i<n; i++){
        if(i<0.80*n){
            sprintf(reg[i].campo3, "Area_%d", i);
        }
        else{
            strcpy(reg[i].campo3, reg[geradorDeNumerosAleatorios(0,0.8*n)].campo3);
        }
    }

    for(int i =0; i<n; i++){
        if(i<0.85*n){
            strcpy(reg[i].campo4,"");
            geradorDeDatas(&reg[i].campo4);
        }
        else{
            strcpy(reg[i].campo4,reg[geradorDeNumerosAleatorios(0,0.85*n)].campo4);
        }
    }
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

void mostrarRegistros(int n, REGISTRO* reg){
    for(int i = 0; i<n; i++){
        printf("%d ", reg[i].campo1);
        printf("%s ", reg[i].campo2);
        printf("%s ", reg[i].campo3);
        printf("%s \n", reg[i].campo4);
    }

    printf("\n");
}
