#include "mochila.h"
#include "pilha.h"
#include "labirinto.h"
#include <stdio.h>

int main() {

    // Estruturas principais
    Lista mochila;   // guarda os tesouros coletados
    Pilha caminho;   // guarda o caminho até a saída

    // Inicializa estruturas
    criaMochila(&mochila);
    criaPilha(&caminho); 

    // Lê o labirinto do arquivo
    lerArquivo("labirinto.txt");

    // Mostra o labirinto inicial no terminal
    mostrarLabirinto();

    // Procura o personagem (P)
    int personagem = procurarPersonagem();
	
    // Se não encontrou, encerra o programa
	if(!personagem){
		printf("Nao encontrou o personagem\n");
		return 0;
	}

    // Executa busca pela saída (DFS)
    int r = buscarSaida(px, py, &mochila, &caminho);

    // Verifica resultado
	if(r == 1) {
    	printf("Encontrou saida!\n");

        // Salva caminho encontrado em arquivo
    	salvarCaminho("saida.txt", linhas, colunas, labOriginal, &caminho);

	} else {
    	printf("Nao encontrou saida\n");
	}

    return 0;
}
