#include <hidef.h>      /* common defines and macros */
#include <stdio.h>
#include <string.h>
#include "help.h"
#include "serialModule.h"
#include "derivative.h"
#include "globals.h"
#include "musicModule.h"
#include "lcdModule.h"

void printHelp(void){
  unsigned char *readString = 0;
  unsigned char *readString2 = 0;
  char *writeString1 = "Welcome to our Gimbal\r\n\0";
  char *writeString3 = "Please press enter key to calibrate the device\r\n\0";
  char *writeString4 = "Beginning Calibration\r\n\0";
  char *newline = "\r\n\0";
  char *lcdString = "Booting Up";
    
  
  serialInitialise(156,SCI1,WRITE,&writeString1);
  serialInitialise(156,SCI1,WRITE,&newline);
  serialInitialise(156,SCI1,WRITE,&newline);
  serialInitialise(156,SCI1,WRITE,&writeString3);
  serialInitialise(156,SCI1,WRITE,&newline);
  serialInitialise(156,SCI1,READ,&readString);
  serialInitialise(156,SCI1,WRITE,&writeString4);
  
  
  Init_TC5();
  bootJingle();
  
  
  InitLCD();
  writeLCD(0b10000000,CMD); // move cursor to 1st row, 1st column
  inputLCD(lcdString);
  delay1ms(2000);
  clearLCD();  
  
}