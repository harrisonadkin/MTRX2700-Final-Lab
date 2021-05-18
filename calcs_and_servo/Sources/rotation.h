#ifndef ROTATION_H
#define ROTATION_H

#include "accelerometer.h"
#include "l3g4200d.h"

//data structure for rotation values
typedef struct rotation{ 
  float pitch;
  float roll; 
} rotation;


void AccelRotation (rotation *AccelRot, AccelScaled *AccelData);

void GyroRotation (rotation *GyroRot, GyroRaw *GyroData, float dT);

void DistCalcs(rotation *TotalRot, rotation *AccelRot, float AccelWeight, rotation *GyroRot, float GyroWeight); 
 
#endif
  
  