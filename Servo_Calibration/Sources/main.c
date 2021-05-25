#include <hidef.h>      /* common defines and macros */
#include "derivative.h"
#include "delay.h"
#include "servo_functions.h"      /* derivative-specific definitions */



void main(void) {
  /* put your own code here */
 	EnableInterrupts;
  servo_setup();
  //delay_setup();
  //delay_movement(1);
  servo_demo();
  
  
  

;


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
