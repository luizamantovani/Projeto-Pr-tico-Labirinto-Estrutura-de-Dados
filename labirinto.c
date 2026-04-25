#include <stdio.h>
#include <stdlib.h>
#include "mochila.h"
#include "pilha.h"
#include<windows.h>

char lab[40][40];
int linhas, colunas;

int visitado[40][40];

int px, py; // posição inicial do jogador

void lerArquivo(char *nomeArquivo) {
    FILE *arq = fopen(nomeArquivo, "r");

    if(arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    fscanf(arq, "%d %d", &linhas, &colunas);
    fgetc(arq);

    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++) {
            lab[i][j] = fgetc(arq);
        }
        fgetc(arq);
    }

    fclose(arq);
}

void mostrarLabirinto() {
	int i, j;
    for(i = 0; i < linhas; i++) {
        for(j = 0; j < colunas; j++) {
            printf("%c", lab[i][j]);
        }
        printf("\n");
    }
}

void procurarPersonagem() {
	int i, j;
    for(i = 0; i < linhas; i++) {
        for(j = 0; j < colunas; j++) {
            if(lab[i][j] == 'P'){
            	px = i;
            	py = j;
			}
        }
    }
}

int podeAndar(int x, int y){ //retorna 0 se não pode e 1 se pode
	if(x < 0 || y < 0 || x >= linhas || y >= colunas){
		return 0;
	}
	
	if(lab[x][y] == '#'){
		return 0;
	}
	
	if(visitado[x][y]){
		return 0;
	}
	
	return 1;
}

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

void mostrarEstado(Lista mochila) {
    system("cls");

    mostrarLabirinto();
    mostrarMochila(mochila);

    Sleep(50);
}


int buscarSaida(int x, int y, Lista *mochila, Pilha *caminho){
	if(x < 0 || y < 0 || x >= linhas || y >= colunas){
		return 0;
	}
	
	if(lab[x][y] == '#' || visitado[x][y])
        return 0;
	
	if(lab[x][y] == 'S'){
		push(caminho, x, y);
		return 1;	
	}
	
	visitado[x][y] = 1;
	processarCelula(x, y, mochila);
	lab[x][y] = '.';
	if(lab[x][y] != 'P' && lab[x][y] != 'S')
    	lab[x][y] = '*';
	mostrarEstado(*mochila);
	
	
	
	push(caminho, x, y);
	
	if(buscarSaida(x-1, y, mochila, caminho)) return 1; //para trás
    if(buscarSaida(x+1, y, mochila, caminho)) return 1;//para frente
    if(buscarSaida(x, y-1, mochila, caminho)) return 1;//para baixo
    if(buscarSaida(x, y+1, mochila, caminho)) return 1;//para cima
    
    lab[x][y] = ' '; // limpa caminho
	mostrarEstado(*mochila);

	pop(caminho);
    
    return 0;
}

void salvarCaminho(char *nomeArquivo, Pilha *caminho) {
    FILE *arq = fopen(nomeArquivo, "w");

    for(int i = 0; i <= caminho->topo; i++) {
        fprintf(arq, "(%d,%d)\n",
            caminho->dados[i].x,
            caminho->dados[i].y);
    }

    fclose(arq);
}










