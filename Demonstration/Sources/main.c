#include <hidef.h>      /* common defines and macros */
#include <stdio.h>
#include <string.h>
#include "derivative.h" /* derivative-specific definitions */
#include "help.h"
#include "serialModule.h"
#include "musicModule.h"
#include "iic.h"
#include "l3g4200d_definitions.h"
#include "l3g4200d.h"


  

void main(void) {
  /* put your own code here */
  
  EnableInterrupts;
  printHelp();
  Init_TC5();
  bootJingle();
  

  while(1){                   // BJORK the swedish dog
  
   
    _FEED_COP(); 
  }
}



/*
  AccelRaw read_accel;
  AccelScaled scaled_accel;
  
  GyroRaw read_gyro;
  GyroOffsets scaled_gyro;
  
  MagRaw read_magnet;
  
  int error_code = NO_ERROR;
  unsigned char buffer[128];
  error_code = iicSensorInit();
  
  Init_TC7();
  
  
  EnableInterrupts;
  COPCTL = 7;
  
  */
  
  /* getRawDataGyro(&read_gyro);
    getRawDataAccel(&read_accel);
    getRawDataMagnet(&read_magnet);
    
    convertUnits(&read_accel, &scaled_accel);
    calibrate_gyro(&read_gyro, &scaled_gyro);
    
    sprintf(buffer, "%.2f, %.2f, %.2f, %d, %d, %d, %d, %d, %d \r\n", scaled_accel.x, scaled_accel.y, scaled_accel.z, scaled_gyro.x, scaled_gyro.y, scaled_gyro.z, read_magnet.x, read_magnet.y, read_magnet.z);
    serialInitialise(156,1,1,&buffer);   */               
    