#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <curses.h>
#include <ncurses.h>
#include "screen.h"
#include "alu.h"
#include "flags.h"
#include "decoder.h"


#define NORMAL       0
#define BRILLO       1
#define SEMIBRILLO   2
#define INTERMITENTE 5
#define INVERSO      7
#define NEGRO       30
#define ROJO        31
#define VERDE       32
#define MARRON      33
#define AZUL        34
#define ROSA        35
#define CELESTE     36
#define BLANCO      37

#define MAXLINEAS 15
#define MAXCAD 70

WINDOW *win; /** manejaremos una única ventana de pantalla completa **/
int Disp(void);
void Inivideo(void);
void Exit(void);

void IniVideo(void){/*Para los colores */
	win=initscr();/* Inicia modo curses */
	clear();
	refresh();
	noecho();/* No imprimir los caracteres leidos */
	cbreak();
	curs_set(0);	/* Cursor Invisible */
	keypad(stdscr, TRUE);/* Obtener F1, F2, etc */
 	border( ACS_VLINE, ACS_VLINE,
			ACS_HLINE, ACS_HLINE,
			ACS_ULCORNER, ACS_URCORNER,
			ACS_LLCORNER, ACS_LRCORNER	);
	if(has_colors()) {
	         start_color();/* Permite manejar colores */
	         init_pair(1, COLOR_RED, COLOR_GREEN);
	         init_pair(2, COLOR_WHITE, COLOR_GREEN);
	         init_pair(3, COLOR_GREEN, COLOR_BLACK);
	         init_pair(4, COLOR_WHITE, COLOR_RED);
	         init_pair(5, COLOR_BLUE, COLOR_GREEN);
        }
        bkgd(COLOR_PAIR(5));/*color del fondo*/

}


void Exit(void){
        
        clear();
        refresh();
        endwin();
        exit(1);
}



int main(void)
{
	IniVideo();  
	Disp();     
    Exit();  
    return 0;  
}

int Disp(void){
	
	
	char ch='0';

		int i, num_instructions;
		ins_t read;
		char** instructions;
		instruction_t instruction;
		uint32_t pcou=0;
		uint32_t memoria=500;
		num_instructions = readFile("code.txt", &read);
		if(num_instructions==-1)
			return 0;

		if(read.array==NULL)
			return 0;

		instructions = read.array; /* Arreglo con las instrucciones */




	/* Ejemplo de uso
		Llama la función que separa el mnemonico y los operandos
		Llama la instrucción que decodifica y ejecuta la instrucción
	*/
	instruction = getInstruction(instructions[1]); /* Instrucción en la posición 0*/
while(pcou<memoria){
            if(pcou>=num_instructions){
                mvprintw(LINES,COLS/2,"\nLimite de instrucciones alcanzado\n");
                getch();
                break;
            }
            
            instruction = getInstruction(instructions[pcou]);
            decodeInstruction(instruction);
            ch = getch();
			if(ch=='u'){
			timeout(1000);}
            if(ch=='p'){
            timeout(-1);}
			if(ch=='q'){
			Exit();
			}
			
            obtenerPC(&pcou);

        }
refresh();
for(i=0; i<num_instructions;i++){
		free(read.array[i]);
	}
	free(read.array);
	return 0;



}
