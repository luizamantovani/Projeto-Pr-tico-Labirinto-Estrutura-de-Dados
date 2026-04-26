#include "mochila.h"
#include "pilha.h"

typedef enum Evento{
    NADA,
    TESOURO,
    ARMADILHA
} Evento;

void lerArquivo(char *nomeArquivo);
void mostrarLabirinto();
void procurarPersonagem();
int buscarSaida(int x, int y, Lista *mochila, Pilha *caminho);
void salvarCaminho(char *nomeArquivo, Pilha *caminho);

extern int px, py;
extern char lab[40][40];
extern int linhas, colunas;
extern Evento ultimoEvento;
extern int ultimoValor;

