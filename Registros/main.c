#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 50000
#define MIN 1


typedef struct reg{

    int campo1;
    char campo2[30];
    char campo3[20];
    char campo4[11];

}REGISTRO;// Caso sobre um tempo, seria interessante juntarmos todos os campos em formator de REGISTRO atraves de uma struct

void geradorDeDatas();
int geradorDeNumerosAleatorios(int lower, int upper);
void criarRegistro(int n, REGISTRO* reg);
void mostrarRegistros(int n, REGISTRO* reg);


void criarBinario(int n, REGISTRO* reg);
void lerBinario();

void swopPlaces(REGISTRO *reg, int pont2, int pont1);

void organizarArquivos(REGISTRO *reg, int inicio, int fim, int n);
void orgPart1(REGISTRO* regis, int inicio, int fim);
void orgPart2(REGISTRO *reg, int num, int campoNum);
void orgPart3(REGISTRO* regis, int inicio, int fim, int campoNum);



//void orgPart2(REGISTRO *reg, int n);
//void orgPart3(REGISTRO* regis, int inicio, int fim);

int main(){
    int n;

    printf("Quantos registros deseja imprimir?: ");
    scanf("%d",&n);

    REGISTRO *regis = (REGISTRO*)malloc(n*sizeof(REGISTRO));

    srand(time(0));

    criarRegistro(n, regis);

    mostrarRegistros(n,regis);

    organizarArquivos(regis,0,n-1,n);

    mostrarRegistros(n,regis);

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

    char dias[30][3] = {"01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28"};
    char meses[13][3] = {"01","02","03","04","05","06","07","08","09","10","11","12"};

    char dia[3];
    sprintf(dia, "%s", dias[geradorDeNumerosAleatorios(0, 27)]);

    char mes[3];
    sprintf(mes, "%s", meses[geradorDeNumerosAleatorios(0,11)]);


    int ano = geradorDeNumerosAleatorios(1996, 2017);

    char vetorAux[12];

    sprintf(vetorAux,"%s/", dia);
    strcat(dataFinal, vetorAux);

    sprintf(vetorAux,"%s/", mes);
    strcat(dataFinal, vetorAux);

    sprintf(vetorAux,"%d", ano);
    strcat(dataFinal, vetorAux);
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

void mostrarRegistros(int n, REGISTRO* reg){

    for(int i = 0; i<n; i++){
        printf("%d ", reg[i].campo1);
        printf("%s ", reg[i].campo2);
        printf("%s ", reg[i].campo3);
        printf("%s \n", reg[i].campo4);
    }

    printf("\n");
}

void organizarArquivos(REGISTRO *reg, int inicio, int fim, int n){

    orgPart1(reg, inicio, fim);
    orgPart2(reg, n, 2);
    orgPart2(reg, n, 3);
    orgPart2(reg, n, 4);

}

void orgPart1(REGISTRO* regis, int inicio, int fim){

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

        orgPart1(regis,inicio, pivot-1);
        orgPart1(regis,pivot+1, fim);

    }
}

void orgPart2(REGISTRO *reg, int num, int campoNum){
    int pont1 = 0;
    int pont2 = 1;



    while(1){
        if(pont2 < num){

            if(campoNum == 2){
               if(reg[pont1].campo1 == reg[pont2].campo1){
                    pont2 ++;
                }
                else{
                    orgPart3(reg, pont1, pont2-1, campoNum);
                    pont1 = pont2;
                    pont2 ++;
                }
            }

            if(campoNum == 3){
               if(reg[pont1].campo2[0] == reg[pont2].campo2[0]){
                    pont2 ++;
                }
                else{
                    orgPart3(reg, pont1, pont2-1, campoNum);
                    pont1 = pont2;
                    pont2 ++;
                }
            }

            if(campoNum == 4){
               if(reg[pont1].campo3[0] == reg[pont2].campo3[0]){
                    pont2 ++;
                }
                else{
                    orgPart3(reg, pont1, pont2-1, campoNum);
                    pont1 = pont2;
                    pont2 ++;
                }
            }

        }
        else{
            break;
        }
    }
}

void orgPart3(REGISTRO* regis, int inicio, int fim, int campoNum){


    int pivot=fim;
    int pont1=inicio;
    int pont2=inicio;
    int i = 0;

    if(fim-inicio > 0){
        while(pont2 != pivot){
            i = 0;
            if(campoNum == 2){

             while(1){
                char a = regis[pont2].campo2[i];
                char b = regis[pivot].campo2[i];

                //printf("pont2: %c e pivot: %c \n", a, b);

                if(a == b){
                    i++;
                }
                else{
                    break;
                }

            }
                if((int)regis[pont2].campo2[i]<=(int)regis[pivot].campo2[i]){
                    swopPlaces(regis, pont2, pont1);
                    pont2++;
                    pont1++;

                }
                else{
                    pont2++;
                }
            }

            if(campoNum == 3){

             while(1){
                char a = regis[pont2].campo3[i];
                char b = regis[pivot].campo3[i];

                //printf("pont2: %c e pivot: %c \n", a, b);

                if(a == b){
                    i++;
                }
                else{
                    break;
                }

            }
                if((int)regis[pont2].campo3[i]<=(int)regis[pivot].campo3[i]){
                    printf("aqui \n");
                    swopPlaces(regis, pont2, pont1);
                    pont2++;
                    pont1++;

                }
                else{
                    pont2++;
                }
            }



            if(campoNum == 4){

             while(1){
                char a = regis[pont2].campo4[i];
                char b = regis[pivot].campo4[i];

                //printf("pont2: %c e pivot: %c \n", a, b);

                if(a == b){
                    i++;
                }
                else{
                    break;
                }

            }
                if((int)regis[pont2].campo4[i]<=(int)regis[pivot].campo4[i]){
                    printf("aqui \n");
                    swopPlaces(regis, pont2, pont1);
                    pont2++;
                    pont1++;

                }
                else{
                    pont2++;
                }
            }
        }

        swopPlaces(regis, pivot, pont1);

        pivot = pont1;

        orgPart3(regis,inicio, pivot-1, campoNum);
        orgPart3(regis,pivot+1, fim, campoNum);

    }

}


void swopPlaces(REGISTRO *reg, int pont2, int pont1){
    REGISTRO aux;

    aux = reg[pont1];
    reg[pont1] = reg[pont2];
    reg[pont2] = aux;

}

