#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include "Estructura_Campo.h"

void gotoxy(int x,int y){
	HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos); 
}
int rdtsc(){
	__asm__ __volatile__("rdtsc");
}

int Calc_minas(int nivel,int x,int y){
	if(x<=1||y<=1){
		return -1;
	}
	
	switch(nivel){
		case 1:
			return (x*y*15)/100;
		case 2:
			return (x*y*30)/100;
		case 3:
			return (x*y*60)/100;
		default:
			return -1;
	}
}

void init_Matrix(Minas *campo,int nivel,int x,int y){
	ListaD matrix[x];
	int i,j,k;
	int ejex,ejey;
	campo->X=x;
	campo->Y=y;
	campo->dificultad=nivel;
	campo->num_minas=Calc_minas(nivel,x,y);
	printf("%d",campo->num_minas);
	//----------------------------------------hora de crear el campo minado
	//paso 1 Crear un campo vacio...

	for(i=0;i<x;i++){
		Init(&matrix[i]);//inicializa la lista de dicha columna
		printf("\n\n");
		for(j=0;j<y;j++){
			InsertI(&matrix[i],0);//crea celdas con con 0 'y' veces (crea las filas en cada columna)
			printf("(%d,%d)%x  ",i,j,tofront(&matrix[i],j),tofront(&matrix[i],j)->ant);
		}
	}
	
	//paso 2 elegir las posisiones de las minas...
	for(i=0;i<campo->num_minas;i++){
		srand(rdtsc());//crea una semilla random
		ejex=rand()%(x-1);//añade la ordenada aleatoria que este dentro de el max num de renglones
		srand(rdtsc());
		ejey=rand()%(y+1);
		Nodo *celda=tofront(&matrix[ejex],ejey);
		printf("\n%x: %d,%d",celda,ejex,ejey);
		/*
		paso 3 Si la posicion elegida no tene una mina => poner una mina
		
			luego si la ordenada en 'y' es impar y la siguiente posición no tiene una mina
			=> poner una mina en la casilla de la columna siguiente.
			
			además si la ordenada 'x' es par y la siguiente posición no tiene una mina
			=> poner una mina en la casilla del renglon siguiente.
			...
		*/
		if(celda->dato!=-1) 
		{
			printf(" vacio");
			/*if((tofront(&matrix[(ejex+1)%x],ejey)->dato!=-1)&&(ejey%2==1)){
				printf(", \"Y\" es impar");
				tofront(&matrix[(ejex+1)%x],ejey)->dato=-1;
				i++;
			}
			if(tofront(&matrix[ejex],ejey+1)->dato!=-1&&(ejex%2==0)){
				tofront(&matrix[ejex],ejey+1)->dato=-1;
				i++;
				printf(", \"X\"es par");
			}*/
			celda->dato=-1;
			printf("..");
		}
		else i--;
		printf("%d\n",i);
		for(k=0;k<y;k++)
			{
				for(j=0;j<x;j++)
				{
					printf("%d ",tofront(&matrix[j],k)->dato);
				}
				printf("\n");
			}
	
	}
	campo->mapa=&matrix;
	printf("\n");
	for(i=0;i<y;i++){
		for(j=0;j<x;j++){
			printf("%d ",tofront(&matrix[i],j)->dato);
		}
		printf("\n");
	}
}
