#include "grafico.h"
#include "labirinto.h"
#include "mochila.h"
#include "pilha.h"
#include "raylib.h"
#include<stdio.h>

int main() {

    // Estruturas principais do jogo
    Lista mochila;   // guarda os tesouros coletados
    Pilha pilha;     // guarda o caminho encontrado até a saída

    criaMochila(&mochila);
    criaPilha(&pilha);

    // Leitura do arquivo do labirinto
    int abriuArquivo = lerArquivo("labirinto.txt");
    
    // Se deu erro ao abrir, encerra o programa
    if(abriuArquivo == 1){
        return 1;
    }

    // Procura a posição inicial do personagem (P)
    int encontrouPersonagem = procurarPersonagem();

    // Inicializa janela gráfica (raylib)
    iniciarJanela(colunas * 32, linhas * 32);
    
    // Controle de estado do jogo
    int terminou = 0;   // indica se a busca já foi executada
    int encontrou = 0;  // indica se encontrou a saída

    // Loop principal do jogo (renderização contínua)
    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Desenha o labirinto atual
        desenharLabirinto();    

        // Caso não exista personagem no mapa
        if (!encontrouPersonagem) {
            desenharSemPersonagem(); // mostra mensagem de erro
            EndDrawing();
            continue; // pula o restante do loop
        }

        // Desenha interface lateral
        desenharMochila(mochila);  // itens coletados
        desenharEvento();          // último evento (tesouro/armadilha)
        desenharLegenda();         // legenda das cores

        // Executa a busca apenas uma vez
        if (!terminou) {
            encontrou = buscarSaida(px, py, &mochila, &pilha);
            terminou = 1;

            // Mostra conteúdo da mochila no terminal
            mostrarMochila(mochila);

            // Caso não encontre saída
            if (!encontrou) {
                printf("Nao encontrou saida!\n");
            }
        }

        // Caso tenha encontrado a saída
        if (terminou && encontrou) {
            desenharFinalDoJogo(); // mensagem na tela

            // Salva o caminho encontrado no arquivo
            salvarCaminho("saida.txt", linhas, colunas, labOriginal, &pilha);
        }

        // Caso não tenha saída
        if (terminou && !encontrou) {
            desenharErroSemSaida();
        }

        EndDrawing();
    }

    // Finaliza janela gráfica
    finalizarJanela();

    return 0;
}
