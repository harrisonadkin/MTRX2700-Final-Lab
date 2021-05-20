#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>
#include "math.h"
#include "servo.h"
#include "rotation.h"
#include "accelerometer.h"
#include "l3g4200d.h"
#include "simple_serial.h"

//int i,j;

void main(void) {
  

  AccelScaled scaled_accel;
  GyroRaw scaled_gyro;
  unsigned char buffer[128];
  duty pitch_features, roll_features;
  
  float dutyFactor;
  
  rotation AccelRot; //= (rotation*) malloc(sizeof(rotation)+5);
  rotation GyroRot; //= (rotation*) malloc(sizeof(rotation)+5);
  rotation TotalRot; //= (rotation*) malloc(sizeof(rotation)+5);
  
  SCI1_Init(BAUD_9600);

  servoInit();
  
	EnableInterrupts;
 
  scaled_accel.x = 0.5773;
  scaled_accel.y = 0.5773;
  scaled_accel.z = 0.5773;
  scaled_gyro.x = 200;
  scaled_gyro.y = 200;
  scaled_gyro.z = 200;
  pitch_features.current = 2000;
  pitch_features.max = 3000;
  pitch_features.min = 1000;
  pitch_features.factor = 11.1;
  roll_features.current = 2000;
  roll_features.max = 3000;
  roll_features.min = 1000;
  roll_features.factor = 11.1;
  
   
  for(;;) {

    AccelRotation(&AccelRot,&scaled_accel);
    sprintf(buffer, "ax = %.2f, ay = %.2f, az = %.2f, a_pitch: %.2f degs, a_roll: %.2f degs\r\n", scaled_accel.x, scaled_accel.y, scaled_accel.z, AccelRot.pitch, AccelRot.roll);
    SCI1_OutString(buffer);
    
    GyroRotation(&GyroRot,&scaled_gyro,0.05);
    sprintf(buffer, "gx = %.2f, gy = %.2f, gz = %.2f, g_pitch: %.2f degs, g_roll: %.2f degs\r\n", scaled_gyro.x, scaled_gyro.y, scaled_gyro.z, GyroRot.pitch, GyroRot.roll);
    SCI1_OutString(buffer);
    
    DistCalcs(&TotalRot, &AccelRot, 0.01, &GyroRot, 0.95);
    sprintf(buffer, "WEIGHTED; pitch = %.2f degs, roll = %.2f degs\r\n", TotalRot.pitch, TotalRot.roll);
    SCI1_OutString(buffer);
    //pitch_travel = TotalRot.pitch;

    changePitch(&TotalRot, &pitch_features);
    sprintf(buffer, "factor = %f, current = %d\r\n", pitch_features.factor, pitch_features.current);
    SCI1_OutString(buffer);
    
    changeRoll(&TotalRot, &pitch_features);
    sprintf(buffer, "factor = %f, current = %d\r\n", roll_features.factor, roll_features.current);
    SCI1_OutString(buffer);
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
