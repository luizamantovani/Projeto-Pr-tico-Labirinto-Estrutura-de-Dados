#include "mochila.h"
#include "pilha.h"

typedef enum Evento{
    NADA,
    TESOURO,
    ARMADILHA
} Evento;

extern int px, py;
extern char lab[40][40];
extern char labOriginal[40][40];
extern int linhas, colunas;
extern Evento ultimoEvento;
extern int ultimoValor;


int lerArquivo(char *nomeArquivo);
void mostrarLabirinto();
int procurarPersonagem();
int buscarSaida(int x, int y, Lista *mochila, Pilha *caminho);
void salvarCaminho(char *nomeArquivo, int linhas, int colunas, char lab[][colunas], Pilha *caminho);


