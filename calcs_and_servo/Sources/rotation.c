#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>
#include "math.h"
#include "rotation.h"
#include "accelerometer.h"
#include "l3g4200d.h"

/*//this function writes to two rotation structs which are dynamically allocated
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
  
}*/