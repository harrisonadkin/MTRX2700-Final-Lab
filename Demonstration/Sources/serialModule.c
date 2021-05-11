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

Serial newSerial;
int index = 0;
int runCondition;
unsigned char inputString[255];
unsigned char *outputString;
unsigned char statusRegister;


void serialInitialise(int baudRate, int interface, int function, unsigned char ** dataLocation){
    if (index == 0) {
      runCondition = 1;
      newSerial.function = function;
      newSerial.interface = interface;
      newSerial.baudRate = baudRate;
      
      if(newSerial.function == 0){
        *dataLocation = &inputString[0];

      } else if(newSerial.function == 1){
        outputString = *dataLocation;
      }

      setControl();
    }
  
    while(runCondition){
        _FEED_COP(); // BYJORK
    }                        
}


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

void writeSerial(void){

    if(newSerial.interface == 0){
        //  statusRegister = SCI0SR1;
        //  SCI0DRL = outputString[index];
      
    } else if(newSerial.interface == 1){
          statusRegister = SCI1SR1;
          SCI1DRL = *(outputString + index);
      
    }

    if(outputString[index] == 0){
          resetSerial();
    
    } else{
          index++;
    }
}

void readSerial(void){

   if(newSerial.interface == 0){
        //  statusRegister = SCI0SR1;
        //  inputString[index] = SCI0DRL;
      
   } else if(newSerial.interface == 1){
          statusRegister = SCI1SR1;
          inputString[index] = SCI1DRL;
      
   } 

   if(inputString[index] == 13){
          index++;
          inputString[index] = '\n';
          index++;
          inputString[index] = '\0';
          
          resetSerial();
    
   } else{
          index++;
    
   }
}

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
    
    if(newSerial.function == 0){
          readSerial();
      
    } else if(newSerial.function == 1){
          writeSerial();
  
    }
} 


