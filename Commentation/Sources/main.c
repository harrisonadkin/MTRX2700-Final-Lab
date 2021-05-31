#include <hidef.h>      /* common defines and macros */
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "derivative.h" /* derivative-specific definitions */
#include "help.h"
#include "serialModule.h"
#include "lcdModule.h"
#include "calibrateServo.h"
#include "offset.h"
#include "rotation.h"
#include "servo.h"
#include "iic.h"
#include "l3g4200d_definitions.h"
#include "l3g4200d.h" 
#include "simple_serial.h"



void main(void) {

  int *xMaxMin;
  int *yMaxMin;
  volatile AccelRaw* AccelOffset= malloc(sizeof(AccelRaw)); 
  volatile AccelRaw* read_accel = malloc(sizeof(AccelRaw));
  volatile AccelScaled* scaled_accel = malloc(sizeof(AccelScaled));
  
  volatile GyroRaw* GyroOffset = malloc(sizeof(GyroRaw));
  volatile GyroRaw* read_gyro = malloc(sizeof(GyroRaw)); 
  volatile GyroScaled* scaled_gyro = malloc(sizeof(GyroScaled));
  
  volatile duty* pitch_features = malloc(sizeof(duty));
  volatile duty* yaw_features = malloc(sizeof(duty));
  
  volatile rotation *AccelRot = malloc(sizeof(rotation)); 
  volatile rotation *GyroRot  = malloc(sizeof(rotation)); 
  volatile rotation *TotalRot = malloc(sizeof(rotation));


  int error_code = NO_ERROR;
  unsigned char buffer[128];
  SCI1_Init(BAUD_9600);
  //servoInit();
  error_code = iicSensorInit();
  
  // write the result of the sensor initialisation to the serial
  /*if (error_code == NO_ERROR) {
    sprintf(buffer, "NO_ERROR");
    SCI1_OutString(buffer);
  } else {
    sprintf(buffer, "ERROR %d");
    SCI1_OutString(buffer);    
  }*/  
  
  //Init_TC7();
  
  
  EnableInterrupts;
  printHelp();
  servoInit();
  calibrateServo(xMaxMin, yMaxMin);
  
  //need this for caluclating the constant in maxmin
  //dutyFactor(pitch_features);
  
  //calibrates the PTU
  //also PTU needs to be in neutral position before running this
  //so do PWMDTY45 = halfway between max and min
  //same with DTY67
  calibrateGyro(read_gyro, GyroOffset);  
  calibrateAccel(read_accel, AccelOffset);
  
  //sprintf(buffer, "%d, %d, %d, %d, %d, %d\r\n", GyroOffset->x, GyroOffset->y, GyroOffset->z, AccelOffset->x, AccelOffset->y, AccelOffset->z );
  //SCI1_OutString(buffer);
  //sprintf(buffer, "%d, %d, %d\r\n", read_accel->x, read_accel->y, read_accel->z );
  //SCI1_OutString(buffer);

  for(;;){                   // BJORK the swedish dog
  
     //gets raw values needed in calculations
     getRawDataGyro(read_gyro);
     getRawDataAccel(read_accel);
     
     //transforms raw acceleration values to meaningful values
     convertUnits(read_accel, scaled_accel, AccelOffset);
     
     //determines the orientation of the PTU according to accelerometer readings
     AccelRotation(AccelRot,scaled_accel); 
     //sprintf(buffer, "%d, %d, %f\r\n", AccelOffset->x, AccelOffset->y, AccelOffset->z );
     //SCI1_OutString(buffer);
     
     //scales the gyroscope readings with their offset and determines how far the PTU has travelled according to the gyroscope
     GyroRotation(GyroOffset, GyroRot, read_gyro,0.105);
     //sprintf(buffer, "g_pitch: %d degs\r\n", read_gyro->y);
     //SCI1_OutString(buffer);
     
     //weights the previous rotation calculations according to constants
     DistCalcs(TotalRot, AccelRot, 0.05, GyroRot, 0.95);
     //sprintf(buffer, "pitch = %.2f degs\r\n", TotalRot.pitch);
     //SCI1_OutString(buffer);

     //determines the duty cycle which the servo needs to maintain in order to oppose relative motion
     changePitch(TotalRot, pitch_features);
     //sprintf(buffer, "current = %d\r\n", pitch_features->current);
     //SCI1_OutString(buffer);
   
     //assigns the value to the PWM output
     PWMDTY45 = pitch_features->current;
     
     //delay 100ms to allow for the servo to make the full movement
     delay(100);
     
    _FEED_COP(); 
  }
}           
    