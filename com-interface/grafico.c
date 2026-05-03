#include "raylib.h"
#include "grafico.h"
#include "labirinto.h"
#include "mochila.h"
#include <stddef.h>
#include <stdio.h>

#define TAM 32

//função que inicia a janela
void iniciarJanela(int largura, int altura){
	InitWindow(colunas * 32 + 180, linhas * 32, "Labirinto 2D");
    SetTargetFPS(60);
}

//função que desenha a mochila a partir de uma lista
void desenharMochila(Lista mochila) {

    int x = colunas * TAM + 20; 
    int y = 20;

    DrawText("Mochila:", x, y, 20, BLACK);
    y += 30;

    Lista aux = mochila; 

    while(aux != NULL) {
        char texto[50];
        sprintf(texto, "%d", aux->valor);

        DrawText(texto, x, y, 20, DARKGREEN);

        y += 25;
        aux = aux->prox;
    }

    int total = calcularTotalMochila(mochila);

    char totalTexto[100];
    sprintf(totalTexto, "Total: %d", total);

    DrawText(totalTexto, x, y + 10, 20, BLACK);
    
}

//função que desenha o ultimo evento que ocorreu (tesouro ou armadilha)
void desenharEvento() {

    int x = colunas * TAM + 20;
    int y = 200;

    if (ultimoEvento == TESOURO) {
        char texto[100];
        sprintf(texto, "TESOURO", ultimoValor);
        DrawText(texto, x, y, 20, GOLD);
    }

    if (ultimoEvento == ARMADILHA) {
        DrawText("ARMADILHA", x, y, 20, RED);
    }
}

//função que desenha a legenda do jogo
void desenharLegenda() {
    int x = colunas * TAM + 10;
    int y = 300;

	if (colunas < 20) {
    	y = 250;
	}

    DrawText("Legenda:", x, y, 20, BLACK);
    DrawText("Verde: Personagem", x, y + 30, 15, GREEN);
    DrawText("Amarelo: Tesouro", x, y + 50, 15, GOLD);
    DrawText("Vermelho: Armadilha", x, y + 70, 15, RED);
    DrawText("Azul: Saida", x, y + 90, 15, BLUE);
}

//função que desenha um erro caso o labirinto não tenha saida
void desenharErroSemSaida(){
	ClearBackground(RED);
	
	int x = colunas * TAM + 20;
	int y = 200;
	
	DrawText("SEM SAIDA", x, y, 20, BLACK);
}

//função que desenha erro se não tiver personagem no labirinto
void desenharSemPersonagem(){
	ClearBackground(RED);
	
	int x = colunas * TAM + 5;
	int y = 200;
	
	DrawText("SEM ", x, y, 20, BLACK);
	DrawText("PERSONAGEM", x, y + 15, 20, BLACK);
}

//função que desenha o labirinto
void desenharLabirinto(){
	for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++) {

            int x = j * TAM;
            int y = i * TAM;

            switch(lab[i][j]) {
                case '#':
                    DrawRectangle(x, y, TAM, TAM, DARKGRAY);
                    break;

                case 'P':
                    DrawRectangle(x, y, TAM, TAM, GREEN);
                    break;

                case 'S':
                    DrawRectangle(x, y, TAM, TAM, BLUE);
                    break;

                case 'T':
                    DrawRectangle(x, y, TAM, TAM, YELLOW);
                    break;

                case 'A':
                    DrawRectangle(x, y, TAM, TAM, RED);
                    break;

                case '.':
                    DrawRectangle(x, y, TAM, TAM, LIGHTGRAY);
                    break;

                default:
                    DrawRectangle(x, y, TAM, TAM, RAYWHITE);
            }
        }
    }
}

//função que desenha a mensagem de encontrar a saida assim que a saida for encontrada
void desenharFinalDoJogo() {

    const char *msg = "ENCONTROU A SAIDA!";
	int fonte = 50;

	if (colunas < 20) {
    	fonte = 40;
	}
	if (colunas < 15) {
    	fonte = 20;
	}
    int largura = colunas * TAM;
    int altura  = linhas * TAM;

    int textWidth = MeasureText(msg, fonte);

    int x = ((largura - textWidth) / 2);
    int y = altura / 2;
    
    
    DrawText(msg, x, y, fonte, GREEN);
}

//função que finaliza a janela do jogo
void finalizarJanela(){
	CloseWindow();
}
