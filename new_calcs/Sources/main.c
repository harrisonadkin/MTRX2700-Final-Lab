#include <hidef.h>      /* common defines and macros */
#include <assert.h>
#include "derivative.h"      /* derivative-specific definitions */

// need this for string functions
#include <stdio.h>

#include "pll.h"
#include "simple_serial.h"
#include "l3g4200d.h"
#include "servo.h"
#include "rotation.h"



void main(void) {

  AccelRaw read_accel;
  AccelScaled scaled_accel;
  GyroRaw read_gyro; 
  MagRaw read_magnet;
  
  GyroRaw scaled_gyro;
  duty pitch_features, yaw_features;
  
  rotation AccelRot; 
  rotation GyroRot; 
  rotation TotalRot; 
    
  int error_code = NO_ERROR;
  unsigned char buffer[128];

  #ifndef SIMULATION_TESTING

  PLL_Init();
  servoInit();
  
  pitch_features.current = 2200;
  PWMDTY45 = pitch_features.current;
  
  pitch_features.max = 3000;
  pitch_features.min = 1400;
  dutyFactor(&pitch_features);
  
  yaw_features.current = 2200;
  PWMDTY67 = yaw_features.current;
   
  yaw_features.max = 3000;
  yaw_features.min = 1400;
  dutyFactor(&yaw_features);
    
  #endif


  // initialise the simple serial
  SCI1_Init(BAUD_9600);
  
  #ifndef SIMULATION_TESTING
  
  // initialise the sensor suite
  error_code = iicSensorInit();
  
  // write the result of the sensor initialisation to the serial
  if (error_code == NO_ERROR) {
    sprintf(buffer, "NO_ERROR");
    SCI1_OutString(buffer);
  } else {
    sprintf(buffer, "ERROR %d");
    SCI1_OutString(buffer);    
  }
  
  #else
  
  Init_TC7();
  
  #endif 
    
	EnableInterrupts;
  COPCTL = 7;

  for(;;) {
  
    #ifndef SIMULATION_TESTING
  
    getRawDataGyro(&read_gyro);
    getRawDataAccel(&read_accel);
    getRawDataMagnet(&read_magnet);
    
    #else
    
    read_gyro.x = 123; read_gyro.y = 313; read_gyro.z = 1002;
    read_accel.x = 124; read_accel.y = 312; read_accel.z = 2002;
    read_magnet.x = 125; read_magnet.y = 311; read_magnet.z = 3002;
    
    #endif
    
    // convert the acceleration to a scaled value
    convertUnits(&read_accel, &scaled_accel);    
    // format the string of the sensor data to go the the serial
    //sprintf(buffer, "%.2f, %.2f, %.2f, %d, %d, %d\r\n", scaled_accel.x, scaled_accel.y, scaled_accel.z, read_gyro.x, read_gyro.y, read_gyro.z);
    // output the data to serial
    //SCI1_OutString(buffer);
    
    GyroRotation(&GyroRot,&read_gyro,0.05);
    //sprintf(buffer, "g_pitch: %.2f degs, g_yaw: %.2f degs\r\n", GyroRot.pitch, GyroRot.yaw);
    //SCI1_OutString(buffer);
    
    AccelRotation(&AccelRot,&scaled_accel);
    //sprintf(buffer, "%.4f, %.4f, %.4f, a_pitch: %.2f degs, a_roll: %.2f degs\r\n", scaled_accel.x, scaled_accel.y, scaled_accel.z, AccelRot.pitch);    
    //SCI1_OutString(buffer);
    
    DistCalcs(&TotalRot, &AccelRot, 0.05, &GyroRot, 0.95);
    //sprintf(buffer, "WEIGHTED; pitch = %.2f degs, yaw = %.2f degs\r\n", TotalRot.pitch, TotalRot.yaw);
    //SCI1_OutString(buffer);

    changePitch(&TotalRot, &pitch_features);
    //sprintf(buffer, "current = %d\r\n", pitch_features.current);
    //SCI1_OutString(buffer);
   
    PWMDTY45 = pitch_features.current; 
    
    changeYaw(&TotalRot, &yaw_features);
    sprintf(buffer, "factor = %f, current = %d\r\n", yaw_features.factor, yaw_features.current);
    SCI1_OutString(buffer);
    
    PWMDTY67 = yaw_features.current; 

    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  
  /* please make sure that you never leave main */
}
