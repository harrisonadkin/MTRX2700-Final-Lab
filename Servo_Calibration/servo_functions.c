#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>
#include "servo_functions.h"
#include "delay.h"

//servo functions

void servo_setup(void){
  

  PWMCLK = 0;        // 24MHz clock
  PWMPOL = 0b10100000; //start high then go low
  PWMPRCLK = 0b01000100; //prescaler of 16
  PWMCTL = 0b11000000; //concatanate 
  PWMCAE = 0; //left align
  PWMPER45 = 30000; //PWMPER = (50Hz signal * 16 * PWMPER)/ 24 MHz
  PWMDTY45 = 2250; //1350-3150 PWMDTY = on/off = PWMDTY/PWMPER  
  PWMPER67 = 30000; //PWMPER = (50Hz signal * 16 * PWMPER)/ 24 MHz
  PWMDTY67 = 2200; //PWMDTY = on/off = PWMDTY/PWMPER  
  PWME = 0b10100000;
  //delay_movement(10);
  
}

int servo_demo(void){

  int i = 2200;
  int j = 2250;
  
  for(;;){
    
    if (PTH == 0b11111110){
        i++;
        PWMDTY67 = i;
        PWME = 0b00000000;
        PWME = 0b10000000;
        //delay_movement(1); 
    
  }
  if (PTH == 0b11111101){
        i--;
        PWMDTY67 = i;
        PWME = 0b00000000;
        PWME = 0b10000000; 
        //delay_movement(1); 
  }
  if (PTH == 0b11111011){
        j++;
        PWMDTY45 = i;
        PWME = 0b00000000;
        PWME = 0b00100000;
        //delay_movement(1);  
    
  }
  if (PTH == 0b11111110){
        j--;
        PWMDTY45 = i;
        PWME = 0b00000000;
        PWME = 0b00100000;
        //delay_movement(1);  
    
  }
  if (PTH == 0b11111100){
        return 1;  
    
  }
  
  
  
}
}


  