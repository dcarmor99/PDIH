# PRÁCTICA 2: Uso de bibliotecas de programación de interfaces de usuario en modo texto

*Autor: Daniel Carrasco Moreno (Grado de Ingeniería Informática, Universidad de Granada)*


El objetivo de la práctica 2 son:

- Instalar la librería ncurses en Linux
- Crear programas sencillos basados en ncurses

<div style="text-align: justify">
En la primera parte de la práctica 2 vamos a instalar la librería ncurses, esencial para comenzar a realizar las siguientes partes de la práctica.
</div>). 
</div>
<br/>

Para instalar hacemos uso del siguiente comando:
```Bash
sudo apt-get install libncurses5-dev libncursesw5-dev
```

En mi caso, he utilizado una máquina virtual con Ubuntu (versión 20.04 LTS ) de su página oficial [Ubuntu](https://ubuntu.com/download "Pagina oficial de Ubuntu").

![](img/cap_1.png)


### [1] Programas de ejemplo

A continuación vamos a comprobar el funcionamiento de los programas de ejemplo del guion.


#### Programa 1 : Mostrar una ventana en el terminal
<div style="text-align: justify">
Este sencillo programa va a mostrar una pantalla con color de fondo azul
y mostrará una cadena de texto en ella.

Primero debemos mostrar la ventana, con sus marcos y un color de fondo y
por otro lado, para mostrar los colores y el fondo de la vetana, debemos crear "pares de colores".


En el código en primer lugar nos encargamos de iniciar , crear y configurar el soporte para colores:

Algunas de las funciones más relevantes que utilizaremos son:

- `has_colors()`  Comprueba si el terminal permite mostrar colores
- `start_color()` Inicia el soporte de colores en la aplicación
- `init_pair()` Crea nuevos pares de colores de fondo y de caracteres,  le asigna un número al nuevo par.
- `clear()` Limpia el contenido de la ventana

Luego, procedemos con la configuración de la ventana, para ello hacemos uso de las siguientes funciones:

- `getmaxyx()` : Calcula el tamaño en caracteres del terminal.
- `newwin()`   : Crea una nueva ventana del tamaño que indiquemos.
- `wbkgd()`    : Establece el color de fondo y de caracteres de la nueva ventana, en este caso será azul.
- `box()`      : Dibuja los marcos de la ventana recién creada.
- `mvwprintw()`: Muestra el contenido (cadenas, numeros, etc) en la ventana actual.
- `wrefresh()` : Refresca el contenido para mostrar en la ventana los últimos cambios.   

Código del programa (ventana.c):

</div>
<br/>
<div style="text-align: center"><img src="img/cap_2.png" /></div>
<div style="text-align: center"><img src="img/cap_3.png" /></div>

<div style=""><img src="img/gif_1.gif" /></div>

#### Programa 2 : Mover una "pelotita" en pantalla
<div style="text-align: justify">

En este ejemplo se va a hacer el movimiento de una pelota (que no es más que el carácter 'o') en pantalla.

El programa en resumidas cuentas, lo que hace es , en un bucle infinito dibujar el caracter 'o' en distintas posiciones, en un rango horizontal determinado por max_y y max_x. Cuando la posición de 'o' sobrepase dicho umbral, se cambia la dirección (que no es más que multiplicar por -1, sentido opuesto).

Antes de realizar el cálculo de la siguiente posición, se hace una breve interrupcion de la ejecución de un DELAY de 30000 microsegundos.

Para compilar:<br/>
![](img/cap_4.png)

</div>
<div style=""><img src="img/cap_5.png" /></div>
<div style=""><img src="img/ex_2.gif" /></div>

### [2] Juego "pong"
<div style="text-align: justify">
La segunda parte de esta práctica, voy a crear una sencilla versión del videojuego "Pong" en C, a partir del ejemplo de la pelotita. 
Al inicio del juego, he programado una ventana que de la bienvenida y muestre , junto con un sencillo "logo" , los controles del juego para cada jugador.

Tras una pausa de unos 3 segundos, se iniciará el juego en sí mismo. 

`Diseño e implementación`

En primer lugar, el movimiento tanto de la pelota como de cada uno de los 2 jugadores , he utilizado las variables x,y y las variables next_x y next_y, que representan la siguiente posición de la pelota para un instante t.

Al inicio del programa, quiero que la pelota comienze desde el centro del campo, luego para ello el valor de x e y será la mitad de las coordenadas x e y del terminal.

EL movimiento de los jugadores viene determinado por las variables pos_p1_x , pos_p1_y (para el jugador 1 ) y pos_p1_x , pos_p1_y (para el jugador 2).

La dirección de la pelota viene determinado, para cada coordenada, por el valor 1 o -1 en función de si va al campo contrario o le regresa al jugador.

En cuanto al cáculo de los movimientos he seguido el siguiente razonamiento:

- Si la pelota llega a los márgenes tanto superior como lateral del terminal, cambia la dirección.
- En caso contrario, sigue en la dirección actual. (Avanza 1 para cada coordenada).

- Para lograr, un comportamiento más real y semejante al juego "pong" original, para que la pelota no haga siempre el mismo recorrido, una vez que un jugador puntúe en campo contrario, por medio de un sencillo generador de números aleatorios en el rango del  eje Y de la pantalla, la pelota saldrá desde distintas posiciones al sacar , en lugar de siempre desde el medio campo. Aumentando así su dificultad.
</div>
<div style=""><img src="img/partida_pong.gif" /></div>

