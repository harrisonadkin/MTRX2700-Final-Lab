#include <hidef.h>
#include "derivative.h"
#include <math.h>

void servoInit(void) {

    PWMCLK = 0;            //24MHz clock 
    PWMPOL = 0b10100000;   //high then go low pwm wave
    PWMPRCLK = 0b01000100; //prescaler of 16
    PWMCTL = 0b11000000;   //concatanate PWM outputs 45 and 67
    PWMCAE = 0;            //left aligned wave
    PWMPER45 = 30000;      //PWMPER = (50Hz signal * 16 * PWMPER)/ 24 MHz
    PWMDTY45 = 1350;       //1350-3150 PWMDTY = on/off = PWMDTY/PWMPER  
    PWMPER67 = 30000;      //PWMPER = (50Hz signal * 16 * PWMPER)/ 24 MHz
    PWMDTY67 = 2000;       //PWMDTY = on/off = PWMDTY/PWMPER                   
    PWME = 0b10100000;     //pwm outputs 7 and 5 which are connected 6 and 4 respectively

}

//intakes the current duty cycle, degrees travelled and the max/min and outputs a servo displacement
//oppisite to that of the movement
float changeDuty(int *currentDuty, float *degTravelled, int *maxDuty, int *minDuty) {

    //initialise variables used in the function
    float newDuty, dutyFactor;

    //this can be done outside the function and fed in as dutyFactor 
    dutyFactor = (maxDuty-minDuty)/180;

    //if expected new duty cycle exceeds the maximum duty cycle then return the max
    if (currentDuty - degTravelled * dutyFactor >= max) {
        return maxDuty;  

    //same as above in the case of minimum
    } else if (currentDuty - degTravelled * dutyFactor <= min) {
        return minDuty;

    //calculates the new duty cycle needed    
    } else {
        newDuty = (int)round(currentDuty - degTravelled * dutyFactor);
        return newDuty;

    }
}