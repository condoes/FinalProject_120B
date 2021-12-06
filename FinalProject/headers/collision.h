#ifndef __collision_h__
#define __collision_h_
#include "variables.h"

enum check_collision {col_start, col_check };

int collisionTick(int state) {
	switch(state) {
		case col_start: 
		if(!win_f && !fail_f) { state = col_check; }
		break;

		case col_check:
		state = col_check;
		if(loc == note1pos || loc == note2pos || loc == note3pos) {
			score++;
		}
       
        if(score > W_score) {
		 W_score = score;
            eeprom_update_float((float*)64, W_score);
        }
		if(score >= 5) {win_f = 1;}


		if(loc == obs1pos || loc == obs2pos) {
			if(health > 0) {health--;}
			if(health == 0) { fail_f = 1;}
		}

		default: state = col_start; break;
	}
return state;
}



#endif