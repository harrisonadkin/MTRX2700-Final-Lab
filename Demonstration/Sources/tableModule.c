#include "mathModule.h"
#include "string.h"
#include <stdio.h>
#include <hidef.h>
#include "derivative.h"
#include "tableModule.h"
#include "serialModule.h"
#include "timers.h"
#include "globals.h"

/******************************************************************************
*                                                                             *
*                                                                             *
*                         Table Module Functions                              *
*                                                                             *
*                                                                             *
******************************************************************************/


int i = 0;
char heading[16] = "   \0";
char str[16]; 
char *writeString = &str[0]; 


void createTable (void){
  
  
  Init_Math();
  mathTimer(output);
  
  
  
  //for(i = 0; i < 6; i++){
  
 
 /* if(i==0){
    serialInitialise(156, SCI1, WRITE, &heading);
    sprintf(heading, "%s","INT            \0");
    serialInitialise(156, SCI1, WRITE, &heading);
    sprintf(heading, "%s","LONG           \0");
    serialInitialise(156, SCI1, WRITE, &heading);
    sprintf(heading, "%s","32BIT FL       \0");
    serialInitialise(156, SCI1, WRITE, &heading);
    sprintf(heading, "%s","64BIT FL   \r\n\0");
    serialInitialise(156, SCI1, WRITE, &heading);
    

  } */
  //}  
  
  
  for(i = 0; i < 24; i++){
    sprintf(&str[0], "%8.2lf | \r\n\0", output[i]);
    serialInitialise(156, SCI1, WRITE, &str[0]);
  }
}  