#include "rotation.h"

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>
#include <math.h>

#define PI 3.1415926535

//this function writes to two rotation structs which are dynamically allocated
void AccelRotation (rotation* AccelRot, AccelScaled* AccelData)
{
  
  //runs calcs needed to determine orientation through values of acceleration in various directions
  AccelRot->previous_pitch = AccelRot->pitch; 
  AccelRot->pitch = (atan2((AccelData->x), sqrt((AccelData->z)*(AccelData->z) + (AccelData->y)*(AccelData->y))) * 180.0) / PI;   
   
}

//takes rotational velocity and outputs the rotation during that time using d = v*t
void GyroRotation (GyroRaw* g_offset, rotation* GyroRot, GyroRaw* GyroData, float dT) 
{

  //0.0175 is the constant defined by the datahsheet for the respective settings being used
  GyroRot->pitch = (float)(GyroData->y - g_offset->y) * 0.0175 * dT;

}

//takes the rotations calced by the accel and gyro and weights them accordingly
void DistCalcs(rotation* TotalRot, rotation* AccelRot, float AccelWeight, rotation* GyroRot, float GyroWeight)
{
  
  //adjusts values to signify changes in rotation and further adjusts for predefined weightings
  TotalRot->pitch = AccelWeight*(AccelRot->previous_pitch - AccelRot->pitch) + GyroWeight*GyroRot->pitch;
  
}