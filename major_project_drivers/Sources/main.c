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

  volatile AccelRaw* read_accel = malloc(sizeof(AccelRaw));
  volatile AccelScaled* scaled_accel = malloc(sizeof(AccelScaled));
  volatile GyroRaw* read_gyro = malloc(sizeof(GyroRaw)); 
  volatile MagRaw* read_magnet = malloc(sizeof(MagRaw));
  volatile GyroRaw* scaled_gyro = malloc(sizeof(GyroRaw));
  
  volatile duty* pitch_features = malloc(sizeof(duty));
  volatile duty* yaw_features = malloc(sizeof(duty));
  
  volatile rotation *AccelRot = malloc(sizeof(rotation)); 
  volatile rotation *GyroRot  = malloc(sizeof(rotation)); 
  volatile rotation *TotalRot = malloc(sizeof(rotation)); 
     
  int error_code = NO_ERROR;
  unsigned char buffer[128];
  
  //assert(error_code != NO_ERROR);
  #ifndef SIMULATION_TESTING

  // make sure the board is set to 24MHz
  servoInit();
  
  pitch_features->current = 2200;
  PWMDTY45 = pitch_features->current;
  PWMDTY67 = pitch_features->current;
  pitch_features->max = 3000;
  pitch_features->min = 1400;
  dutyFactor(pitch_features);
  //delay(100);
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
  
    // read the raw values
    getRawDataGyro(read_gyro);
    getRawDataAccel(read_accel);
    getRawDataMagnet(read_magnet);
    
    #else
    
    // inject some values for simulation
    read_gyro.x = 123; read_gyro.y = 313; read_gyro.z = 1002;
    read_accel.x = 124; read_accel.y = 312; read_accel.z = 2002;
    read_magnet.x = 125; read_magnet.y = 311; read_magnet.z = 3002;
    
    #endif

    // convert the acceleration to a scaled value
    convertUnits(read_accel, scaled_accel);    
    // format the string of the sensor data to go the the serial
    //sprintf(buffer, "%.2f, %.2f, %.2f, %d, %d, %d\r\n", scaled_accel.x, scaled_accel.y, scaled_accel.z, read_gyro.x, read_gyro.y, read_gyro.z);
    // output the data to serial
    //SCI1_OutString(buffer);
    
    GyroRotation(GyroRot,read_gyro,0.2);
    //sprintf(buffer, "g_pitch: %.2f degs\r\n", GyroRot.pitch);
    //SCI1_OutString(buffer);
    
    AccelRotation(AccelRot,scaled_accel);
    //sprintf(buffer, "%.4f, %.4f, %.4f, a_pitch: %.2f degs, a_roll: %.2f degs\r\n", scaled_accel.x, scaled_accel.y, scaled_accel.z, AccelRot.pitch);    
    //SCI1_OutString(buffer);
    
    DistCalcs(TotalRot, AccelRot, 0.05, GyroRot, 0.95);
    //sprintf(buffer, "pitch = %.2f degs\r\n", TotalRot.pitch);
    //SCI1_OutString(buffer);

    changePitch(TotalRot, pitch_features);
    sprintf(buffer, "current = %d\r\n", pitch_features->current);
    SCI1_OutString(buffer);
   
    delay(200);
    PWMDTY45 = pitch_features->current;
    //delay(1000); 

    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  
  /* please make sure that you never leave main */
}
