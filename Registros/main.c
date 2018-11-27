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


void criarBinario(int n, REGISTRO* reg, char nomeArquivo[30]);
void lerBinario(REGISTRO* salvar, char nomeArquivo[30]);

void swopPlaces(REGISTRO *reg, int pont2, int pont1);

void organizarArquivos(REGISTRO *reg, int inicio, int fim, int n);
void orgPart1(REGISTRO* regis, int inicio, int fim);
void orgPart2(REGISTRO *reg, int num, int campoNum);
void orgPart3(REGISTRO* regis, int inicio, int fim, int campoNum);



//void orgPart2(REGISTRO *reg, int n);
//void orgPart3(REGISTRO* regis, int inicio, int fim);

int main(){

    int numeroDaFuncao;

    scanf("%d", &numeroDaFuncao);

    if(numeroDaFuncao == 1){
        char nomeArquivo[30];
        int n;
        scanf("%s %d", nomeArquivo, &n);
        REGISTRO *reg = (REGISTRO*)malloc(n*sizeof(REGISTRO));
        criarRegistro(n, reg);
        criarBinario(n, reg, nomeArquivo);
        free(reg);
    }

    if(numeroDaFuncao == 2){
        char nomeArquivo[30];
        scanf("%s", nomeArquivo);
        FILE* fp;
        fp = fopen(nomeArquivo, "rb");

        if ( fp == NULL ){
                printf( "Arquivo vazio.\n" );
                exit(1);
        }
        else{
            fseek(fp, 0L, SEEK_END);
            int tamTotal = ftell(fp);
            int n = tamTotal/64;
            REGISTRO *reg = (REGISTRO*)malloc(n*sizeof(REGISTRO));
            lerBinario(reg, nomeArquivo);
            mostrarRegistros(n, reg);
            free(reg);
        }
    }

    if(numeroDaFuncao == 3){
        char nomeArquivo[30];
        char nomeArquivoFinal[30];
        scanf("%s %s", nomeArquivo, nomeArquivoFinal);
        FILE* fp;
        fp = fopen(nomeArquivo, "rb");

        if ( fp == NULL ){
                printf( "Arquivo vazio.\n" );
                exit(1);
        }
        else{
            fseek(fp, 0L, SEEK_END);
            int tamTotal = ftell(fp);
            int n = tamTotal/64;
            REGISTRO *reg = (REGISTRO*)malloc(n*sizeof(REGISTRO));
            lerBinario(reg, nomeArquivo);
            organizarArquivos(reg,0,n-1,n);
            criarBinario(n,reg,nomeArquivoFinal);
            free(reg);
        }

    }


    return  0;
}

// ***************************************** FUNCIONALIDADE 1 *****************************************************


/*

Ainda estou usando string genericas nos campos 1 e 2, mas a ideia é substituir
isso por algo que realmente nomeie o nome de start ups e suas areas de atuação

*/

void mostrarRegistros(int n, REGISTRO* reg){

    for(int i = 0; i<n; i++){
        printf("%d |", reg[i].campo1);
        printf(" %s |", reg[i].campo2);
        printf(" %s |", reg[i].campo3);
        printf(" %.10s \n", reg[i].campo4);
    }

    printf("\n");
}


int geradorDeNumerosAleatorios(int lower, int upper){
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;

}

void criarRegistro(int n, REGISTRO* reg){

    char campo2valor1[22][9] = {"UBER","AIRBNB","CYBER","OPEN","CROWD","UDEMY","DUO","FLEX","STONE","QUINTO","TELEGRAM","SHELBY","GENERAL","DROP","RUBRIK","FLUKE","NU","ARQUIVEI","IFOOD","WE","WAVY","GIT"};
    char campo2valor2[24][10] = {"LINGO","SECURIT","NETWORK","BOX","ONLINE","MAIL","WORK","SLACK","PREZY","GIPHY","COMPUTER","CLOUD","TRADES","COMMERCE","CLOUD","BUFFER","LABS","HUB","LISTS","CHAT","PAYMENT","TINDER","BANK"};
    char campo2valor3[20][9] = {"DATA","BASE","MODE",".ME","MATCH","LOCAL","VIEW","LTDA","FINDER","GRID","DIGITAL","RANK","STORE","FITNESS","NOW","CHAT","APP","BRANDS","EDUCATION","GAMES"};
    char campo3valor1[22][12] = {"NUVEM","LAZER","TELEFONIA","MOBILIDADE","ENSINO","SOCIAL","VENDAS","MENSAGENS","HOSPEDAGEM","BANCARIO","HARDWARE","SOFTWARE","ADM","SEGURANCA","FINANCA","TURISMO","LOCALIZACAO","ARMAZEN","COACHING"};
    char campo3valor2[28][4] = {"BRA","USA","ITA","FRA","GRA","FIL","CHI","RUS","AUG","EC!","ARM","EGT","GMA","IND","IND","JPO","JMK","SKO","POR","LYS","CHL","GER","SAF","MEX","ESP","SZH","ISR","CAN"};

    for(int i = 0; i<n; i++){ //Geração do campo1 (valor de mercado), onde gera um valor aleatorio correspondente num intervalo de 1000000 e 100000000
        if(i<0.7*n){
            reg[i].campo1 = geradorDeNumerosAleatorios(MIN, MAX);
        }
        else{ //todos os elses servirão para configurar as repetições esperadas (aqueles 30%, 25%, 20% e 15% de repetição)
            reg[i].campo1 = reg[geradorDeNumerosAleatorios(0, 0.7*n)].campo1;
        }
    }

    for(int i = 0; i<n; i++){
        if(i<0.75*n){
            sprintf(reg[i].campo2,"%s %s %s", campo2valor1[geradorDeNumerosAleatorios(0,21)], campo2valor2[geradorDeNumerosAleatorios(0,21)], campo2valor3[geradorDeNumerosAleatorios(0,19)]);//essa função serve para se escrever dentro de uma string
        }
        else{
            strcpy(reg[i].campo2, reg[geradorDeNumerosAleatorios(0,0.75*n)].campo2); //essa funcao serve para copiar a segunda string no final da primeira string
        }
    }

    for(int i = 0; i<n; i++){
        if(i<0.80*n){
            sprintf(reg[i].campo3, "%s %s", campo3valor1[geradorDeNumerosAleatorios(0,17)], campo3valor2[geradorDeNumerosAleatorios(0,27)]);
        }
        else{
            strcpy(reg[i].campo3, reg[geradorDeNumerosAleatorios(0,0.8*n)].campo3);
        }
    }

    for(int i =0; i<n; i++){
        if(i<0.85*n){
            strcpy(reg[i].campo4,"");
            geradorDeDatas(&reg[i].campo4); // chama uma função que gera datas de acordo com a necessidade
        }
        else{
            strcpy(reg[i].campo4,reg[geradorDeNumerosAleatorios(0,0.85*n)].campo4);
        }
    }
}

void geradorDeDatas(char *dataFinal){

	// Para evitar o calculo complexo de anos bissextos, usamos os dias até o numero 28

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


// ***************************************** FUNCIONALIDADE 2 *****************************************************

/*

A segunda funcionalidade basicamente escreve um ponteiro de registros que ja foi criado
na main.c e também já possui os dados em seu interior (ou seja, ja passou pela função gerarRegistro)

*/

//Caso seja necessario criar mais de um binario, basta chamar ela usando registros diferentes e arquivos diferentes (ex: file2.bin, file3.bin e etc)

void criarBinario(int n, REGISTRO* reg, char nomeArquivo[30]){
     FILE *binaryFile;
     binaryFile = fopen(nomeArquivo, "wb"); //aqui deve ser defino em qual arquivo sera feita a leitura e escrita binaria

    if (binaryFile != NULL){
        for(int i = 0;i<n;i++){
            fwrite(&reg[i].campo1, sizeof(int),1,binaryFile);
            fwrite(&reg[i].campo2, 30,1,binaryFile);
            fwrite(&reg[i].campo3, 20,1,binaryFile);
            fwrite(&reg[i].campo4, 10,1,binaryFile);
        }
        printf("Arquivo gerado");
    }

    else{
        printf("Falha no Processamento");
    }

    fclose(binaryFile);
}

/*

Essa função aqui basicamente ira selecionar um arquivo binario que foi criado (ex arquivo.bin)
e ira ler seu contudo. Importante frizar que nosso registro possui tamanho 65 e não 64, devido a insuficiencia
do tamanho de nosso quarto campo. Essa escolha foi feita pois acaba por


*/

void lerBinario(REGISTRO *salvar, char nomeArquivo[30]){ //Essa função ira carregar o arquivo binario para dentro de do ponteiro REGISTRO oferecido como paramentro
    FILE *binaryFile;
    binaryFile = fopen(nomeArquivo, "rb");
    int i = 0;

    if(binaryFile != NULL){

        while(fread(&salvar[i],64, 1, binaryFile) != 0){
            //printf("%d %s %s %s\n", salvar[i].campo1, salvar[i].campo2, salvar[i].campo3, salvar[i].campo4);
            i++;
        }

        //printf("\n");
        fclose(binaryFile);
    }
}

// ***************************************** FUNCIONALIDADE 3 *****************************************************

/*

Abaixo o método de ordenação que encontra-se implementado é o quicksort

Uso interno: Foi bem complicado fazer com que ele funcionasse, então não vou explicar ele aqui nos comentarios.
A única coisa que precisa ficar clara para seu uso é sua chamada principal --> organizarArquivos(REGISTRO* reg, int inicio, int fim, int n)

reg -> o registro que voce criou e trabalhou na main
inicio -> entrar com "0"
fim-> entrar com "n-1"
n-> numero de registros "n"

*/

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

