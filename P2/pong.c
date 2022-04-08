#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define DELAY 3000000


int main(int argc, char * argv[])
{


int fils, cols;
int x = 0, y = 0;
int num = 0;


//------------------------------------------------------------------------------
// Pantalla principal
  initscr();
  
  
  
  
	 start_color();
	 
	 init_pair(1, COLOR_YELLOW, COLOR_GREEN);
	 init_pair(2, COLOR_BLACK, COLOR_WHITE);
	 init_pair(3, COLOR_WHITE,COLOR_BLUE);
	 clear();
	 
	 
	 refresh();
  	 curs_set(0);
  	 getmaxyx(stdscr,fils,cols);
  
  //clear();

  
    WINDOW *window = newwin(fils, cols, 0, 0);
    wbkgd(window, COLOR_PAIR(3));
  
  
  
  mvprintw(4,0,"\t	   oooooooooo                                        \n"
               "\t           888    888  ooooooo    ooooooo    oooooooo8       \n"
               "\t           888oooo88 888     888 888   888  888    88o       \n"
               "\t           888       888     888 888   888   888oo888o       \n"
               "\t          o888o        88ooo88  o888o o888o 888     888      \n"
               "\t                                             888ooo888     \n\n"
               "\t Creado por Daniel Carrasco Moreno <dcarmor@correo.ugr.es>     \n"
               "\t \t\t\tPlayer 1 CONTROLES: 'Q' (ARRIBA)       'A' (ABAJO)         \n"
               "\t \t\t\tPlayer 2 CONTROLES: FLECHA ARRIBA      FLECHA ABAJO\n"
          
               "\t \t\t\tPulsar cualquier tecla para empezar..." ); 
  
  
  refresh();
  getch();
  clear();


//------------------------------------------------------------------------------
// Juego
	
	keypad(stdscr,true);
	
	// Rango de movimiento
	int max_y = fils, max_x = cols;
	int next_x = max_x/2;
	int next_y = max_y/2; 
	
	
	x = next_x;
	y = next_y;
	
	
	// posicion del jugador 1
    int pos_p1_x = 0;
    int pos_p1_y = 0;	
	
	// posicion del jugador 2
    int pos_p2_x = max_x - 1;
    int pos_p2_y = 0;	
	
	// direccion de la pelota
    int dir_x = 1;
    int dir_y = 1;	
	
    //Puntuaciones
    int puntos_player1 = 0;
    int puntos_player2 = 0;	
	
	
	//init_pair(2, COLOR_WHITE,COLOR_BLUE);
	//noecho();
	//curs_set(FALSE);
	timeout(50);


    //WINDOW *window2 = newwin(fils, cols, 0, 0);
    //wbkgd(window2, COLOR_PAIR(2));

	//box(window2, '|', '-'); 

    wbkgd(window, COLOR_PAIR(2));
    wrefresh(window);

    int N = max_y/2;
    int M = 0;
    
	while(1)
	{
		clear();
		
		//Score 
        mvprintw(0, max_x/2 - 11, "PLAYER 1: %d |  PLAYER 2: %d",puntos_player1,puntos_player2);
        mvvline(0,max_x/2,ACS_VLINE,max_y);
        
        // pintar pelota

        //next_y =  rand () % (N-M+1) + M;
        
        mvprintw(next_y, next_x, "o");
        
        //Pintar al jugador 1
        mvprintw(pos_p1_y + 1, pos_p1_x,"|");
        mvprintw(pos_p1_y + 2, pos_p1_x,"|");
        mvprintw(pos_p1_y + 3, pos_p1_x,"|");
        mvprintw(pos_p1_y + 4, pos_p1_x,"|");
        
        //Pintar al jugador 2
        mvprintw(pos_p2_y + 1, pos_p2_x,"|");
        mvprintw(pos_p2_y + 2, pos_p2_x,"|");
        mvprintw(pos_p2_y + 3, pos_p2_x,"|");
        mvprintw(pos_p2_y + 4, pos_p2_x,"|");
        
        //refresh();
        
 		//Movimiento de la pelota
 		//y = rand () % (N-M+1) + M;
        next_y = y + dir_y;
        next_x = x + dir_x;        
        
        //Calculo del movimiento pelota eje y
        if (next_y >= max_y || next_y <= 0)
        {
            dir_y *= -1;
        }else{
            y += dir_y ;
        }        
        
        
        //Calculo del movimiento pelota eje x
        if (next_x == pos_p2_x && (next_y <= pos_p2_y + 4 && next_y >= pos_p2_y)){
            dir_x *= -1;
        } 
        else if (next_x == pos_p1_x && (next_y <= pos_p1_y + 4 && next_y >= pos_p1_y)){
            dir_x *= -1;
        }else{
            x += dir_x;
        }       
        
        //Scores
        if (next_x > pos_p2_x){
            next_x = max_x/2;
            //next_y = max_y/2;
            next_y = rand () % (N-M+1) + M;;
            x = max_x / 2;
            //y = max_y / 2;
            y = rand () % (N-M+1) + M;;
            puntos_player1++;
        } 
        else if (next_x < pos_p1_x){
            next_x = max_x/2;
            //next_y = max_y/2;
            next_y = rand () % (N-M+1) + M;;
            x = max_x / 2;
            //y = max_y / 2;
            y = rand () % (N-M+1) + M;;
            puntos_player2++;
        }     
       

        switch (getch())
        {

            //Movimiento jugador 1
            case 'w':
                if (pos_p1_y >= 2)
                    pos_p1_y -= 1;
                break;

            case 's':
                if (pos_p1_y + 3 <= max_y - 3)
                    pos_p1_y += 1;
                break;

            //Movimiento jugador 2
            case KEY_UP:
                if (pos_p2_y >= 2)
                    pos_p2_y -= 1;
                break;

            case KEY_DOWN:
                if (pos_p2_y + 3 <= max_y - 3)
                    pos_p2_y += 1;
                break;

            default:
                break;
        }
        
        //next_y = rand () % (N-M+1) + M;
		
		
	}
 	endwin();
}
