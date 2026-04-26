typedef struct No {
	int valor;
	struct No *prox;
} No;

typedef No *Lista;

void criaMochila(Lista *p);

void insereMochila(Lista *p, int valor);

void removePrimeiroMochila(Lista *p, int *p_valor);

void mostrarMochila(Lista p);

int calcularTotalMochila(Lista mochila);
