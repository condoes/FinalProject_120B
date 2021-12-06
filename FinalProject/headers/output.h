#ifndef __output_h__
#define __output_h__
#include "variables.h"

enum lcd_output {output_start, output_check, title, main_game, win, fail};

int outputTick(int state) {
	switch(state) {
	case output_start:
		state = output_check;
		break;

	case output_check:
		if(win_f && !fail_f) {state = win;}
		else if(fail_f && !win_f) {state = fail;}
		else if(restart_f && !start_f && !win_f && !fail_f) {state = title; }
		else if(start_f && !restart_f && !win_f && !fail_f) {state = main_game; }
		break;

	case title:
		score = 0;		
		for(i = 1; i <= msg_size; i++) {
			if(i > 15) { pos = 0; }
			else { pos = i; };
    		LCD_Cursor(pos);
	
	    	((i+j) < msg_size) ?
	    	LCD_WriteData(start_msg[i+j]) :
	    	LCD_WriteData(start_msg[(i+j) - msg_size]);
		}

		j++;
		if(j >= msg_size) {
		    j = 0;
		}
		if(fail_f || win_f) { j = 0; pos = 1; i = 0;} 
		LCD_DisplayString(17, prompt_msg); 
		state = output_check;

	break;

	case main_game:
		LCD_ClearScreen();
		state = output_check;
		LCD_Cursor(note1pos); LCD_WriteData(1);
		LCD_Cursor(note2pos); LCD_WriteData(1);	
		LCD_Cursor(note3pos); LCD_WriteData(1);

		LCD_Cursor(obs1pos); LCD_WriteData(2);
		LCD_Cursor(obs2pos); LCD_WriteData(2);
	break;

	case win:
		R_score = eeprom_read_float((float*)64);
		LCD_DisplayString(1, "Score:");
		LCD_WriteData(score + '0');
		LCD_DisplayString(17, "High Score:");
        	LCD_WriteData(R_score + '0');
		state = output_check;
	break;

	case fail:
        	R_score = eeprom_read_float((float*)64);
		LCD_DisplayString(1, "Failed. Score:");
        	LCD_WriteData(score + '0');
		LCD_DisplayString(17, "High Score:");
        	LCD_WriteData(R_score + '0');
		state = output_check;

	break;

	default: state = output_start; break;
	}

return state;
}


#endif