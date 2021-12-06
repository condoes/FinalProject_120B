#ifndef __INGAME_H__
#define __INGAME_H__
#include "scheduler.h"
#include "variables.h"

enum in_game {game_start, game_init, char_controls };

int inGameTick(int state) {
	switch(state) {
	case game_start: 
		state = game_init; 
		break;
	
	case game_init:
		LCD_CustomChar(0, player);
		if(start_f && !restart_f && !win_f && !fail_f) {
			loc = 1; LCD_Cursor(loc); LCD_WriteData(0); LCD_ClearScreen(); 
			state = char_controls; }
	
	break;

	case char_controls:
		restart_f = 0;
		
		state = char_controls;
		if(up_f) { 
			loc = 1;	
		}
		else if(down_f) {
			loc = 17;
		}
		LCD_Cursor(loc);
		if(!win_f && !fail_f && !restart_f && start_f) {LCD_WriteData(0);}

	    break;

	default: 
        state = game_start; 
        break;
	}

return state;
}




#endif