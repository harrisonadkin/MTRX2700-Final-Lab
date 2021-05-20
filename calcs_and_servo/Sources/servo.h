#ifndef SERVO_C
#define SERVO_C

void servoInit(void); 

float changeDuty(int *currentDuty, float *degTravelled, int *maxDuty, int *minDuty) ;