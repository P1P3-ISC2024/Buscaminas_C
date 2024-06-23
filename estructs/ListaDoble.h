#include <stdio.h>

#ifndef _DLista_
#define _Dlista_
#define Tipo int

typedef struct ptr{
	Tipo dato;
	struct ptr *sgt;
	struct ptr *ant;
}Nodo;

typedef struct{
	int numElem;
	Nodo *inicio;
	Nodo *final;
}ListaD;

void Init(ListaD *lista);// inicializa los valores de la lista.
Nodo *tofront(ListaD *lista,int pos);//regresa el nodo de la poscicion indicada.(recorre de inicio a final)
Nodo *toback(ListaD *lista,int pos,Nodo *actual);//regresa el nodo de la poscicion indicada. (recorre de final a inicio)
void InsertFirst(ListaD *lista, Tipo datum);// inserta el primer elemento. (lista vacia)
int InsertI(ListaD *lista, Tipo datum);// inserta un elemento en el inicio.
int InsertF(ListaD *lista, Tipo datum);// inserta un elemento en el final
int InsertA(ListaD *lista,int pos, Tipo datum);// inserta un elemento en la lista una posicion antes.
int InsertD(ListaD *lista,int pos, Tipo datum);// inserta un elemento en la lista una posicion despúes.
Tipo ClearI(ListaD *lista);// Elimina el elemento en el inicio de la lista.
Tipo ClearF(ListaD *lista);// Elimina el elemento final de la lista.
Tipo Clear(ListaD *lista, int pos);// Elimina el elemento en una pocicion.
int Clearall(ListaD *lista);// Elimina todos los elementos de una lista.
Tipo See(ListaD *lista,int pos);// Observa un elemento especifico de una pocicion.
void SeeALL(ListaD *lista);// Visualiza a todos los elementos de la lista.

#endif
