#include <hidef.h>      /* common defines and macros */
#include <stdio.h>
#include <string.h>
#include "derivative.h" /* derivative-specific definitions */
#include "help.h"
#include "pll.h"
#include "iic.h"


  

void main(void) {
  /* put your own code here */
  
  EnableInterrupts;
  printHelp();
  

  while(1){                   // BJORK the swedish dog
  
   // flag is set to 1 on completion, use this to print to serial
   // time and notes remaining are shifting during play, print this to serial too.

  }
}

