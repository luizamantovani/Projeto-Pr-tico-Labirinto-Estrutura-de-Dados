#include "mochila.h"
#include "pilha.h"
#include "labirinto.h"
#include<stdio.h>

int main() {
    Lista mochila;
    Pilha caminho;
    criaMochila(&mochila);

    lerArquivo("labirinto.txt");
    mostrarLabirinto();
    int personagem = procurarPersonagem();
	
	if(!personagem){
		printf("Nao encontrou o personagem\n");
		return 0;
	}
    int r = buscarSaida(px, py, &mochila, &caminho);


	if(r == 1) {
    	printf("Encontrou saida!\n");
    	salvarCaminho("saida.txt",linhas, colunas, labOriginal, &caminho);
	} else {
    	printf("Nao encontrou saida\n");
	}

    return 0;
}
