#include "rotation.h"

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>
#include <math.h>

#define PI 3.1415926535

//this function writes to two rotation structs which are dynamically allocated
void AccelRotation (rotation* AccelRot, AccelScaled* AccelData)
{
  
  AccelRot->previous_pitch = AccelRot->pitch; 
  AccelRot->pitch = (atan2(AccelData->x, sqrt(AccelData->z*AccelData->z + AccelData->y*AccelData->y)) * 180.0) / PI;   
   
}

//takes rotational velocity and outputs the rotation during that time using d = v*t
void GyroRotation (rotation* GyroRot, GyroRaw* GyroData, float dT) 
{

  GyroRot->pitch = GyroData->y * 0.01750 * dT;
  GyroRot->yaw =  GyroData->z * 0.01750 * dT;

}

void DistCalcs(rotation* TotalRot, rotation* AccelRot, float AccelWeight, rotation* GyroRot, float GyroWeight)
{
  
  TotalRot->pitch = AccelWeight*(AccelRot->previous_pitch - AccelRot->pitch) + GyroWeight*GyroRot->pitch;
  TotalRot->yaw = GyroWeight*GyroRot->yaw;  
  
}