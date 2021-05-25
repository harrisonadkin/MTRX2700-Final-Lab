#ifndef ACCELEROMETER_HEADER
#define ACCELEROMETER_HEADER


// data structures containing the raw values
typedef struct AccelRaw {
  int z;
  int y;
  int x;
} AccelRaw;


// data structures containing the raw values
typedef struct AccelScaled {
  float z;
  float y;
  float x;
} AccelScaled;

void convertUnits(AccelRaw *raw_data, AccelScaled *scaled_data);

#endif