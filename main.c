#include "grafico.h"
#include "labirinto.h"
#include "mochila.h"
#include "pilha.h"
#include "raylib.h"

int main() {

    Lista mochila;
    Pilha pilha;

    criaMochila(&mochila);
    criaPilha(&pilha);

    lerArquivo("labirinto.txt");
    procurarPersonagem();

    iniciarJanela(colunas * 32, linhas * 32);

    int terminou = 0;

	while (!WindowShouldClose()) {

    	BeginDrawing();
    	ClearBackground(RAYWHITE);

    	desenharLabirinto();
    	desenharMochila(mochila);
		desenharEvento();
    	

    	if (!terminou) {
        	terminou = buscarSaida(px, py, &mochila, &pilha);
        	mostrarMochila(mochila);
        	
    	} else if(terminou){
    		desenharFinalDoJogo();
		}
    	
    	EndDrawing();
    	
    	salvarCaminho("saida.txt", &pilha);
	}

    finalizarJanela();
    return 0;
}
