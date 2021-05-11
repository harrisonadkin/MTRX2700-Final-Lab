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

// create module wide scope functions for remaining notes + time.
int timeRemaining;
int notesRemaining;

   // example score: Jupiter theme [THE PLANETS] in b flat 
   // current notes only across scales 3,4,5. No flats or sharps.
   // duration is value multiplied by 10ms. 100 = 1s of note. 
  unsigned int score[] = {
    A3,C4,D4,ZZ,D4,F4,E4,C4,F4,G4,F4,E4,D4,E4,D4,C4,A3,
    ZZ,A3,C4,D4,ZZ,D4,F4,E4,C4,F4,G4,A4,ZZ,A4,ZZ,A4,G4,F4,G4,F4,
    C5,A4,G4,ZZ,G4,F4,A4,G4,C4,C5,A4,G4,ZZ,G4,A4,C5,D5,
    ZZ,D5,E5,F5,E5,D5,C5,E5,A4,G4,F4,G4,A4,C5,0};
  unsigned int duration[] = { 
    100,100,100,3,50,50,75,25,50,50,100,100,50,50,100,100,200,
    3,50,50,100,3,50,50,75,25,50,50,100,3,100,3,50,50,100,100,200,
    50,50,100,3,100,50,50,100,100,50,50,100,3,100,50,50,200,
    3,50,50,100,100,100,100,100,100,50,50,100,100,200,0};

int scoreFunc(void){    
  playnote(score, duration); // pass score and duration pointers into play function
	return flag;
}

// delay function given integer duration (multiplies by 10ms) and delays that amount
void delay10ms(int duration){
  int counter;
  TIOS |= 0b01000000;     // enable channel 6 for output compare
  TC6   = TCNT + 30000;   // set an output compare amount that is 30K cycles after current time

// run through for loop "duration" times that takes 10ms
  for(counter = 0; counter < duration; counter++){
    while(!(TFLG1 & 0b01000000));  // while output compare not reached do nothing
    timeRemaining -= 1;
    TC6 += 30000;                  // when output compare reached add another 30K cycles then repeat
  }                                // note 30K was calced using Clockspeed/(10*Amount*prescalar) = 10ms

  TIOS &= 0b10111111;              // turn 6 back off for later use
}



// Takes pointer to score and duration arrays and plays each note for that duration
void playnote(unsigned int * score, unsigned int * duration){
  int i = 0, j = 0;
  
  //while loop to calculate how many notes and total song duration
  while(duration[i]){
    timeRemaining += duration[i];
    notesRemaining += 1;
    i++;
  }
  
  //while loop that runs through score until termination character 0 and plays each note
  while(score[j]){

    frequency = score[j];
    delay10ms(duration[j]);
    notesRemaining -= 1;
    j++;

  }
  // turn off output compares for use later
  TIOS &= 0x11011111;
  flag = 1; 
}











































