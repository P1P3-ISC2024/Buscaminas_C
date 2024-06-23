#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Estructura_campo.h"
#include "Pila.h"



void main() {
	//system("mode 170,46");
	//PRECAUCIÓN las siguientes instrucciones pueden dejar presionado (virtualmente) alt o enter (u otra tecla) ¡cuidado al modificar!
	keybd_event(VK_MENU,0x38,0,0);       // Presiona ALT   --no modificar el 2do parametro para que sea eficas el alt+enter
	keybd_event(VK_RETURN,0x1c,0,0);     // Presiona ENTER
	keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);// Libera ENTER
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);   // Libera ALT*/
	//si se modifico mal, precionar dos veces alt o enter o volver a ejecutar el programa, para desoprimir (virtualmente)
	init_options();
	Sleep(100);
	main_menu();
	options_menu();/*sí está función se manda a llamar desde main_menu(), 
	se generá un efecto de recursividad y se tendrá que
	pulsar n'veces salir para salir :,v ; aunque las otras opciones trabajen correctamente*/
}
