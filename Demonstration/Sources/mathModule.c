#include "mathModule.h"
#include <math.h>
#include <hidef.h>
#include "derivative.h"
#include "globals.h"

/******************************************************************************
*                                                                             *
*                                                                             *
*                          Math Module Functions                              *
*                                                                             *
*                                                                             *
******************************************************************************/


float buffer1[bufferSize];
float buffer2[bufferSize];
float buffer3[bufferSize];
float buffer4[bufferSize];

void mathTimer(float * output1, float * output2, float * output3, float * output4){
  volatile int a = 3;
  volatile long b = 1234567891;
  volatile float c = 1.2345;
  volatile double d = 3.00000000001234;
  
  EnableInterrupts;
  intCalcs(a);
  longCalcs(b);
  floatCalcs(c);
  doubleCalcs(d);
  //convertString(output);
  memcpy(output1, buffer1, 6*sizeof(float));
  memcpy(output2, buffer2, 6*sizeof(float));
  memcpy(output3, buffer3, 6*sizeof(float));
  memcpy(output4, buffer4, 6*sizeof(float));

}


void intCalcs(volatile int a){
  volatile int ans;
  unsigned int time;
    
      time = TCNT;
      ans = a+a;
      buffer1[0] = calcTime(time)*(2/24.0);
      
      time = TCNT;
      ans = a*a;
      buffer1[1] = calcTime(time)*(2/24.0);
    
      time = TCNT;
      ans = a/a;
      buffer1[2] = calcTime(time)*(2/24.0);

      time = TCNT;
      ans = sqrt(a);
      buffer1[3] = calcTime(time)*(2/24.0);
      
      time = TCNT;
      ans = sin(a);
      buffer1[4] = calcTime(time)*(2/24.0);
      
      time = TCNT;
      ans = cos(a);
      buffer1[5] = calcTime(time)*(2/24.0); 

}

void longCalcs(volatile long b){
  volatile long ans;
  unsigned int time;
  
      time = TCNT;
      ans = b+b;
      buffer2[0] = calcTime(time)*(2/24.0);

      time = TCNT;
      ans = b*b;
      buffer2[1] = calcTime(time)*(2/24.0);
    
      time = TCNT;
      ans = b/b;
      buffer2[2] = calcTime(time)*(2/24.0);

      time = TCNT;
      ans = sqrt(b);
      buffer2[3] = calcTime(time)*(2/24.0);
      
      time = TCNT;
      ans = sin(b);
      buffer2[4] = calcTime(time)*(2/24.0);

      time = TCNT;
      ans = cos(b);
      buffer2[5] = calcTime(time)*(2/24.0);
   
}

void floatCalcs(volatile float c){
  volatile float ans;
  unsigned int time;
  
      time = TCNT;
      ans = c+c;
      buffer3[0] = calcTime(time)*(2/24.0);

      time = TCNT;
      ans = c*c;
      buffer3[1] = calcTime(time)*(2/24.0);
                                       
      time = TCNT;
      ans = c/c;
      buffer3[2] = calcTime(time)*(2/24.0);

      time = TCNT;
      ans = sqrt(c);
      buffer3[3] = calcTime(time)*(2/24.0);
      
      time = TCNT;
      ans = sin(c);
      buffer3[4] = calcTime(time)*(2/24.0);
      
      time = TCNT;
      ans = cos(c);
      buffer3[5] = calcTime(time)*(2/24.0);
   
}

void doubleCalcs(volatile double d){
  volatile double ans;
  unsigned int time;
  
      time = TCNT;
      ans = d+d;
      buffer4[0] = calcTime(time)*(2/24.0);

      time = TCNT;
      ans = d*d;
      buffer4[1] = calcTime(time)*(2/24.0);
    
      time = TCNT;
      ans = d/d;
      buffer4[2] = calcTime(time)*(2/24.0);

      time = TCNT;
      ans = sqrt(d);
      buffer4[3] = calcTime(time)*(2/24.0);
      
      time = TCNT;
      ans = sin(d);
      buffer4[4] = calcTime(time)*(2/24.0);
      
      time = TCNT;
      ans = cos(d);
      buffer4[5] = calcTime(time)*(2/24.0);
   
}




