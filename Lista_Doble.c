#include <stdio.h>
#include "Lista_Doble.h"

void initDL(DobleLista *elemento){
	elemento->num_nodos=0;
	elemento->inicio=NULL;
	elemento->final=NULL;
}

int insertFirst(DobleLista *elemento,Tipo valor,Tipo valor2){
	if(elemento->num_nodos!=0) return -1;
	nodo *novo=calloc(sizeof(nodo),1);
	if(novo!=NULL){
		novo->dato=valor;
		novo->data=valor2;
		novo->ant=novo;
		novo->sgt=novo;
		elemento->inicio=novo;
		elemento->final=novo;
		elemento->num_nodos=1;
	}
	else return -2;
}

int *insertI(DobleLista *elemento,Tipo valor,Tipo valor2){
	if(elemento->num_nodos==0){
		insertFirst(elemento,valor,valor2);
		return 0;
	}
	else{
		nodo *novo=calloc(sizeof(nodo),1);
		if(novo!=NULL){
			novo->dato=valor;
			novo->data=valor2;
			novo->sgt=elemento->inicio;
			novo->ant=elemento->final;
			elemento->inicio->ant=novo;
			elemento->final->sgt=novo;
			elemento->inicio=novo;
			elemento->num_nodos++;
			return 1;
		}
	}
	return -1;
}

int *insertF(DobleLista *elemento,Tipo valor,Tipo valor2){
	if(elemento->num_nodos==0){
		insertFirst(elemento,valor,valor2);
		return 0;
	}
	else{
		nodo *novo=calloc(sizeof(nodo),1);
		if(novo!=NULL){
			novo->dato=valor;
			novo->data=valor2;
			novo->sgt=elemento->inicio;
			novo->ant=elemento->final;
			elemento->inicio->ant=novo;
			elemento->final->sgt=novo;
			elemento->final=novo;
			return 1;
		}
	}
	return -1;
}

Tipo *clearI(DobleLista *elemento){
	if(elemento->num_nodos==0)
	return -1;
	else{
		nodo *novoInicio=elemento->inicio->sgt;
		elemento->final->sgt=novoInicio;
		novoInicio->ant=elemento->final;
		elemento->inicio=novoInicio;
		return 0;
	}
	return -2;
}

Tipo *clearF(DobleLista *elemento){
	if(elemento->num_nodos==0)
	return -1;
	else{
		int value=elemento->final->dato;
		nodo *novoEnd=elemento->final->ant;
		elemento->inicio->ant=novoEnd;
		novoEnd->sgt=elemento->inicio;
		elemento->final=novoEnd;
		return 0;
	}
	return -2;
}

int search_data(DobleLista *elemento, Tipo valor,Tipo valor2){
	if(elemento->num_nodos==0)
		return -1;
	else{
		int i=1;
		nodo *actual=elemento->final;
		do{
			actual=actual->sgt;
			if(actual->dato==valor&&actual->data==valor2)
				return i;
			i++;
		}while(actual!=elemento->final);
		return 0;
	}
	return -2;
}
