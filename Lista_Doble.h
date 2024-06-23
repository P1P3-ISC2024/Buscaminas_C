#include <stdio.h>
#ifndef _Doublelista_
#define _Doublelista_
#define Tipo int

typedef struct ptr{
	Tipo dato;
	Tipo data;
	struct ptr *sgt;
	struct ptr *ant;
}nodo;

typedef struct{
	int num_nodos;
	nodo *inicio;
	nodo *final;
}DobleLista;

void initDL(DobleLista *elemento);// inicia la lista
int insertFirst(DobleLista *elemento,Tipo valor,Tipo valor2);// inserta el primer elemento
int *insertI(DobleLista *elemento,Tipo valor,Tipo valor2);//inserta al inicio
int *insertF(DobleLista *elemento,Tipo valor,Tipo valor2);//inserta al final
int *insertA(DobleLista *elemento,Tipo valor,Tipo valor2,int pos);//inserta antes de una posicion
int *insertD(DobleLista *elemento,Tipo valor,Tipo valor2,int pos);//inserta despúes de una posicion
nodo *Recorre_frente(DobleLista *elemento,int pos);//regresa el nodo de una posicion con un recorrido de inicio a fin
nodo *Recorre_atras(DobleLista *elemento,int pos);////regresa el nodo de una posicion con un recorrido de fin a inicio
Tipo *clearI(DobleLista *elemento);//Elimina el primer elemento de una lista
Tipo *clearF(DobleLista *elemento);//Elimina el ultimo elemento de una lista
Tipo *clearPos(DobleLista *elemento,int pos);//elimina el elemento de una posicion especifica
int *clearAll(DobleLista *elemento);//elimina todos los nodos de una lista
int search_data(DobleLista *elemento, Tipo valor,Tipo valor2);//buscar un elmento en la lista
#endif



