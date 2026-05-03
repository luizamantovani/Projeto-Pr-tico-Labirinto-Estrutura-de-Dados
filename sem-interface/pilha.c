#include<stdio.h>
#include<stdlib.h>
#include "pilha.h"

//função que cria a pilha
void criaPilha(Pilha *p){
	p->topo = -1;
}

//função que insere as coordenadas na pilha
void push(Pilha *p, int x, int y) {
    p->topo++;
    p->dados[p->topo].x = x;
    p->dados[p->topo].y = y;
}

//função que retira da pilha
void pop(Pilha *p){
	if(p->topo >= 0){ 
		p->topo--;
	}
}

//função que retorna o topo da pilha
Posicao topoPilha(Pilha *p) {
    return p->dados[p->topo];
}

//função que retorna 1 se a pilha for vazia e 0 se estiver com algum elemento
int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}
