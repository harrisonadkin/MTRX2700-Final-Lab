#include <hidef.h>      /* common defines and macros */
#include <stdio.h>
#include <string.h>
#include "serialModule.h"
#include "calibrate.h"
#include "derivative.h"
#include "globals.h"


/*#pragma CODE_SEG __NEAR_SEG NON_BANKED 
__interrupt void ButtonISR(void) { 
    
    switch(PTH)
    
}  */

  

void calibrate (void){  
  while(1){
    //create break for end calibrate
    switch(PTH){
      
      case 15:
        // toggle to neutral
        //PWMDTY67 = 1400;
        break;
        
      case 14:
        // 180deg
        //PWMDTY67 = 3000;
        break;
      
      case 13:
        // 0
        break;
      
      case 11:
        // 90
        break;
        
      case 7:
        // ?
        break;
        
    }
  }
}

void servoInit(void) {

    PWMCLK = 0;            //24MHz clock 
    PWMPOL = 0b10100000;   //high then go low pwm wave
    PWMPRCLK = 0b01000100; //prescaler of 16
    PWMCTL = 0b11000000;   //concatanate PWM outputs 45 and 67
    PWMCAE = 0;            //left aligned wave
    PWMPER45 = 30000;      //PWMPER = (50Hz signal * 16 * PWMPER)/ 24 MHz
    PWMDTY45 = 1350;       //1350-3150 PWMDTY = on/off = PWMDTY/PWMPER  
    PWMPER67 = 30000;      //PWMPER = (50Hz signal * 16 * PWMPER)/ 24 MHz
    PWMDTY67 = 2000;       //PWMDTY = on/off = PWMDTY/PWMPER                   
   // PWME = 0b10100000;     //pwm outputs 7 and 5 which are connected 6 and 4 respectively

}

