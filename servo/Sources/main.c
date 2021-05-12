#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>
#include "kalman.h"
int i,j;



void main(void) {
  //put your own code here 
  PWMCLK = 0;        // 24MHz clock
  PWMPOL = 0b10100000; //start high then go low
  PWMPRCLK = 0b01000100; //prescaler of 16
  PWMCTL = 0b11000000; //concatanate 
  PWMCAE = 0; //left align
  PWMPER45 = 30000; //PWMPER = (50Hz signal * 16 * PWMPER)/ 24 MHz
  PWMDTY45 = 1350; //1350-3150 PWMDTY = on/off = PWMDTY/PWMPER  
  PWMPER67 = 30000; //PWMPER = (50Hz signal * 16 * PWMPER)/ 24 MHz
  PWMDTY67 = 2000; //PWMDTY = on/off = PWMDTY/PWMPER                   
  PWME = 0b10100000;
  
	EnableInterrupts;

  for(;;) {
  
    /*for (i = 1350; i < 3000; i++) {
      //delay(1000);
      PWMDTY67 = i;
      
    }*/
    for (i = 3000; i > 1400; i--) {
      //delay(1000);
      PWMDTY67 = i;
      
    } 

    _FEED_COP(); /* feeds the dog */
  //} /* loop forever */
  /* please make sure that you never leave main */
  }
}
