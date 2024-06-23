#include <stdio.h>
#include "ListaDoble.h"

void Init(ListaD *lista){
	lista->numElem=0;
	lista->inicio=NULL;
	lista->final=NULL;
}

Nodo *tofront(ListaD *lista,int pos){
	Nodo *actual=calloc(sizeof(Nodo),1);//el indice que apunta a un nodo dado
	if(lista->numElem==0){
		actual=NULL;
		return 0;
	}
	if(pos!=0){
		int ind=1;
		actual=lista->inicio;
		pos=pos%(lista->numElem+1);
		do{
			actual=actual->sgt;
			ind++;
		}while(ind<pos);
		return actual;
	}
	else
		return lista->inicio;
}

Nodo *toback(ListaD *lista, int pos, Nodo *actual){
	if(lista->numElem==0){
		return NULL;
	}	
	if(pos!=lista->numElem&&pos!=0){
		int ind=lista->numElem-1;
		actual=lista->final;
		pos=pos%(lista->numElem);
		do{
			actual=actual->ant;
			ind--;
		}while(ind>pos);
		return actual;
	}
	else
		return lista->final;
}

void InsertFirst(ListaD *lista, Tipo datum){
	Nodo *novo=calloc(sizeof (Nodo),1);
	if(novo==NULL||lista->numElem!=0)
		return -1;
	novo->dato=datum;
	novo->ant=novo;
	novo->sgt=novo;
	lista->inicio=novo;
	lista->final=novo;
	lista->numElem++;
}

int InsertI(ListaD *lista,Tipo datum){
	if(lista->numElem==0){
		InsertFirst(lista,datum);
		return 0;
	}
	Nodo *novo=calloc(sizeof(Nodo),1);
	if(novo==NULL)
		return -1;
	novo->dato=datum;
	novo->sgt=lista->inicio;
	novo->ant=lista->final;
	lista->inicio->ant=novo;
	lista->final->sgt=novo;
	lista->inicio=novo;
	lista->numElem++;
	return 0;
}

int InsertF(ListaD *lista, Tipo datum){
	if(lista->numElem==0){
		InsertFirst(lista,datum);
		return 0;
	}
	Nodo *novo=calloc(sizeof(Nodo),1);
	if(novo==NULL)
		return -1;
	novo->dato=datum;
	novo->ant=lista->final;
	novo->sgt=lista->inicio;
	lista->final->sgt=novo;
	lista->inicio->ant=novo;
	lista->final=novo;
	lista->numElem++;
	return 0;
}

int InsertA(ListaD *lista,int pos, Tipo datum){
	if(lista->numElem==0){
		InsertFirst(lista,datum);
		return 0;
	}
	if(pos>lista->numElem)
		return NULL;
	if(pos==2)
		InsertI(lista,datum);
	else if(pos==1)
		InsertF(lista,datum);
	else if(pos>0){
		
		Nodo *novo=calloc(sizeof(Nodo),1);
		Nodo *actual=NULL;
		
		
		if(novo==NULL)
			return NULL;
		if(pos<=lista->numElem/2)
			actual=tofront(lista,pos);
		else
			actual=toback(lista,pos,actual);
		Nodo *past=actual->ant;
		novo->dato=datum;
		past->sgt=novo;
		actual->ant=novo;
		novo->sgt=actual;
		novo->ant=past;
		lista->numElem++;
		return 0;
	}
	return -2;
}

int InsertD(ListaD *lista,int pos, Tipo datum){
	if(lista->numElem==0){
		InsertFirst(lista,datum);
		return 0;
	}
	if(pos>lista->numElem)
		return -1;
	if(pos==lista->numElem)
		InsertI(lista,datum);
	else if(pos==lista->numElem-1)
		InsertF(lista,datum);
	else if(pos>0){
		Nodo *novo=calloc(sizeof(Nodo),1);
		Nodo *actual;
		Nodo *post;
		
		if(novo==NULL)
			return -1;
		if(pos<=lista->numElem/2)
			actual=tofront(lista,pos);
		else
			actual=toback(lista,pos,actual);
			
		novo->dato=datum;
		post=actual->sgt;
		post->ant=novo;
		actual->sgt=novo;
		novo->sgt=post;
		novo->ant=actual;
		lista->numElem++;
		return 0;	
	}
	return -2;
}

Tipo ClearI(ListaD *lista){
	if(lista->numElem==0){
		printf("error lista vacia");
	}
	else{
		Nodo *inin=lista->inicio;//inin (este)
		if(lista->numElem==1){
			lista->inicio=NULL;
			lista->final=NULL;
			return inin->dato;
		}
		lista->inicio=inin->sgt;
		lista->final->sgt=lista->inicio;
		lista->inicio->ant=lista->final;
		lista->numElem--;
		return inin->dato;
	}
}

Tipo ClearF(ListaD *lista){
	if(lista->numElem==0){
		return 0;
	}
	Nodo *inin=lista->final;
	if(lista->numElem==1){
		lista->inicio=NULL;
		lista->final=NULL;
		return inin->dato;
	}
	lista->final=inin->ant;
	lista->final->sgt=lista->inicio;
	lista->inicio->ant=lista->final;
	lista->numElem--;
	return inin->dato;
}

Tipo Clear(ListaD *lista, int pos){
	if(lista->numElem==0)
		return 0;
	Nodo *inin=NULL;
	inin=tofront(lista,pos);
	inin->ant->sgt=inin->sgt;
	inin->sgt->ant=inin->ant;
	return inin->dato;
	
	
}
int Clearall(ListaD *lista){
	Init(lista);
}
Tipo See(ListaD *lista,int pos){
	Nodo *actual;
	if(pos<=lista->numElem/2)
			actual=tofront(lista,pos);
	else
		toback(lista,pos,actual);
	printf("%d",actual->dato);
}

void SeeALL(ListaD *lista){
	printf("1---");
	if(lista->numElem==0)
		printf("Error");
	else{
		Nodo *indice=lista->inicio;
		do{
			printf("%d ",indice->dato);
			indice=indice->sgt;
		}while(indice->sgt!=lista->inicio->sgt);
		printf("\n");
	}
}
