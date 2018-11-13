#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100000
#define MIN 1000

typedef struct reg REGISTRO;
void geradorDeDatas();
int geradorDeNumerosAleatorios(int lower, int upper);
void criarRegistro(int n, REGISTRO* reg);
void criarBinario(int n, REGISTRO* reg);
void mostrarRegistros(int n, REGISTRO* reg);
void swopPlaces(REGISTRO *reg, int pont2, int pont1);
void organizarArquivos(REGISTRO* regis, int inicio, int fim);
void lerBinario();

typedef struct reg{

    int campo1;
    char campo2[30];
    char campo3[20];
    char campo4[11];

}REGISTRO;// Caso sobre um tempo, seria interessante juntarmos todos os campos em formator de REGISTRO atraves de uma struct

int main()
{
    int n;

    printf("Quantos registros deseja imprimir?: ");
    scanf("%d",&n);

    REGISTRO *regis = (REGISTRO*)malloc(n*sizeof(REGISTRO));

    srand(time(0));

    criarRegistro(n, regis);

    mostrarRegistros(n,regis);

    organizarArquivos(regis,0,n);

    mostrarRegistros(n,regis);

    //mostrarRegistros(n,regis);

    //criarBinario(n, regis);

    //lerBinario();

    free(regis);

    return  0;
}

int geradorDeNumerosAleatorios(int lower, int upper){
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

void criarRegistro(int n, REGISTRO* reg){

    for(int i = 0; i<n; i++){ //Geração do campo1 (valor de mercado), onde gera um valor aleatorio correspondente num intervalo de 1000000 e 100000000
        if(i<0.7*n){
            reg[i].campo1 = geradorDeNumerosAleatorios(MIN, MAX)*1000;
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

void criarBinario(int n, REGISTRO* reg){
     FILE *binaryFile;
     binaryFile = fopen("file.bin", "wb");

    if (binaryFile != NULL){
        for(int i = 0;i<n;i++){
            fwrite(&reg[i].campo1, sizeof(int),1,binaryFile);
            fwrite(&reg[i].campo2, 30,1,binaryFile);
            fwrite(&reg[i].campo3, 20,1,binaryFile);
            fwrite(&reg[i].campo4, 11,1,binaryFile);
        }
    }

    else{
        printf("unable to open");
    }

    fclose(binaryFile);
}

void lerBinario(){
    FILE *binaryFile;
    binaryFile = fopen("file.bin", "rb");
    REGISTRO salvar;

    if(binaryFile != NULL){

        while(fread(&salvar,65, 1, binaryFile) != 0){
            printf("%d %s %s %s\n", salvar.campo1, salvar.campo2, salvar.campo3, salvar.campo4);
        }
        fclose(binaryFile);
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

void organizarArquivos(REGISTRO* regis, int inicio, int fim){

    int pivot=fim;
    int pont1=inicio;
    int pont2=inicio;

    if(fim-inicio > 0){
        while(pont2 != pivot){
        if(regis[pont2].campo1<=regis[pivot].campo1){
            swopPlaces(regis, pont2, pont1);
            pont2++;
            pont1++;

        }
        else{
            pont2++;
        }
    }

    swopPlaces(regis, pivot, pont1);

    pivot = pont1;

    organizarArquivos(regis,inicio, pivot-1);
    organizarArquivos(regis,pivot, fim);

    }
}

void swopPlaces(REGISTRO *reg, int pont2, int pont1){
    REGISTRO aux;

    aux = reg[pont1];
    reg[pont1] = reg[pont2];
    reg[pont2] = aux;

}

