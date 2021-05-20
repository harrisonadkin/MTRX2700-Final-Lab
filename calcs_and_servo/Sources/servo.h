#ifndef SERVO_C
#define SERVO_C

#include "rotation.h"

typedef struct duty {
  int current;
  float max;
  float min;
  float factor;
  
} duty;

void servoInit(void);

void dutyFactor(duty *MaxMin); 

void changePitch(rotation *degTravelled, duty *MaxMin);

//void changeRoll(rotation *degTravelled, duty *MaxMin);

#endif