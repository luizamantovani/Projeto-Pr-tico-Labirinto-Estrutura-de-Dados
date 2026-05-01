extern int px, py;
extern int linhas, colunas;
extern char lab[40][40];
extern char labOriginal[40][40];

void lerArquivo(char *nomeArquivo);
void mostrarLabirinto();
int procurarPersonagem();
int buscarSaida(int x, int y, Lista *mochila, Pilha *caminho);
void salvarCaminho(char *nomeArquivo, int linhas, int colunas, char lab[][colunas], Pilha *caminho);


