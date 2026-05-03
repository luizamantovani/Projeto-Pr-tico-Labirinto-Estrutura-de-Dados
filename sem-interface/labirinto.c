#include <stdio.h>
#include <stdlib.h>
#include "mochila.h"
#include "pilha.h"
#include <windows.h>

char lab[40][40];

char labOriginal[40][40];

int linhas, colunas;

int visitado[40][40];

int px, py;

//função que le o arquivo inicial
void lerArquivo(char *nomeArquivo) {
    FILE *arq = fopen(nomeArquivo, "r");

    if(arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    // Lê dimensões do labirinto
    fscanf(arq, "%d %d", &linhas, &colunas);
    fgetc(arq); // consome quebra de linha

    // Lê o labirinto
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++) {
            lab[i][j] = fgetc(arq);
        }
        fgetc(arq); // consome quebra de linha
    }

    fclose(arq);
}

//função que imprime o labirinto no terminal
void mostrarLabirinto() {
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++) {
            printf("%c", lab[i][j]);
        }
        printf("\n");
    }
}

//função que procura personagem e retorna 1 se encontrou
int procurarPersonagem() {
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++) {
            if(lab[i][j] == 'P'){
                px = i;
                py = j;
                return 1; // encontrou
            }
        }
    }
    return 0; // não encontrou
}

//função que verifica se pode andar
int podeAndar(int x, int y){
    if(x < 0 || y < 0 || x >= linhas || y >= colunas)
        return 0;

    if(lab[x][y] == '#')
        return 0;

    if(visitado[x][y])
        return 0;

    return 1;
}

//função que processa a celula para fazer as interações de tesouro e armadilha
void processarCelula(int x, int y, Lista *mochila){
    if(lab[x][y] == 'T'){
        int valor = rand() % 100 + 1;
        insereMochila(mochila, valor);
        printf("Pegou tesouro: %d\n", valor);
    }

    if(lab[x][y] == 'A'){
        removePrimeiroMochila(mochila, NULL);
        printf("Caiu em armadilha!\n");
    }
}

//função que mostra o labirinto e a mochila no terminal
void mostrarEstado(Lista mochila) {
    system("cls"); // limpa terminal

    mostrarLabirinto();
    mostrarMochila(mochila);

    Sleep(50); // delay para visualização
}

//função que busca saida e se encontrar retorna 1, se não encontrar retorna 0
int buscarSaida(int x, int y, Lista *mochila, Pilha *caminho){

    // se não pode andar, sai
    if(!podeAndar(x, y))
        return 0;

    // encontrou saída
    if(lab[x][y] == 'S'){
        push(caminho, x, y);
        return 1;
    }

    // marca como visitado
    visitado[x][y] = 1;

    // processa eventos da célula
    processarCelula(x, y, mochila);

    // marca visual do caminho
    if(lab[x][y] != 'P' && lab[x][y] != 'S')
        lab[x][y] = '*';

    mostrarEstado(*mochila);

    // adiciona ao caminho
    push(caminho, x, y);

    // tenta as 4 direções 
    if(buscarSaida(x-1, y, mochila, caminho)) return 1;
    if(buscarSaida(x+1, y, mochila, caminho)) return 1;
    if(buscarSaida(x, y-1, mochila, caminho)) return 1;
    if(buscarSaida(x, y+1, mochila, caminho)) return 1;

    // backtracking (remove caminho inválido)
    lab[x][y] = ' ';
    mostrarEstado(*mochila);

    pop(caminho);

    return 0;
}

//função que salva caminho em arquivo
void salvarCaminho(char *nomeArquivo, int linhas, int colunas, char lab[][colunas], Pilha *caminho) {

    FILE *arq = fopen(nomeArquivo, "w");

    if (!arq) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    char copia[linhas][colunas];

    // copia labirinto original
    for (int i = 0; i < linhas; i++)
        for (int j = 0; j < colunas; j++)
            copia[i][j] = lab[i][j];

    // escreve coordenadas e marca caminho
    for (int i = 0; i <= caminho->topo; i++) {
        int x = caminho->dados[i].x;
        int y = caminho->dados[i].y;

        fprintf(arq, "(%d,%d), ", x, y);

        if (copia[x][y] != 'P' && copia[x][y] != 'S')
            copia[x][y] = '*';
    }

    fprintf(arq, "\n");

    // imprime labirinto final
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            fprintf(arq, "%c", copia[i][j]);
        }
        fprintf(arq, "\n");
    }

    fclose(arq);
}
