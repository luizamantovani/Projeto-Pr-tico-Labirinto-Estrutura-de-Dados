//Guarda o caminho do personagem

typedef struct {
	int x, y;
} Posicao;

typedef struct {
	int topo;
	Posicao dados[1600]; //40x40
} Pilha;

void criaPilha(Pilha *p);
void push(Pilha *p, int x, int y);
void pop(Pilha *p);
Posicao topoPilha(Pilha *p);
int pilhaVazia(Pilha *p);
