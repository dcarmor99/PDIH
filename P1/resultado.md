# PRÁCTICA 1: Entrada/Salida utilizando interrupciones con lenguaje C

*Autor: Daniel Carrasco Moreno (Grado de Ingeniería Informática, Universidad de Granada)*

En esta práctica vamos a acceder a las rutinas de servicio a interrupción de la BIOS , tanto para teclado como para video, usando DOSBOX.Vamos a utilizar el lenguaje de programación C para realizar interrupciones software a través de la función no estándar int86().

El objetivo principal de esta primera práctica era implementar 9 funciones similares a las ofrecidas por la biblioteca conio.lib (Console Input Output Library).

Estas son las 9 funciones implementadas:
- `gotoxy`
- `setcursortype`
- `getvideomode`
- `textcolor`
- `textbackground`
- `clscr`
- `cputchar`
- `getche`


### Menu

En primer lugar, he implementado un sencillo menú a través de un simple `switch` en el cual, introduciendo un número del [1-10], nos ejecutará cada una de las funciones anteriormente nombradas.

![](capturas/1.png)

### [1] gotoxy - Colocar cursor en una posicion determinada

![](capturas/2.png)
![](capturas/3.png)
![](capturas/4.png)
