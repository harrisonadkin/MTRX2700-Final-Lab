#include <hidef.h>
#include "derivative.h"
#include "rotation.h"
#include "servo.h"
#include <math.h>


void servoInit(void) {

    PWMCLK = 0;            //24MHz clock 
    PWMPOL = 0b10100000;   //high then go low pwm wave
    PWMPRCLK = 0b01000100; //prescaler of 16
    PWMCTL = 0b11000000;   //concatanate PWM outputs 45 and 67
    PWMCAE = 0;            //left aligned wave
    PWMPER45 = 30000;      //PWMPER = (50Hz signal * 16 * PWMPER)/ 24 MHz
    //PWMDTY45 = 1350;       //1350-3150 PWMDTY = on/off = PWMDTY/PWMPER  
    PWMPER67 = 30000;      //PWMPER = (50Hz signal * 16 * PWMPER)/ 24 MHz
    //PWMDTY67 = 2000;       //PWMDTY = on/off = PWMDTY/PWMPER                   
    PWME = 0b10100000;     //pwm outputs 7 and 5 which are connected 6 and 4 respectively

}

void dutyFactor(duty *MaxMin) {

   MaxMin->factor = (MaxMin->max - MaxMin->min)/180;
   
}

//intakes the current duty cycle, degrees travelled and the max/min and outputs a servo displacement
//oppisite to that of the movement
void changePitch(rotation *degTravelled, duty *MaxMin) { 

      //if expected new duty cycle exceeds the maximum duty cycle then return the max
      if (((float)MaxMin->current - degTravelled->pitch * MaxMin->factor) >= MaxMin->max) {
          MaxMin->current = (int)MaxMin->max; 
      
      } else if (((float)MaxMin->current - degTravelled->pitch *  MaxMin->factor) <= MaxMin->min) {
          MaxMin->current = (int)MaxMin->min;
   
      } else {
          MaxMin->current = (int)((float)MaxMin->current - degTravelled->pitch *  MaxMin->factor);
      
      }
}

void changeYaw(rotation *degTravelled, duty *MaxMin) {

      //if expected new duty cycle exceeds the maximum duty cycle then return the max
      if (((float)MaxMin->current - degTravelled->yaw * MaxMin->factor) >= MaxMin->max) {
          MaxMin->current = (int)MaxMin->max; 
      
      } else if (((float)MaxMin->current - degTravelled->yaw *  MaxMin->factor) <= MaxMin->min) {
          MaxMin->current = (int)MaxMin->min;
   
      } else {
          MaxMin->current = (int)((float)MaxMin->current - degTravelled->yaw *  MaxMin->factor);
      
      }
}