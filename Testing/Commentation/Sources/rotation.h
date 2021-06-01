#ifndef ROTATION_H
#define ROTATION_H

#include "offset.h"
#include "l3g4200d.h"

//data structure for rotation values
typedef struct rotation{ 
  float pitch;
  float yaw;
  float previous_pitch; 
} rotation;


void AccelRotation (rotation *AccelRot, AccelScaled *AccelData);

void GyroRotation (GyroRaw* g_offset,rotation *GyroRot, GyroRaw *GyroData, float dT);

void DistCalcs(rotation *TotalRot, rotation *AccelRot, float AccelWeight, rotation *GyroRot, float GyroWeight); 
 
#endif
  
  