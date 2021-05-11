#include "timers.h"
#include <hidef.h>
#include "derivative.h"      
#include "globals.h"



void Init_TC5 (void) {
  // set up the timers for channel 5 to use the interrupt
  
  TSCR1 = 0b11110000;   // timer enable, timer stop in wait and freeze, fast flag clear all on
  TSCR2 = 0b00000011;   // no overflow, prescalar 8
  TIOS |= 0b00100000;   // channel 5 to output compare, rest for input capture 
  TCTL1 = 0b00000100;   // channel 5 to toggle OCx output line
  TIE  |= 0b00100000;   // channel 5 timer interrupt enable 
  
}

void Init_Math (void) {
  // set up timer for counting calc time of math functions
  
  TSCR1 = 0b10000000;   // timer enable, stop in wait/freeze, no fast flag clear
  TSCR2 = 0b10000001;   // set prescalar to 2 
  TFLG2 = 0b10000000;
  
}


//create overflow counter scope just this file
int TOFcount = 0;

//create function to clear overflow counter
void clearTOF(void){
  TOFcount = 0;
}

//function that uses overflow to calc clock cycles
unsigned long calcTime(unsigned int time){
  unsigned long timeTaken;
  timeTaken = (TCNT - time + TOFcount*65536);
  clearTOF();
  return timeTaken;  
}

// initialising channel 5 interrupt
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void TC5_ISR(void) { 

  TC5 += frequency; // add delay time to output compare. plays note at correct frequency. 
}

// initialising timer overflow interrupt
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
__interrupt void TOF_ISR(void) { 
  
  TOFcount += 1;
  TFLG2 |= 0b10000000; //reset flag 
} 









