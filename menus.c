#include <stdio.h>
#include <ctype.h>
#include <windows.h>
#include "Lista_Doble.h"
#include "Estructura_campo.h"

int print_game();
void print_game_win();
void print_game_lose();
void main_menu();
int options_menu();
int settings_menu();
void howToPlay();
void bye();

int print_game(){
	system("cls");
	system("color 02");
	printf("\n Campo %dx%d\t dificultad:",campo.X,campo.Y);
	switch(campo.dificultad){
		case 1:
			printf(" facil");
			break;
		case 2:
			printf(" normal");
			break;
		case 3:
			printf(" dificil");
			break;
		case 4:
			printf(" pesadilla");
			break;
		default:
			printf(" wtf?");
			return -10;
	}
	printf("\t\t %d Minas\n",campo.num_minas);
	//gotoxy(13,35);
	//printf("muevete con w,a,s,d cava con 'enter' marca una mina con '+' y desmarcala con '{' (para las casillas no exploradas)");
	gotoxy(0,5);
	print_mapa();
}

void print_game_win(){
	system("cls");
	system("color 0B");;
	play_sound("win");
	//hecho con https://www.messletters.com/es/big-text/ estilo larry3d
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t                                                            ___              __                        __     \n");
	printf("\t\t                                                           /\\_ \\      __    /\\ \\                      /\\ \\    \n");
	printf("\t\t  ___      __       ___ ___     _____     ___              \\//\\ \\    /\\_\\   \\ \\ \\____   _ __     __   \\ \\ \\   \n");
	printf("\t\t /'___\\  /'__`\\   /' __` __`\\  /\\ '__`\\  / __`\\              \\ \\ \\   \\/\\ \\   \\ \\ '__`\\ /\\`'__\\ /'__`\\  \\ \\ \\  \n");
	printf("\t\t/\\ \\__/ /\\ \\L\\.\\_ /\\ \\/\\ \\/\\ \\ \\ \\ \\L\\ \\/\\ \\L\\ \\              \\_\\ \\_  \\ \\ \\   \\ \\ \\L\\ \\\\ \\ \\/ /\\  __/   \\ \\_\\ \n");
	printf("\t\t\\ \\____\\\\ \\__/.\\_\\\\ \\_\\ \\_\\ \\_\\ \\ \\ ,__/\\ \\____/              /\\____\\  \\ \\_\\   \\ \\_,__/ \\ \\_\\ \\ \\____\\   \\/\\_\\ \n");
	printf("\t\t \\/____/ \\/__/\\/_/ \\/_/\\/_/\\/_/  \\ \\ \\/  \\/___/               \\/____/   \\/_/    \\/___/   \\/_/  \\/____/    \\/_/ \n");
	printf("\t\t                                  \\ \\_\\ \n");
	printf("\t\t                                   \\/_/");
	getch();
	main_menu();
}

void print_game_lose(){
	system("cls");
	system("color F0");
	Sleep(1000);
	system("color 04");
	play_sound("lose");
	//hecho con https://www.messletters.com/es/big-text/ estilo larry3d
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t\t\t __   __                __   __ \n");
	printf("\t\t\t\t\t\t\t/\\ \\ /\\ \\              /\\ \\ /\\ \\ \n");
	printf("\t\t\t\t\t\t\t\\ `\\`\\/'/'             \\ `\\`\\/'/' \n");
	printf("\t\t\t\t\t\t\t `\\/ > <                `\\/ > <   \n");
	printf("\t\t\t\t\t\t\t    \\/'/\\`\\                \\/'/\\`\\  \n");
	printf("\t\t\t\t\t\t\t    /\\_\\\\ \\_\\              /\\_\\\\ \\_\\ \n");
	printf("\t\t\t\t\t\t\t    \\/_/ \\/_/  _______     \\/_/ \\/_/ \n");
	printf("\t\t\t\t\t\t\t              /\\______\\   \n");
	printf("\t\t\t\t\t\t\t              \\/______/   \n");
	getch();
	main_menu();
}

void main_menu(){
	int i,j;
	char top=205,col=186;
	char ESD=187,EID=188,ESI=201,EII=200;
	char *titulo[6];
	char viga[71];
	
	char titulo0[]="______                                      _                    ";
	char titulo1[]="| ___ \\                                    (_)                   ";
	char titulo2[]="| |_/ / _   _  ___   ___   __ _  _ __ ___   _  _ __    __ _  ___ ";
	char titulo3[]="| ___ \\| | | |/ __| / __| / _` || '_ ` _ \\ | || '_ \\  / _` |/ __|";
	char titulo4[]="| |_/ /| |_| |\\__ \\| (__ | (_| || | | | | || || | | || (_| |\\__ \\";
	char titulo5[]="\\____/  \\__,_||___/ \\___| \\__,_||_| |_| |_||_||_| |_| \\__,_||___/";//70 -> 78
	
	titulo[0]=&titulo0;
	titulo[1]=&titulo1;
	titulo[2]=&titulo2;
	titulo[3]=&titulo3;
	titulo[4]=&titulo4;
	titulo[5]=&titulo5;
	
	for(i=0;i<71;i++){
		viga[i]=top;
	}
	system("cls");
	system("color 0D");
	//efecto de recorrido del titulo
	play_sound("start");
	for(i=0;i<6;i++){
		system("cls");
		if(i==5) {printf("\n\n\t\t\t\t\t%c%s%c\n",ESI,viga,ESD);}//imprime la parte sup de la caja
		for(j=5-i;j<6;j++){
			printf("\t\t\t\t\t");
			printf("%c   ",col);
			printf("%s",titulo[j]);
			printf("   %c\n",col);
		}
		printf("\t\t\t\t\t%c%s%c",EII,viga,EID);//imprime la parte inf de la caja
		Sleep(200);
	}
	gotoxy(13,35);
	printf("muevete con 'w' y 's' y selecciona con 'enter'\n");
	printf("\t\truta actual %s",ajuste.direccion);
	system("color 50");
}

int options_menu(){
	int x= 20, y= 10;
	short int estado,opcion;
	char select;
	estado = 0;
	
	//imprime opciones
	Sleep(250);
	fflush(stdin);
	gotoxy(43,12);
	printf(" -->jugar\n\t\t\t\t\t   configuraci%cn\n\t\t\t\t\t   %cComo jugar?\n\t\t\t\t\t   salir",418,168);
	gotoxy(53,12);//se va a la funcion elegida por default
	do{
		system("color 0D");
		select=getch();
		if(select!=13){
			switch(select){//dependiendo de la entrada realiza un movimiento
				case 'W':
				case 'w':
					play_sound("move");
					estado=modulo(estado-1,4);
					break;
				case 'S':
				case 's':
					play_sound("move");
					estado=modulo(estado+1,4);
					break;
			}
			Sleep(100);
		}
		else{ //si ha pulsado enter
			switch(estado){
				case 0://jugar
					//empieza una partida x
					play_sound("startgame");
					init_options();//se revisan y guarda los parametros para ajuste
					init_struct(ajuste.columnas,ajuste.filas,ajuste.dificultad);
					init_mapa();
					initDL(&explorados);
					print_game();
					jugar();
					opcion = estado;
					break;
				case 1://configuración
					play_sound("select");
					settings_menu();
					opcion = estado;
					break;
				case 2://¿como jugar?
					play_sound("select");
					howToPlay();
					break;
				case 3://salir
					play_sound("start3");
					opcion = estado;
					bye();
					Sleep(1700);
					break;
			}
		}
		
		//vuelve a imprimir todo sin una opcion seleccionada
		gotoxy(43,12);
		printf("jugar      \n\t\t\t\t\t   ");
		printf("configuraci%cn      \n\t\t\t\t\t   ",418);
		printf("%cComo jugar?       \n\t\t\t\t\t   ",168);
		printf("salir      \n");
		//se va a la opcion del estado un la marca como seleccionada
		switch(estado){
			case 0://jugar
				gotoxy(43,12);
				printf(" -->jugar");
				break;
			case 1://configuración
				gotoxy(43,13);
				printf(" -->configuraci%cn",418);
				break;
			case 2:
				gotoxy(43,14);
				printf(" -->%cComo jugar?",168);
				break;
			case 3://salir
				gotoxy(43,15);
				printf(" -->salir");
				break;
		}
	}while(opcion!=3);
}

int settings_menu(){
	int x= 10, y= 5;
	short int estado,opcion = 1,setInt,setLevel = 1;
	char select;
	estado = 0;
	
	init_options();
	system("cls");
	system("color 0B");
	printf("\n\n\t Configuraciones");
	//imprime opciones
	gotoxy(43,12); printf("-->regresar");
		
	gotoxy(43,13); printf("   columnas");
	gotoxy(60,13); printf("%d",ajuste.columnas);
	
	gotoxy(43,14); printf("   filas");
	gotoxy(60,14); printf("%d",ajuste.filas);
	
	gotoxy(43,15); printf("   dificultad");
	gotoxy(60,15);
	switch(ajuste.dificultad){
		default:
			printf("|---facil---|");
			break;
		case 2:
			printf("|---normal--|");
			break;
		case 3:
			printf("|--dificil--|");
			break;
		case 4:
			printf("|-pesadilla-|");
			break;

	}
	
	gotoxy(53,12);//se va a la funcion elegida por default
	do{
		select=getch();
		if(select!=13){
			switch(select){//dependiendo de la entrada realiza un movimiento
				case 'W':
				case 'w':
					play_sound("move");
					estado=modulo(estado-1,4);
					break;
				case 'S':
				case 's':
					play_sound("move");
					estado=modulo(estado+1,4);
					break;
			}
		}
		else{ //si ha pulsado enter
			switch(estado){
				case 0://regresar
					save_settings();
					Sleep(200);
					break;
				case 1://columnas
					play_sound("select");
					printf("\t             ");
					gotoxy(13,35);
					printf("introduce un valor entre %d y %d columnas",TAMIN,TAMAX_X);
					gotoxy(60,13);
					
					do{
						scanf("%d",&setInt);
						fflush(stdin);
					}while(isalpha(setInt));
					
					insert_columnas(setInt);					
					break;
				case 2://filas
					play_sound("select");
					printf("\t             ");
					gotoxy(13,35);
					printf("introduce un valor entre %d y %d filas     ",TAMIN,TAMAX_Y);
					gotoxy(60,14);
					
					do{
						scanf("%d",&setInt);
						fflush(stdin);
					}while(isalpha(setInt));
					
					insert_filas(setInt);
					break;
				case 3://dificultad
					play_sound("select");
					gotoxy(13,35);
					printf("cambia las opciones con w,a,s,d y selecciona con 'enter'                   ");
					select = 0;
					setLevel = ajuste.dificultad - 1; //como va de 1 - 4 le restamos 1 para operar con modulo 4 osea de 0-3
					gotoxy(73,15);
					while(select!=13){
						select=getch();
						switch(select){//dependiendo de la entrada realiza un movimiento
							case 'S':
							case 'A':
							case 's':
							case 'a':
								play_sound("down");
								setLevel=modulo(--setLevel,4);
								break;
							case 'w':
							case 'd':
							case 'W':
							case 'D':
								play_sound("up");
								setLevel=modulo(++setLevel,4);
								break;
						}
						gotoxy(60,15);
						switch(setLevel+1){
							case 1:
								printf("|---facil---|");
								break;
							case 2:
								printf("|---normal--|");
								break;
							case 3:
								printf("|--dificil--|");
								break;
							case 4:
								printf("|-pesadilla-|");
								break;
							default:
								printf("wtf?\t");
								return -10;
						}
					}
					insert_dificultad(setLevel+1);//le regresamos el uno que se le quitó para que valla de 1 - 4 
					break;
			}
			opcion = estado;
		}
		
		//vuelve a imprimir todo sin una opcion seleccionada
		gotoxy(43,12);
		printf("   regresar");
		gotoxy(43,13);
		printf("   columnas");
		gotoxy(43,14);
		printf("   filas");
		gotoxy(43,15);
		printf("   dificultad");
		//se va a la opcion del estado un la marca como seleccionada
		gotoxy(43,12+estado);
		printf("-->");
		switch(estado){//para que el puntero esté al final de la palabra
			case 0:
				printf("regresar");
				break;
			case 1:
				printf("columnas");
				break;
			case 2:
				printf("filas");
				break;
			case 3:
				printf("dificultad");
				break;
		}
	}while(opcion!=0);
	main_menu();
	return 0;
}

void howToPlay(){
	system("cls");
	system("color 0E");
	printf("\n\n\n\n\n\t\t");
	printf("Buscaminas es un juego arcade, en el que el objetivo consiste en explorar y analizar el campo de juego");
	printf("\n\t\t");
	printf("para deducir en donde hay minas; el juego termina en victoria cuando el jugador ha explorado o 'cavado'");
	printf("\n\t\t");
	printf("en todas las casillas libres y termina en derrota cuando se cava en una casilla con una mina.");
	printf("\n\n\t\t");
	printf("Las casillas libres marcan el numero de minas cercanas al rededor, en un rango de un cuadro de distancia, es decir, el mayor");
	printf("\n\t\t");
	printf("numero de minas cercanas posible es 9 y el menor 0 endonde si una casilla libre no tiene un numero indica 0 minas cercanas.");
	printf("\n\n\t\t");
	printf("Para moverte e interactuar dentro del mapa utiliza las siguientes teclas");
	printf("\n\t\t\tW -> arriba   a -> izquierda   s-> abajo   d-> derecha");
	printf("\n\t\t\t+ -> marcar casilla    { -> desmarcar casilla   enter -> cavar");
	gotoxy(3,2);
	printf("<<regresar");
	while(getch() != 13);
	play_sound("return");
	Sleep(200);
	main_menu();
}

void bye(){//ascii de http://patorjk.com/software/taag/#p=display&f=Soft&t=Adios%20%3A)
	system("cls");
	system("color 03");
	gotoxy(43,12);
	printf("  ,---.     ,--.,--.                      ,-.   ");
	gotoxy(43,13);
	printf(" /  O  \\  ,-|  |`--' ,---.  ,---.     .--.'. \\  ");
	gotoxy(43,14);
	printf("|  .-.  |' .-. |,--.| .-. |(  .-'     '--' |  | ");
	gotoxy(43,15);
	printf("|  | |  |\\ `-' ||  |' '-' '.-'  `)    .--. |  | ");
	gotoxy(43,16);
	printf("`--' `--' `---' `--' `---' `----'     '--'.' /  ");
	gotoxy(43,17);
	printf("                                          `-'   ");
}
