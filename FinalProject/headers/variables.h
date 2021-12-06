#ifndef __variables_h__
#define __variables_h__

//flags
unsigned char up_f, down_f = 0; //up and down
unsigned char start_f = 0; //start
unsigned char restart_f = 1; //restart
unsigned char win_f, fail_f = 0; //win and fail

//note & obst. positions
unsigned char note1pos = 6;	unsigned char obs1pos = 19;
unsigned char note2pos = 25;	unsigned char obs2pos = 11;
unsigned char note3pos = 14;

//custom chars
unsigned char player[8] = {0xE, 0xA, 0xE, 0x15, 0xE, 0x04, 0xA, 0x11}; 
unsigned char notes[8] = { 0x04,0x06, 0x05,0x04,0x0C,0x1C,0x0C, 0x00 };
unsigned char obs[8] = {0x00,  0x0E,  0x15,  0x1B,  0x0E,  0x0E,  0x00,  0x00 };

//counters
unsigned i, pos, j = 0;
unsigned char loc = 0;
unsigned char health = 1; //starting health

//display arrays
unsigned char start_msg[] = "     Welcome to Rhythm Dash!!!";
unsigned char prompt_msg[] = "Tap A3 to start!";
unsigned char row[16];
unsigned char msg_size = sizeof(start_msg)/sizeof(start_msg[0]);
unsigned char prompt_size = sizeof(prompt_msg)/sizeof(prompt_msg[0]);

//eeprom vars
float W_score, R_score; //write, read
float score = 0; //temp
unsigned char high_score[1]; //buffer

#endif