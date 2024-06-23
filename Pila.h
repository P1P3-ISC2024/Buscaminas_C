#ifndef _pila_
#define _pila_

#include <stdio.h>
#include <stdlib.h>

#define tipo int
typedef struct celda{
	tipo dato;
	struct celda *sgt;
}Nodo;

typedef struct{
	int elmentos;
	Nodo *tope;
}Pila;

int init_pila(Pila *duracel);
int push_pila(Pila *duracel,tipo data);
tipo pop_pila(Pila *duracel);
tipo see_top(Pila *duracel);
#endif
