#include <hidef.h>
#include "derivative.h"
#include "rotation.h"
#include "servo.h"
#include <math.h>

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