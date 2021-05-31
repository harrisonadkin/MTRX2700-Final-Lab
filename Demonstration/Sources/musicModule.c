#include "musicModule.h"
#include <hidef.h>
#include "derivative.h"
#include "globals.h"




/******************************************************************************
*                                                                             *
*                                                                             *
*                         Music Module Functions                              *
*                                                                             *
*                                                                             *
******************************************************************************/


   // example score: Jupiter theme [THE PLANETS] in b flat 
   // current notes only across scales 3,4,5. No flats or sharps.
   // duration is value multiplied by 10ms. 100 = 1s of note. 
  unsigned int jingle[] = {
    A5, C5, G5, E5, 0};
  unsigned int duration1[] = { 
    250,250,250,500,0};
  
  unsigned int error[] = {
    G6, ZZ, G6, ZZ, G6, 0};
  unsigned int duration2[] = { 
    250,100,250,100,250,0}; 

void bootJingle(void){    
  playnote(jingle, duration1); // pass score and duration pointers into play function
}

void errorSound(void){
  playnote(error, duration2); 
}

// delay function given integer duration (multiplies by 10ms) and delays that amount
void delay1ms(int duration){
  int counter;
  TIOS |= 0b01000000;     // enable channel 6 for output compare
  TC6   = TCNT + 3000;   // set an output compare amount that is 30K cycles after current time

// run through for loop "duration" times that takes 10ms
  for(counter = 0; counter < duration; counter++){
    while(!(TFLG1 & 0b01000000));  // while output compare not reached do nothing
    TC6 += 3000;                  // when output compare reached add another 30K cycles then repeat
  }                                // note 30K was calced using Clockspeed/(10*Amount*prescalar) = 10ms

  TIOS &= 0b10111111;              // turn 6 back off for later use
}


// Takes pointer to score and duration arrays and plays each note for that duration
void playnote(unsigned int * score, unsigned int * duration){
  int i = 0, j = 0;
  
  //while loop to calculate how many notes and total song duration
  while(duration[i]){
    i++;
  }
  
  //while loop that runs through score until termination character 0 and plays each note
  while(score[j]){

    frequency = score[j];
    delay1ms(duration[j]);
    j++;

  }
  // turn off output compares for use later
  TIOS &= 0x11011111;
}

void Init_TC5 (void) {
  // set up the timers for channel 5 to use the interrupt
  TSCR1 = 0b11110000;   // timer enable, timer stop in wait and freeze, fast flag clear all on
  TSCR2 = 0b00000011;   // no overflow, prescalar 8
  TIOS |= 0b00100000;   // channel 5 to output compare, rest for input capture 
  TCTL1 = 0b00000100;   // channel 5 to toggle OCx output line
  TIE  |= 0b00100000;   // channel 5 timer interrupt enable 
    
}

__interrupt void TC5_ISR(void) { 

  TC5 += frequency; // add delay time to output compare. plays note at correct frequency. 
} 









































