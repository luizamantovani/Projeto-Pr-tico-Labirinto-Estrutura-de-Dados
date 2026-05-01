#include<stdio.h>
#include<stdlib.h>
#include "pilha.h"

void criaPilha(Pilha *p){
	p->topo = -1;
}

void push(Pilha *p, int x, int y) {
    p->topo++;
    p->dados[p->topo].x = x;
    p->dados[p->topo].y = y;
}

void pop(Pilha *p){
	if(p->topo >= 0){ //significa que a pilha não é vazia
		p->topo--;
	}
}

Posicao topoPilha(Pilha *p) {
    return p->dados[p->topo];
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}
