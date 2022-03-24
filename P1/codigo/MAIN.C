#include <dos.h>
#include <stdio.h>
#include "MI_IO.H"
#define BYTE unsigned char

int main()
{
  int opcion = 0;
  int incorrecto = 1;

  do{

    clrscr();
    printf("\nMenu: ");
    printf("\n\t 1 - gotoxy -  colocar cursor");
    printf("\n\t 2 - setcursortype - fijar aspecto cursor");
    printf("\n\t 3 - setvideomode  -  fijar el modo de video");
    printf("\n\t 4 - getvideomode  -  obtiene el modo de video actual");
    printf("\n\t 5 - textcolor - modifica color de primer plano de los caracteres");
    printf("\n\t 6 - textbackground - modifica color de fondo de los caracteres");
    printf("\n\t 7 - clscr - borra toda la pantalla");
    printf("\n\t 8 - cputchar - escribir caracter con el color indicado");
    printf("\n\t 9 - getche - obtener caracter de teclado y mostrarlo en pantalla");
    printf("\n\t 10 - Salir");

    printf("\n\t Selecciona una opcion : ");
    scanf("%d", &opcion);

    if  (opcion < 1 || opcion > 10){
      printf("\n Introduce una opción valida [1-9]: ");
    }
    else{
      incorrecto = 0;
    }

    pausa();
  }while(incorrecto != 0);


    switch (opcion){
      case 1:
      // (1) - gotoxy -------------------------------------------#
      
          clrscr();
          gotoxy(20,1);
          printf("*");
          printf("Cursor movido a la posicion (20,1)\n");
          pausa();
          clrscr();

          gotoxy(5, 20);
          printf("*");
          printf("Cursor movido a la posicion (5,20)");
          pausa();
          clrscr();

          gotoxy(1,15);
          printf("*");
          printf("Cursor movido a la posicion (1,15)");
          pausa();
          clrscr();
      break;
      case 2:
      // (2) - setcursortype -------------------------------------------#
        clrscr();
        setcursortype(0);
        printf("\nCursor  INVISIBLE: ");
        pausa();

        setcursortype(1);
        printf("\nCursor  NORMAL: ");
        pausa();

        setcursortype(2);
        printf("\nCursor  GRUESO: ");
        pausa();
        clrscr();
      break;
      case 3:
      // (3) - setvideomode -------------------------------------------#
        clrscr();
        setvideomode(MODO_VIDEO);
        printf("\nModo <%u>, video\n", getvideomode());
        pixel(10,40,0);
        pixel(10,50,1);
        pixel(15,60,2);
        pixel(20,70,3);

        pausa();
        setvideomode(MODO_TEXTO);
        printf("\nModo <%u>, texto\n", getvideomode());
        pausa();
        clrscr();
      break;

      case 4:
      // (4) - getvideomode -------------------------------------------#
        clrscr();
        if (getvideomode() == 3){
          printf("Modo <%u> TEXTO\n", getvideomode());
        }
        else if (getvideomode() == 4){
          printf("Modo <%u> VIDEO\n", getvideomode());
				}


        pausa();
        clrscr();
      break;

      case 5:
      // (5) - textcolor -------------------------------------------#
        clrscr();
        printf("Caracter color: ");
        textcolor(12); // Cambia el color a LIGHTRED
        cputchar('Y',1); // Escribimos un caracter por pantalla
        pausa();
        clrscr();
      break;

      case 6:
      // (6) - textbackground -------------------------------------------#
        clrscr();
        printf("Caracter color: ");
        textbackground(2);
        cputchar('X',1);
        pausa();
        clrscr();
      break;

      case 7:
      // (7) - clrscr -------------------------------------------#
        printf("\nPrueba de clrscr. Pulse una tecla para borrar la pantalla.");
        pausa();
        clrscr();
        printf("Pantalla Borrada.");
      break;

      case 8:
      // (8) - cputchar -------------------------------------------#
        clrscr();      
        printf("\nPrueba de cputchar\n");
        printf("Caracter: ");
        textcolor(1);
        cputchar('X',1);
        printf("\nCambiamos el color actual");
        printf("\nCaracter:");
        textcolor(11);
        cputchar('X',1);
        pausa();
        clrscr();
      break;

      case 9:
      // (8) - getche -------------------------------------------#
        clrscr();
        printf("Introduce un caracter: ");
        printf("\nCaracter leido: <%c>", getche());
        pausa();
        clrscr();
      break;

      case 10: // salir del menu

      break;
    }
    //cls();
    return 0;

}