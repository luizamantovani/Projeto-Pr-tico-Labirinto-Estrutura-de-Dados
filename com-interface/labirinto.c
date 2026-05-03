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
char labOriginal[40][40];
Evento ultimoEvento = NADA;
int ultimoValor = 0;

int px, py; // posição inicial do jogador

//função que lê o arquivo e retorna 1 se tiver algum erro e 0 se der certo
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
    
    fclose(arq);
	return 0;
    
}

//função que procura o personagem no labirinto e retorna 1 se encontrar e 0 se não encontrar
int procurarPersonagem() {
	int i, j;
    for(i = 0; i < linhas; i++) {
        for(j = 0; j < colunas; j++) {
            if(lab[i][j] == 'P'){
            	px = i;
            	py = j;
            	return 1;
			}
        }
    }
    return 0;
}

//função que verifica se a célula atual é alguma célula especial (A, S, T) e retorna o evento em questão
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

//função que utiliza o algoritmo de backtracking para encontrar a saída, retorna 0 se não encontrou e 1 se encontrou
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
	desenharLegenda();
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
	desenharLegenda();
	desenharMochila(*mochila);
	desenharEvento();
	EndDrawing();

	WaitTime(0.1);

	pop(caminho);
    
    return 0;
}

//função que salva as coordenadas do caminho e o caminho em si em um arquivo
void salvarCaminho(char *nomeArquivo, int linhas, int colunas, char lab[][colunas], Pilha *caminho) {
    FILE *arq = fopen(nomeArquivo, "w");

    if (!arq) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    char copia[linhas][colunas];
	   
    // copia labirinto
    for (int i = 0; i < linhas; i++)
        for (int j = 0; j < colunas; j++){
        	 copia[i][j] = lab[i][j];
		}
            

    // marca caminho
    fprintf(arq, "Coordenadas para encontrar a saída: ");
    for (int i = 0; i <= caminho->topo; i++) {
        int x = caminho->dados[i].x;
        int y = caminho->dados[i].y;

        fprintf(arq, "(%d,%d), ", //imprime as coordenadas antes de imprimir o caminho do labirinto
            caminho->dados[i].x,
            caminho->dados[i].y);
		
        if (copia[x][y] != 'P' && copia[x][y] != 'S')
            copia[x][y] = '*';
    }
    
    fprintf(arq, "\n"); //pula linha antes de gerar labirinto com saida 

    // salva exatamente como o labirinto
    fprintf(arq, "Caminho: ");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            fprintf(arq, "%c", copia[i][j]);
        }
        fprintf(arq, "\n");
    }

    fclose(arq);
}










