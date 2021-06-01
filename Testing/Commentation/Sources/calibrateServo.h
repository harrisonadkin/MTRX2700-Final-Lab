#ifndef CALIBRATE_HEADER
#define CALIBRATE_HEADER

#define RIGHT 1 
#define LEFT  0
#define UP    1
#define DOWN  0
#define MAX   1
#define MIN   0

void calibrateServo(int *xMaxMin, int *yMaxMin);
void servoInit(void);;
void panServo(int direction);
void tiltServo(int direction);
void storeServo(int type);


#endif