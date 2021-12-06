/*	Author: Cindy Do
 *  Partner(s) Name: 
 *	Lab Section: 
 *	Assignment: Final Project
 *	Exercise Description: [optional - include for your own benefit]

	Things I worked on in this demo: custom characters, EEPROM
	sources used: https://www.electronicwings.com/avr-atmega/analog-joystick-interface-with-atmega-16-32

	!!! DEMO VIDEO: 

 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h> //EEPROM
#include "io.h"
#include "inputs.h"
#include "output.h"
#include "collision.h"
#include "inGame.h"
#include "moveNotesAndObs.h"
#include "adc.h"
#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
#include "scheduler.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;

    static task task1, task2, task3, task4, task5, task6;
    task *tasks[] = { &task1, &task2, &task3, &task4, &task5, &task6};
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

    const char start = -1;

    task1.state = start;
    task1.period = 50;
    task1.elapsedTime = task1.period;
    task1.TickFct = &buttonTick;

    task2.state = j_start;
    task2.period = 50;
    task2.elapsedTime = task2.period;
    task2.TickFct = &joystickTick;

    task3.state = game_start;
    task3.period = 20;
    task3.elapsedTime = task3.period;
    task3.TickFct = &inGameTick;

    task4.state = move_start;
    task4.period = 200;
    task4.elapsedTime = task4.period;
    task4.TickFct = &moveTick;

    task5.state = output_start;
    task5.period = 100;
    task5.elapsedTime = task5.period;
    task5.TickFct = &outputTick;

    task6.state = col_start;
    task6.period = 100;
    task6.elapsedTime = task6.period;
    task6.TickFct = &collisionTick;

    ADC_init();
    TimerSet(10);
    TimerOn();
    LCD_init();


    unsigned short i = 0;
    while (1) {
	
        for(i = 0; i < numTasks; i++) {
            if(tasks[i]->elapsedTime == tasks[i]->period) {
                tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
                tasks[i]->elapsedTime = 0;
            }
            tasks[i]->elapsedTime += 10;
        }
        while(!TimerFlag);
        TimerFlag = 0;
    }
    return 1;
}