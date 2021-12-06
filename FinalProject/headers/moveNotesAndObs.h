#ifndef __moveNotesAndObs_h__
#define __moveNotesAndObs_h__
#include "variables.h"

enum note_notesObs {move_start, move_init};
int moveTick(int state) {
	switch(state) {
	case move_start: 
  
        LCD_CustomChar(1, notes);
		LCD_CustomChar(2, obs);
		state = move_init;
		break;
	
	case move_init:
	   	state = move_init;
		
	    if(!start_f) {restart_f = 1;}
	    else if(start_f && !restart_f){
		if(note1pos > 1 && start_f) { //notes
            		note1pos--;
        	}
		else { note1pos = 16; }

		if(note2pos > 17 && start_f) {
            		note2pos--;
        	}
		else { note2pos = 32; }

		if(note3pos > 1 && start_f) {
            		note3pos--;
        	}
		else { note3pos = 16; }

		if(obs1pos > 1 && start_f) { //obstacles
			obs1pos--;
		}
		else { obs1pos = 16; }
		
		if(obs2pos > 17 && start_f) {
			obs2pos--;
		}
		else { obs2pos = 32; }

		if(fail_f || win_f) {
			note1pos = 6;	
			obs1pos = 19;
			note2pos = 25;	
			obs2pos = 11;
			note3pos = 14;
		}
	}

        break;
	
    default: 
        state = move_start;
        break;
    }

return state;
}


#endif