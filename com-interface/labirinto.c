#include <stdio.h>
#include <stdlib.h>
#include "mochila.h"
#include "pilha.h"
#include "grafico.h"
#include "raylib.h"
#include "labirinto.h"

int visitado[40][40];
int linhas, colunas;
char lab[40][40];
Evento ultimoEvento = NADA;
int ultimoValor = 0;

int px, py; // posição inicial do jogador

int lerArquivo(char *nomeArquivo) {
    FILE *arq = fopen(nomeArquivo, "r");

    if(arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return 1;
        exit(1);
    }

    fscanf(arq, "%d %d", &linhas, &colunas);
    
    if(linhas == 0 || colunas == 0){
    	printf("\nArquivo em branco");
    	return 1;
	}
	
	if (linhas < 0 || colunas < 0 || linhas > 40 || colunas > 40) {
    printf("Erro: dimensoes invalidas!\n");
    return 0;
	}
    fgetc(arq);

    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++) {
            lab[i][j] = fgetc(arq);
        }
        fgetc(arq);
    }
	return 0;
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

int procurarPersonagem() {
	int i, j;
    for(i = 0; i < linhas; i++) {
        for(j = 0; j < colunas; j++) {
            if(lab[i][j] == 'P'){
            	px = i;
            	py = j;
			}
        }
    }
    
    if(px != 0 || py != 0){
    	return 0;
	}
	return 1;
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

Evento processarCelula(int x, int y, Lista *mochila) {
    if (lab[x][y] == 'T') {
        int valor = rand() % 100 + 1;
        insereMochila(mochila, valor);

        ultimoValor = valor;

        printf("Pegou tesouro: %d\n", valor);
        lab[x][y] = ' ';

        return TESOURO;
    }

    if (lab[x][y] == 'A') {
    	if(*mochila == NULL){
		printf("A mochila está vazia!\n");
		}

        if (*mochila != NULL) {
            removePrimeiroMochila(mochila, NULL);
            printf("Caiu em armadilha!\n");
        }

        return ARMADILHA;
    }

    return NADA;
}

void mostrarEstado(Lista mochila) {
    mostrarLabirinto();
    mostrarMochila(mochila);
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

	ultimoEvento = processarCelula(x, y, mochila);

	if(lab[x][y] != 'P' && lab[x][y] != 'S')
    	lab[x][y] = '.';


	BeginDrawing();
	ClearBackground(RAYWHITE);
	desenharLabirinto();
	desenharMochila(*mochila);
	desenharEvento();
	EndDrawing();

	WaitTime(0.1);
		
	push(caminho, x, y);
	
	if(buscarSaida(x-1, y, mochila, caminho)) return 1; //para trás
    if(buscarSaida(x+1, y, mochila, caminho)) return 1;//para frente
    if(buscarSaida(x, y-1, mochila, caminho)) return 1;//para baixo
    if(buscarSaida(x, y+1, mochila, caminho)) return 1;//para cima
    
    if(lab[x][y] != 'P')
    lab[x][y] = ' ';

	BeginDrawing();
	ClearBackground(RAYWHITE);
	desenharLabirinto();
	desenharMochila(*mochila);
	desenharEvento();
	EndDrawing();

	WaitTime(0.1);

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










