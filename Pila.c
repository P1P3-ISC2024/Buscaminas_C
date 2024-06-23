#include "Pila.h"

//inicia los valores de una pila nueva
int init_pila(Pila *duracel){
	duracel->elmentos=0;
	duracel->tope=NULL;
	return 0;
}

//inserta un elemento en la pila
int push_pila(Pila *duracel,tipo data){
	Nodo *novo=calloc(sizeof (Nodo),1);
	novo->dato=data;
	novo->sgt=duracel->tope;
	duracel->tope=novo;
	duracel->elmentos++;
	return 0;
}

//eliminar el tope de la pila, retorna el dato eleminado
tipo pop_pila(Pila *duracel){
	if(duracel->elmentos==0){
		printf(" La pila esta vacia !!!");
		return 0;
	}
	Nodo *ptr=duracel->tope;
	duracel->tope=ptr->sgt;
	duracel->elmentos--;
	return ptr->dato;
}

//ver el dato del tope de la pila
tipo see_top(Pila *duracel){
	if(duracel->elmentos<=0){
		printf("No hay elementos que mostrar en la pila, la pila esta vacia");
		return 0;
	}
	return duracel->tope->dato;
}
