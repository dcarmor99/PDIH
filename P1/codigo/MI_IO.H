#include <dos.h>
#include <stdio.h>
#define BYTE unsigned char

// VARIABLES GLOBALES

unsigned int MODO_TEXTO = 3;
unsigned int MODO_VIDEO = 4;

BYTE  COLOR_TEXTO = 7;  // Color del texto. Por defecto gris claro. 
BYTE  COLOR_FONDO = 0;  // Color de  fondo. Por defecto será el 0 (negro)

int ALTO_PANTALLA = 24;
int ANCHO_PANTALLA = 79;

/*  
    *@brief Función Auxiliar - Devuelve la posicion 'x' actual del cursor
    * Devuelve el registro dl, que almacena la columna actual del cursor
    * La función llama a la subfunción 3 de la interrupción nº 10.
    *@return devuelve el valor del registro dl
*/
int posX(void){
    union REGS inregs, outregs;

    inregs.h.ah = 0x03;
    inregs.h.bh = 0x00;

    int86(0x10,&inregs, &outregs);

    return outregs.h.dl;

}

/*
    *@brief Indica la posicion 'y' actual del cursor
    * La funcion llama a la subfuncion 3 de la interrupcion nº 10.
    * Devuelve el registro dh, en el cual se almacena la fila actual
    * donde se encuentra el cursor.
    *@return devuelve el valor del registro dh
*/


int posY(void){
    union REGS inregs, outregs;

    inregs.h.ah = 0x03;
    inregs.h.bh = 0x00;

    int86(0x10,&inregs,&outregs);

    return outregs.h.dh;
}




/*
    * @brief Mueve el cursor a una posición determinada
    * Se llama a la subfuncion 2 de la interrupción nº 10.
    * Se mueve el cursor a la posición que se le indique.

    *@param x Indica la columna de la posición deseada
    *@param y Indica la fila donde se quiere colocar el cursor
*/
void gotoxy(int x, int y){
    union REGS inregs, outregs;
    // en ah introducimos el código de la función AH = 02h
    inregs.h.ah = 0x02;
    // en el registro DH introducimos la fila y en DL la columna
    inregs.h.bh = 0x00; // en BH indicamos la página (por defecto es 0x00)
    inregs.h.dh = y;
    inregs.h.dl = x;

    int86(0x10, &inregs, &outregs);

}

/*
   * @brief Hace una pausa esperando cualquier tecla y continúa
*/

void pausa(void){
   union REGS inregs, outregs;

   printf("\n Pulsa cualquier tecla para continuar...");
   inregs.h.ah = 0x00;
   int86(0x16, &inregs, &outregs);
}


void cls(void){
    union REGS regs;
    regs.h.ah = 15; 
    int86( 0x10, &regs, &regs );
    regs.h.ah = 0; 
    int86( 0x10, &regs, &regs );
}


void poner_color(unsigned char cfondo, unsigned char ctexto){
	union REGS inregs, outregs;
	inregs.h.ah = 0x09;
	inregs.h.al = '*';
	inregs.h.bl = (cfondo << 4) | ctexto;
	inregs.h.bh = 0x00;
	inregs.x.cx = 1;
	int86(0x10,&inregs,&outregs);
	return;
}
/*
 *@brief Selecciona el tipo de cursor
 *@param tipo_cursor  0- invisible 1- normal 2- grueso
*/
void setcursortype(int tipo_cursor){
    union REGS inregs, outregs;
    inregs.h.ah = 0x01;
    switch(tipo_cursor) {
        case 0: // invisible
            inregs.h.ch = 010;
            inregs.h.cl = 000;
            break;
        case 1: // normal
            inregs.h.ch = 010;
            inregs.h.cl = 010;
            break;
        case 2: // grueso
            inregs.h.ch = 000;
            inregs.h.cl = 010;
            break;
    }
    int86(0x10, &inregs, &outregs);
}

/*
 *@brief Fija el modo de video deseado
 *@param BYTE modo 3-texto 4-gráfico
*/
void setvideomode(BYTE modo){
    union REGS inregs, outregs;
    inregs.h.al = modo;
    inregs.h.ah = 0x00;
    int86(0x10, &inregs, &outregs);
}

/*
*   @brief Pone un pixel en la coordenada X,Y
*/

void pixel(int x, int y, BYTE C){
    union REGS inregs, outregs;
    inregs.x.cx = x;
    inregs.x.dx = y;
    inregs.h.al = C;
    inregs.h.ah = 0x0C;
    int86(0x10,&inregs, &outregs);
}

/*
    *@brief Obtiene el modo de video actual
    *@return unsigned int con el modo de video
*/

unsigned int getvideomode(void)
{
    union REGS inregs, outregs;

    inregs.h.ah = 0xF;
    int86(0x10, &inregs, &outregs);

    return outregs.h.al;

}


/*
    *@brief Modifica el color de primer plano con que se mostraran los caracteres
    * Esta funcion modifica la variable global COLOR_TEXTO
*/

void textcolor(int color)
{
    COLOR_TEXTO = color; // COLOR_TEXTO contiene el color con el que se escribe en la consola
}

/*
    * @brief Modifica el color de fondo con que se muestran los caracteres
    * Esta funcion modifica la variable global COLOR_FONDO
*/

void textbackground(int color)
{
    COLOR_FONDO = color; // COLOR_FONDO contiene el color de fondo de la consola.
}

/*
    *@brief Escribe un caracter en pantalla con el color indicado en las variables
    * COLOR_TEXTO y COLOR_FONDO
    * AL = CARACTER
    * BL = COLOR>(DE TEXTO Y DE FONDO)
    * CX = Nº REPETICIONES
*/
void cputchar(char caracter, int reps){
    union REGS inregs, outregs;

    inregs.h.ah = 0x09; // Subfuncion nº 9 , permite escribir un caracter en pantalla

    inregs.h.al = caracter;
    inregs.h.bl = (COLOR_FONDO << 4) | COLOR_TEXTO;
    inregs.h.bh = 0x00;
    inregs.x.cx = reps;

    int86(0x10, &inregs, &outregs);
}

/*
    *@brief Desplaza toda la pantalla una línea hacia arriba
    *Se llama a la subfuncion 6 de la interrupcion numero 10 (Interrupción BIOS de vídeo)
    * Esta subfuncion desplaza toda la pantalla hacia arriba un nº x de lineas
    * que se le indiquen. Si se indican 0 lineas, se borra la pantalla entre los puntos que
    * se quieran(mediante lsi,csi,lid,cid).
    *@param lineas Nº de lineas que se desean desplazar. 0 para borrar
    *@param color  Color de relleno para espacios en blanco
    *@param l_sup_izq    Linea superior izquierda. Línea desde la que queremos comenzar a desplazar/borrar.
    *@param c_sup_izq    Columna superior izquierda. Columna desde la que se comienza a desplazar/borrar
    *@param l_inf_dch    Linea inferior derecha. Linea final hasta la que se desea desplazar/borrar
    *@param c_inf_dch    Columna inferior derecha. Columna final hasta la que se desea desplazar/borrar
*/

void desliza_arriba(int lineas, int color, int l_sup_izq, int c_sup_izq, int l_inf_dch, int c_inf_dch)
{
    union REGS inregs, outregs;

    inregs.h.ah = 0x06;

    inregs.h.al = lineas;
    inregs.h.bh = color;
    inregs.h.ch = l_sup_izq;
    inregs.h.cl = c_sup_izq;
    inregs.h.dh = l_inf_dch;
    inregs.h.dl = c_inf_dch;
    
    int86(0x10,&inregs, &outregs);

    //Una vez desplazada la pantalla , movemos el cursor el mismo nº de líneas
    gotoxy(posX(), posY()-lineas);

}

/*
*@brief Borra toda la pantalla
* Esta funcion borra la pantalla llamando a la funcion desliza_arriba, que desliza
* la pantalla hacia arriba tantas lineas como alto tenga la consola. Y al final situa el
* cursor en la posición (0,0).
*/
void clrscr(void){
    int color = COLOR_FONDO << 4 | COLOR_TEXTO;

    desliza_arriba(ALTO_PANTALLA+1,color,0,0,ALTO_PANTALLA,ANCHO_PANTALLA);
    gotoxy(0,0);
}

/*
* @brief Obtiene el caracter de teclado y lo muestra en pantalla
* Se llama primero a la subfunción 0 de la interrupción numero 16.
* Dicha subfuncion lee un caracter desde el teclado y lo almacena
* en el regsitro al.
*
*@return Decimal que representa el caracter introducido por el teclado.
*
*/
int getche(void){
    union REGS inregs, outregs;
    int character;

    inregs.h.ah = 0x00;

    // Llamamos a la interrupcion 0x16 que gestiona el teclado
    int86(0x16,&inregs,&outregs);

    // Hacemos distincion de si se trata de un caracter especial o no.
    // Caracteres especiales --> 0
    // Caracteres normales   --> 1
    if(outregs.h.al != 0)
        character = outregs.h.al;
    else
        character = outregs.h.ah;
    
    // Llamamos a cputchar para escribirlo en pantalla
    cputchar(character,1);
    return character;
}


