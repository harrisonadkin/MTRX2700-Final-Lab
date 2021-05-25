//Delay function for servo movement

#include "delay.h"
#include "derivative.h"


void delay_movement(int kk){
  int counter;
  TIOS |= 0b01000000;
  TC6 = TCNT + 30000;
  
  for(counter = 0; counter < kk; counter++){
    while(!(TFLG1 & 0b01000000));
    TC6 += 30000;
  }
  
  TIOS &= 0b10111111;
}

void delay_setup(void){
  TSCR1 = 0b11110000;
  TSCR2 = 0b00000011;
  //TIOS |= 0b00100000;
 // TCTL1 = 0b00000100;
 // TIE  |= 0b00100000;
  
}
