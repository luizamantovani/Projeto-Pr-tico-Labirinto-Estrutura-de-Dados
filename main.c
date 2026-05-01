#include "grafico.h"
#include "labirinto.h"
#include "mochila.h"
#include "pilha.h"
#include "raylib.h"
#include<stdio.h>

int main() {

    Lista mochila;
    Pilha pilha;

    criaMochila(&mochila);
    criaPilha(&pilha);

    int abriuArquivo = lerArquivo("labirinto.txt");
    
    if(abriuArquivo == 1){
    	return 1;
	}
    int encontrouPersonagem = procurarPersonagem();

    iniciarJanela(colunas * 32, linhas * 32);

    int terminou = 0;
    int encontrou = 0;

	while (!WindowShouldClose()) {

    	BeginDrawing();
    	ClearBackground(RAYWHITE);
    	
    	desenharLabirinto();
    	desenharMochila(mochila);
    	desenharEvento();
		
    	if (!terminou) {
        	encontrou = buscarSaida(px, py, &mochila, &pilha);
        	terminou = 1;

        	mostrarMochila(mochila);

        	if (!encontrou) {
            	printf("Nao encontrou saida!\n");
        	}
    	}

    	if (terminou && encontrou) {
        	desenharFinalDoJogo();
    	}


    	if (terminou && !encontrou) {
        	desenharErroSemSaida();
    	}

    	EndDrawing();
	}

    finalizarJanela();
    return 0;
}
