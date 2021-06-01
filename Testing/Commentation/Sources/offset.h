#ifndef OFFSET_HEADER
#define OFFSET_HEADER

//#include "l3g4200d.h"

// data structures
typedef struct AccelRaw {
  int z;
  int y;
  int x;
} AccelRaw;

typedef struct GyroRaw {
  int z;
  int y;
  int x;
} GyroRaw;

typedef struct AccelScaled {
  float x;
  float y;
  float z;
} AccelScaled;

typedef struct GyroScaled {
  float x;
  float y;
  float z;
} GyroScaled;

//void convertUnits(AccelRaw *raw_data, AccelScaled *scaled_data);
void calibrateGyro(GyroRaw *raw_data, GyroRaw *gyro_offset);
void convertUnits(AccelRaw *raw_data, AccelScaled *scaled_data, AccelRaw* accel_offset);
void calibrateAccel(AccelRaw *raw_data, AccelRaw *accel_offset); 

#endif