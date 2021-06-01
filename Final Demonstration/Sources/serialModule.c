#include <hidef.h>      /* common defines and macros */
#include <stdio.h>
#include <string.h>
#include "serialModule.h"
#include "derivative.h"



/******************************************************************************
*                                                                             *
*                                                                             *
*                           Serial Printing Module                            *
*                                                                             *
*                                                                             *
******************************************************************************/

// instance of serial struct + initial conditions and strings
Serial newSerial;
int index = 0;
int runCondition;
unsigned char inputString[255];
unsigned char *outputString;
unsigned char statusRegister;

// function to initialise serial, consider baud rate, interface, read/write and input/output string
void serialInitialise(int baudRate, int interface, int function, unsigned char ** dataLocation){
    if (index == 0) {
      // first character
      runCondition = 1;
      newSerial.function = function;
      newSerial.interface = interface;
      newSerial.baudRate = baudRate;
      
      //store info in struct
      // read or write
      if(newSerial.function == 0){
        *dataLocation = &inputString[0];

      } else if(newSerial.function == 1){
        outputString = *dataLocation;
      }
      // decide based on function
      setControl();
    }
  
    //wait for interrupts
    while(runCondition){
        _FEED_COP(); // BYJORK
    }                        
}

// function to initialise all serials as inputted
void setControl(void){
   if(newSerial.interface == 0){
      //SCI0BDL = newSerial.baudRate;
   }else if (newSerial.interface == 1){
      SCI1BDL = newSerial.baudRate;
   }
   
   if(newSerial.function == 0){
      if(newSerial.interface == 0){
         // SCI0CR2 |= SCI0CR2_RIE_MASK;
         // SCI0CR2 |= SCI0CR2_RE_MASK;
      
      } else if(newSerial.interface == 1){
          SCI1CR2 |= SCI1CR2_RIE_MASK;
          SCI1CR2 |= SCI1CR2_RE_MASK;
      
      }
        
   } else if(newSerial.function == 1){
      if(newSerial.interface == 0){
         // SCI0CR2 |= SCI0CR2_SCTIE_MASK;
         // SCI0CR2 |= SCI0CR2_TE_MASK;
      
      } else if(newSerial.interface == 1){
          SCI1CR2 |= SCI1CR2_SCTIE_MASK;
          SCI1CR2 |= SCI1CR2_TE_MASK;
      
      }
   } 
}

// write to serial function
void writeSerial(void){

// based on interface (SCI0 or SCI1)
    if(newSerial.interface == 0){
        //  statusRegister = SCI0SR1;
        //  SCI0DRL = outputString[index];
      
    } else if(newSerial.interface == 1){
          statusRegister = SCI1SR1;
          SCI1DRL = *(outputString + index);
      
    }


    // if at end of string reset serial
    if(outputString[index] == 0){
          resetSerial();
    
    // otherwise go to next character
    } else{
          index++;
    }
}

// function to read from serial
void readSerial(void){

  // based on interface
   if(newSerial.interface == 0){
        //  statusRegister = SCI0SR1;
        //  inputString[index] = SCI0DRL;
      
   } else if(newSerial.interface == 1){
          
          statusRegister = SCI1SR1; // set status register to exit interrupt
          inputString[index] = SCI1DRL; // read input string 
      
   } 

// once end line is inputted
   if(inputString[index] == 13){
          index++;                   // go to next character
          inputString[index] = '\n'; // input newline
          index++;                   // next char
          inputString[index] = '\0'; // null char
          
          resetSerial();             // now reset
    
   } else{
          index++;                   // otherwise keep reading
    
   }
}

// function for resetting serial
void resetSerial(void){
    
    index = 0;
    //SCI0CR2 = 0;
    SCI1CR2 = 0;
    runCondition = 0;
    
}

// initialising SCI0 interrupt
/*#pragma CODE_SEG __NEAR_SEG NON_BANKED 
__interrupt void SCI0_ISR(void) { 
    
    if(newSerial.function == 0){
          readSerial();
      
    } else if(newSerial.function == 1){
          writeSerial();
  
    }
} */

// initialising SCI1 interrupt
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
__interrupt void SCI1_ISR(void) { 
    
    // based on function do one or other
    if(newSerial.function == 0){
          readSerial(); 
      
    } else if(newSerial.function == 1){
          writeSerial();
  
    }
} 


