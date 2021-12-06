#ifndef __inputs_h__
#define __inputs_h__
#include "adc.h"
#include "scheduler.h"
#include "variables.h"

const unsigned char VRy = 1;

enum read_joystick {j_start, read};
enum button_check {b_start, b_press, b_rel, start_set, restart_set};

int joystickTick(int state) {
	switch(state) {
	case j_start: state = read; break;

	case read:

	if(ADC_read(VRy) < 175) { up_f = 1; down_f = 0;} //up
	else if(ADC_read(VRy) > 530) {down_f = 1; up_f = 0;} //down
	state = read;
	break;

	default: state = j_start; break;
	}

return state;
}

int buttonTick(int state) {
    switch (state)
    {
    case b_start:
        state = b_press;
        break;

    case b_press:
        if((~PINA & 0x18) == 8) {
            state = restart_set;
        }
	else if((~PINA & 0x18) == 16) {
		state = start_set;
	}
        break;

	case start_set:
		start_f = 0; restart_f = 1; win_f = 0; fail_f = 0;
		state = b_rel;
		break;

	case restart_set:
		start_f = 1; restart_f = 0; win_f = 0; fail_f = 0;
		state = b_rel;
		break;

    case b_rel:
	if((~PINA & 0x18) == 0) {
		state = b_press;	
	}
	else { state = b_rel;} 
	break;
 
    default:
        state = b_start;
        break;
    }

    return state;
}


#endif