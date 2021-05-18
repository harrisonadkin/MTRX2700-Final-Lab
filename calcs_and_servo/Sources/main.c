#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>
#include "math.h"
#include "rotation.h"
#include "accelerometer.h"
#include "l3g4200d.h"

int i,j;

typedef struct rotation { 
  float pitch;
  float roll; 
} rotation;

//this function writes to two rotation structs which are dynamically allocated
void AccelRotation (rotation* AccelRot, AccelScaled* AccelData)
{
  
  AccelRot->pitch = (atan2(AccelData->x, (sqrt(AccelData->y*AccelData->y + AccelData->z*AccelData->z)))) * 180.0 / 3.14159;
  AccelRot->roll = (atan2(AccelData->y, (sqrt(AccelData->x*AccelData->x + AccelData->z*AccelData->z)))) * 180.0 / 3.14159; 
     
   
}

//takes rotational velocity and outputs the rotation during that time using d = v*t
void GyroRotation (rotation* GyroRot, GyroRaw* GyroData, float dT) 
{

  GyroRot->pitch = GyroData->x * dT;
  GyroRot->roll =  GyroData->y * dT;

}

void DistCalcs(rotation* TotalRot, rotation* AccelRot, float AccelWeight, rotation* GyroRot, float GyroWeight)
{
  
  TotalRot->pitch = AccelWeight*AccelRot->pitch + GyroWeight*GyroRot->pitch;
  TotalRot->roll = AccelWeight*AccelRot->roll + GyroWeight*GyroRot->roll;  
  
}

void main(void) {
  
  //Alessandro's Calculations Section
  //rotation *AccelRot;
  //rotation *GyroRot;
  //rotation *TotalRot;
  AccelScaled *scaled_accel;
  GyroRaw *scaled_gyro;
  

  
  rotation *AccelRot; //= (rotation*) malloc(sizeof(rotation)+5);
  rotation *GyroRot; //= (rotation*) malloc(sizeof(rotation)+5);
  rotation *TotalRot; //= (rotation*) malloc(sizeof(rotation)+5);
  
  //AccelRot.pitch = 1;
  /*
  PWMCLK = 0;        // 24MHz clock
  PWMPOL = 0b10100000; //start high then go low
  PWMPRCLK = 0b01000100; //prescaler of 16
  PWMCTL = 0b11000000; //concatanate PWM outputs 45 and 67
  PWMCAE = 0; //left aligned wave
  PWMPER45 = 30000; //PWMPER = (50Hz signal * 16 * PWMPER)/ 24 MHz
  PWMDTY45 = 1350; //1350-3150 PWMDTY = on/off = PWMDTY/PWMPER  
  PWMPER67 = 30000; //PWMPER = (50Hz signal * 16 * PWMPER)/ 24 MHz
  PWMDTY67 = 2000; //PWMDTY = on/off = PWMDTY/PWMPER                   
  PWME = 0b10100000;
  
	EnableInterrupts;
  */
  
  for(;;) {

    AccelRotation(AccelRot,scaled_accel);
    GyroRotation(GyroRot,scaled_gyro,0.02);
    DistCalcs(TotalRot,AccelRot, 0.05,GyroRot, 0.95);
  
    /*for (i = 1350; i < 3000; i++) {
      //delay(1000);
      PWMDTY67 = i;
      
    }
    for (i = 3000; i > 1400; i--) {
      //delay(1000);
      PWMDTY67 = i;
      
    }*/ 

    _FEED_COP(); /* feeds the dog */

  }
}
