#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>

#define TAM 500

#define LIN 5 //alterar o tamanho da matriz LINHA
#define COL 5 //alterar o tamanho da matriz COLUNA

void legenda(){
    printf("\n Última Esperança Contra a Skynet");
    printf("\n Aluno: Hugo Henrique Marques");
    printf("\n Primeiro periodo de Eng. Computação");
    printf("\n CEFET - MG // Campus - V");
    printf("\n Materia IPC - Prof. Eduardo Habib");
    printf("\n ---------------------------- \n");
    printf("\n Legenda para o programa: \n");
    printf("\n R. Robo Skynet");
    printf("\n H. Humano ");
    printf("\n Z. Zona de Fuga");
    printf("\n *. Caminho que o Humano percorreu");
    printf("\n  . Local livre");
    printf("\n E. END");
    printf("\n Retorno = 1 : Humano Saiu");
    printf("\n Retorno = 0 : Humano não conseguiu escapar");
}

void printMat(char mapa[LIN][COL]){
    printf("\n---------------------\n\n");
        for (int i = 0; i < LIN; i++){ // printa mapa
            printf("\n");
            for (int j = 0; j < COL; j++){
                printf("[ %c ] ", mapa[i][j]);
            }  
        }
        printf("\n\n---------------------\n\n");
}

int podeCaminhar(int x, int y, char matriz[LIN][COL]){ // 0 = NAO PODE / 1 = PODE
    if(x < 0 || x == LIN || y < 0 || y == COL){ // verifica se vai sair do mapa
        return 0;
    }
    if(matriz[x][y] == '*'){// verifica se o proximo caminho ja foi explorado
        return 2;
    }
    if(matriz[x][y] == 'R'){ // verifica se o proximo caminho é robo
        return 0;
    }
    if(matriz[x][y] == 'x'){ // verifica se o proximo caminho é robo
        return 0;
    }
    return 1;
}

int caminhar(int* xH, int* yH, int* xZ, int* yZ, char (*matriz)[LIN][COL], char direcao){
    if(direcao == 'c'){
        if(podeCaminhar((*xH)-1, (*yH), (*matriz)) == 1) {
            (*matriz)[(*xH)][(*yH)] = '*';
            (*matriz)[(*xH)-1][(*yH)] = 'H';
            (*xH) = (*xH)-1;
            return 1;
        }
        
    }
    else if(direcao == 'd'){
        if(podeCaminhar((*xH), (*yH)+1, (*matriz)) == 1) {
            (*matriz)[(*xH)][(*yH)] = '*';
            (*matriz)[(*xH)][(*yH)+1] = 'H';
            (*yH) = (*yH)+1;
            return 1;
        }
        
    }
    
    else if(direcao == 'b'){
        if(podeCaminhar((*xH)+1, (*yH), (*matriz)) == 1) {
            (*matriz)[(*xH)][(*yH)] = '*';
            (*matriz)[(*xH)+1][(*yH)] = 'H';
            (*xH) = (*xH)+1;
            return 1;
        }
        
    }
    
    else if(direcao == 'e'){
        if(podeCaminhar((*xH), (*yH)-1, (*matriz)) == 1) {
            (*matriz)[(*xH)][(*yH)] = '*';
            (*matriz)[(*xH)][(*yH)-1] = 'H';
            (*yH) = (*yH)-1;
            return 1;
        }
        
    }

    return 0;
}

int voltaCasa(int* xH, int* yH, int* xZ, int* yZ, char (*matriz)[LIN][COL], char direcao){
     if(direcao == 'c'){
        if(podeCaminhar((*xH)+1, (*yH), (*matriz)) == 2) {
            (*matriz)[(*xH)][(*yH)] = 'x';
            (*matriz)[(*xH)+1][(*yH)] = 'H';
            (*xH) = (*xH)+1;
            return 1;
        }
    }
    else if(direcao == 'd'){
        if(podeCaminhar((*xH), (*yH)-1, (*matriz)) == 2) {
            (*matriz)[(*xH)][(*yH)] = 'x';
            (*matriz)[(*xH)][(*yH)-1] = 'H';
            (*yH) = (*yH)-1;
            return 1;
        }
    }
    else if(direcao == 'b'){
        if(podeCaminhar((*xH)-1, (*yH), (*matriz)) == 2) {
            (*matriz)[(*xH)][(*yH)] = 'x';
            (*matriz)[(*xH)-1][(*yH)] = 'H';
            (*xH) = (*xH)-1;
            return 1;
        }
    }
    else if(direcao == 'e'){
        if(podeCaminhar((*xH), (*yH)+1, (*matriz)) == 2) {
            (*matriz)[(*xH)][(*yH)] = 'x';
            (*matriz)[(*xH)][(*yH)+1] = 'H';
            (*yH) = (*yH)+1;
            return 1;
        }
    }

    return 0;
}

void encontrarCoordenasHumanoZona(int* xHumano, int* yHumano, int* xZona, int* yZona, char matriz[LIN][COL]){
    for (int i = 0; i < LIN; i++){ // encontra zona dentro da matriz
        for (int j = 0; j < COL; j++){
            if ('H' == matriz[i][j]){
                *xHumano = i;
                *yHumano = j;
            }
              if ('Z' == matriz[i][j]){
                *xZona = i;
                *yZona = j;
            }
        }
    }
}

char mostrarZ(int xHumano, int yHumano, int xZona, int yZona){
    if (xZona < xHumano){
        return 'c';
    }else if (yZona > yHumano){
        return 'd';
    }else if (xZona > xHumano){
        return 'b';
    }
    return 'e';
}

int main(){

    legenda();

    int saiu = 1;


    setlocale(LC_ALL,"Portuguese");
    char mapa[LIN][COL] = {// Local para inserir a matriz
        {' ', 'R', 'R', 'R', 'Z'},
        {' ', ' ', ' ', 'R', ' '},
        {'R', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', 'R', ' '},
        {' ', 'R', 'H', 'R', ' '}
    };

    int xHumano = 0, yHumano = 0 , xZona = 0, yZona = 0;
    encontrarCoordenasHumanoZona(&xHumano, &yHumano, &xZona, &yZona, mapa);

    printMat(mapa);

    do{
        switch (mostrarZ(xHumano, yHumano, xZona, yZona)){
            case 'c': {
                    if(caminhar(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'c') == 0){
                        if(caminhar(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'd') == 0){
                            if(caminhar(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'b') == 0){
                                if(caminhar(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'e') == 0){
                                    //-----------------------------------------------------------------------
                                    //VOLta CASA
                                    if(voltaCasa(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'c') == 0){
                                        if(voltaCasa(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'd') == 0){
                                            if(voltaCasa(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'b') == 0){
                                                if(voltaCasa(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'e') == 0){
                                                    saiu = 0;
                                                    printMat(mapa);
                                                    printf("\n Não tem caminho, retorno: %d \n", saiu);
                                                    exit(1);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        } 
                    }
                break;
            }
            case 'd': {
                    if(caminhar(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'd') == 0){
                        if(caminhar(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'b') == 0){
                            if(caminhar(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'e') == 0){
                                if(caminhar(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'c') == 0){
                                    //-----------------------------------------------------------------------
                                    //VOLta CASA
                                    if(voltaCasa(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'd') == 0){
                                        if(voltaCasa(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'b') == 0){
                                            if(voltaCasa(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'e') == 0){
                                                if(voltaCasa(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'c') == 0){
                                                    saiu = 0;
                                                    printMat(mapa);
                                                    printf("\n Não tem caminho, retorno: %d\n", saiu);
                                                    exit(1);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        } 
                    }
                break;
            }
            case 'b':{
                if(caminhar(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'b') == 0){
                    if(caminhar(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'e') == 0){
                        if(caminhar(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'c') == 0){
                            if(caminhar(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'd') == 0){
                                //-----------------------------------------------------------------------
                                    //VOLta CASA
                                if(voltaCasa(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'b') == 0){
                                    if(voltaCasa(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'e') == 0){
                                        if(voltaCasa(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'c') == 0){
                                            if(voltaCasa(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'd') == 0){
                                                saiu = 0;
                                                printMat(mapa);
                                                printf("\n Não tem caminho, retorno: %d \n", saiu);
                                                exit(1);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } 
                }
                break;
            }
            case 'e':{
                if(caminhar(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'e') == 0){
                    if(caminhar(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'c') == 0){
                        if(caminhar(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'd') == 0){
                            if(caminhar(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'b') == 0){
                                //-----------------------------------------------------------------------
                                //VOLta CASA
                                if(voltaCasa(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'e') == 0){
                                    if(voltaCasa(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'c') == 0){
                                        if(voltaCasa(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'd') == 0){
                                            if(voltaCasa(&xHumano, &yHumano, &xZona, &yZona, &mapa, 'b') == 0){
                                                saiu = 0;
                                                printMat(mapa);
                                                printf("Não tem caminho, retorno: %d \n", saiu);
                                                exit(1);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } 
                }
                break;
            }  
        }
        
        //printMat(mapa);

    } while ((xHumano != xZona) || (yHumano != yZona));

    for (int i = 0; i < LIN; i++){
        for (int j = 0; j < COL; j++){
            if (mapa[i][j] == 'H'){
                mapa[i][j] = 'E';
            }   
            if (mapa[i][j] == 'x'){
                mapa[i][j] = ' ';
            }          
        }
    }

    printMat(mapa);
    
    printf("Caminho Encontrado, retorno: %d \n\n", saiu);

    return 0;
}