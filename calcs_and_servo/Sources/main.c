#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>
#include "math.h"
#include "rotation.h"
#include "accelerometer.h"
#include "l3g4200d.h"
#include "simple_serial.h"

//int i,j;

void main(void) {
  
  //Alessandro's Calculations Section
  //rotation *AccelRot;
  //rotation *GyroRot;
  //rotation *TotalRot;
  AccelScaled scaled_accel;
  GyroRaw scaled_gyro;
  unsigned char buffer[128];
  
  rotation AccelRot; //= (rotation*) malloc(sizeof(rotation)+5);
  rotation GyroRot; //= (rotation*) malloc(sizeof(rotation)+5);
  rotation TotalRot; //= (rotation*) malloc(sizeof(rotation)+5);
  
  SCI1_Init(BAUD_9600);
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
 
  scaled_accel.x = 0.5773;
  scaled_accel.y = 0.5773;
  scaled_accel.z = 0.5773;
  scaled_gyro.x = 200;
  scaled_gyro.y = 200;
  scaled_gyro.z = 200;
   
  for(;;) {

    AccelRotation(&AccelRot,&scaled_accel);
    sprintf(buffer, "ax = %.2f, ay = %.2f, az = %.2f, a_pitch: %.2f degs, a_roll: %.2f degs\r\n", scaled_accel.x, scaled_accel.y, scaled_accel.z, AccelRot.pitch, AccelRot.roll);
    SCI1_OutString(buffer);
    
    GyroRotation(&GyroRot,&scaled_gyro,0.5);
    sprintf(buffer, "gx = %.2f, gy = %.2f, gz = %.2f, g_pitch: %.2f degs, g_roll: %.2f degs\r\n", scaled_gyro.x, scaled_gyro.y, scaled_gyro.z, GyroRot.pitch, GyroRot.roll);
    SCI1_OutString(buffer);
    
    DistCalcs(&TotalRot, &AccelRot, 0.05, &GyroRot, 0.95);
    sprintf(buffer, "WEIGHTED; pitch = %.2f degs, roll = %.2f degs\r\n", TotalRot.pitch, TotalRot.roll);
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
