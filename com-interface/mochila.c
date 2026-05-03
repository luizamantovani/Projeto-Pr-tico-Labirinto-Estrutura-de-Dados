#include<stdio.h>
#include <stdlib.h>
#include "mochila.h"

//função que cria a mochila (lista)
void criaMochila(Lista *p){
	*p = NULL;
}

//função que insere o valor passado como parametro sempre no inicio 
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

//função que remove o primeiro elemento da função
void removePrimeiroMochila(Lista *p, int *p_valor){
	if(*p == NULL) return;

	No *aux = *p;
	*p = (*p)->prox;

	if(p_valor != NULL)
    	*p_valor = aux->valor;

	free(aux);
}

//função que mostra a mochila no terminal
void mostrarMochila(Lista p){
    printf("\nMochila: ");

    while(p != NULL){
        printf(" %d", p->valor);
        p = p->prox;
    }

    printf("\n");
}

//função que soma todos os elementos da mochila e retorna esse valor
int calcularTotalMochila(Lista mochila) {
    int total = 0;

    while (mochila != NULL) {
        total += mochila->valor;
        mochila = mochila->prox;
    }

    return total;
}

//função que retorna 1 se a mochila estiver vazia e 0 se estiver com algum elemento
int mochilaVazia(Lista mochila){
	if(mochila==NULL){
		return 1;
	}
	return 0;
}
