#include<stdio.h>
#include <stdlib.h>
#include "mochila.h"

void criaMochila(Lista *p){
	*p = NULL;
}

void insereMochila(Lista *p, int valor){
	No *novo = malloc(sizeof(No));
	novo->valor = valor;
	novo->prox = NULL;
	
	if(*p == NULL || valor < (*p)->valor){ // se for o primeiro elemento da lista ou se o valor a ser inserido for menor que o primeiro elemento - insere na primeira posição
		novo->prox = *p;
		*p = novo;
		return;		
	}
	
	No *atual = *p;
	
	while(atual->prox != NULL && atual->prox->valor < valor){ //enquanto não estiver no ultimo elemento e valor do próximo elemento for menor que o valor - anda
		atual = atual->prox;
	}
	
	novo->prox = atual->prox;
	atual->prox = novo;
}

void removePrimeiroMochila(Lista *p, int *p_valor){
	if(*p == NULL) return;

	No *aux = *p;
	*p = (*p)->prox;

	if(p_valor != NULL)
    	*p_valor = aux->valor;

	free(aux);
}

void mostrarMochila(Lista p){
    printf("\nMochila: ");

    while(p != NULL){
        printf(" %d", p->valor);
        p = p->prox;
    }

    printf("\n");
}

int calcularTotalMochila(Lista mochila) {
    int total = 0;

    while (mochila != NULL) {
        total += mochila->valor;
        mochila = mochila->prox;
    }

    return total;
}
