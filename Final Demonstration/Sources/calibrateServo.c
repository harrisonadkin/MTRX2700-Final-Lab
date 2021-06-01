#include <hidef.h>      /* common defines and macros */
#include <stdio.h>
#include <string.h>
#include "serialModule.h"
#include "calibrateServo.h"
#include "derivative.h"
#include "musicModule.h"
#include "lcdModule.h"
#include "math.h"
#include "servo.h"


    // begin initialising variables
    int xMax;
    int xMin;
    int yMax;
    int yMin;
    
    char *pan_msg1 = "Pan Mode";
    char *pan_msg2 = "Panning Right";
    char *pan_msg3 = "Panning Left";
    char *tilt_msg1 = "Tilt Mode";
    char *tilt_msg2 = "Tilting Up";
    char *tilt_msg3 = "Tilting Down";  
    char *instruct_msg1 = "All hi 2 cmplete";
    char *instruct_msg2 = "Config Dipswitch";
    char *instruct_msg3 = "Storing Max Pos";
    char *instruct_msg4 = "Storing Min Pos";
    char *instruct_msg5 = "ServoCal Cmplete";

    char *serialString1 = "Servo Calibration Completed. \r\n\0";
    char *serialString2 = "Please press enter key to calibrate the accelerometer \r\n\0";
    unsigned char *readString = 0;
    char *serialString3 = "Beginning Calibration\r\n\0";
    char *newline = "\r\n\0";  


// initialise the servos 
void servoInit(void) {

    PWMCLK_PCLK7 = 0;
    PWMCLK_PCLK5 = 0;      //24MHz clock 
    //PWMPRCLK = 0b00110011; //prescaler of 8
    PWMPRCLK = 0b01000100; //prescaler of 16
    PWMCTL = 0b11000000;   //concatanate PWM outputs 45 and 67
    PWMPER45 = 3750; //PWMPER = (50Hz signal * 16 * PWMPER)/ 24 MHz
    PWMPER67 = 3750; //PWMPER = (50Hz signal * 16 * PWMPER)/ 24 MHz
    PWME = PWME | PWME_PWME4_MASK;     //pwm outputs 7 and 5 which are connected 6 and 4 respectively
    PWME = PWME | PWME_PWME5_MASK;
    PWME = PWME | PWME_PWME6_MASK;
    PWME = PWME | PWME_PWME7_MASK;

}

// calibrate the servo based on switches
void calibrateServo(duty *pitch_features){    
    
  while((PTH != 255)){  
    switch(PTH){
      case 15:
        clearLCD(); 
        break;

      case 143:
        clearLCD();
        break;
        
      case 14:
        writeLCD(0b10000000,CMD); // move cursor to 1st row, 1st column
        inputLCD(pan_msg1);           // Send first line
        writeLCD(0b11000000,CMD); // move cursor to 2nd row, 1st column
        inputLCD(pan_msg2);           // Send second line
        panServo(RIGHT);      
        break;
        
      case 13:
        writeLCD(0b10000000,CMD); // move cursor to 1st row, 1st column
        inputLCD(pan_msg1);           // Send first line
        writeLCD(0b11000000,CMD); // move cursor to 2nd row, 1st column
        inputLCD(pan_msg3);           // Send second line
        panServo(LEFT);      
        break;
        
      case 142:
        writeLCD(0b10000000,CMD); // move cursor to 1st row, 1st column
        inputLCD(tilt_msg1);           // Send first line
        writeLCD(0b11000000,CMD); // move cursor to 2nd row, 1st column
        inputLCD(tilt_msg2);           // Send second line 
        tiltServo(UP);      
        break;
        
      case 141:
        writeLCD(0b10000000,CMD); // move cursor to 1st row, 1st column
        inputLCD(tilt_msg1);           // Send first line
        writeLCD(0b11000000,CMD); // move cursor to 2nd row, 1st column
        inputLCD(tilt_msg3);           // Send second line 
        tiltServo(DOWN);      
        break;
        
      case 11:                     // store the max/mins based on button
        xMax = PWMDTY67;
        storeServo(MAX);
        break;
        
      case 7:
        xMin = PWMDTY67;      
        storeServo(MIN);  
        break;
        
      case 139:
        yMax = PWMDTY45;
        storeServo(MAX);        
        break;
        
      case 135:
        yMin = PWMDTY45;
        storeServo(MIN);
        break;
        
      default:
        clearLCD();
        writeLCD(0b10000000,CMD); // move cursor to 1st row, 1st column
        inputLCD(instruct_msg2);           // Send first line
        delay1ms(1000);      
        break;
        
    }
  }
  
  clearLCD();
  writeLCD(0b10000000,CMD); // move cursor to 1st row, 1st column
  inputLCD(instruct_msg5);           // Send first line
  
  // output instructions and calibrate accelerometer
  serialInitialise(156,1,1,&serialString1);
  serialInitialise(156,1,1,&serialString2);
  serialInitialise(156,1,1,&newline);
  serialInitialise(156,1,0,&readString);
  serialInitialise(156,1,1,&serialString3);


  
  PWMDTY67 = 1350;
  delay1ms(1000);
  PWMDTY45 = 1550;
  delay1ms(1000);
  
  clearLCD();
}  

void storeServo(int type){
  delay1ms(100);
  clearLCD();
  
  if(type == 1){
    writeLCD(0b10000000,CMD); // move cursor to 1st row, 1st column
    inputLCD(instruct_msg3);           // Send first line
    writeLCD(0b11000000,CMD); // move cursor to 2nd row, 1st column
    inputLCD(instruct_msg1);           // Send second line
  
  }else if(type == 0){
    writeLCD(0b10000000,CMD); // move cursor to 1st row, 1st column
    inputLCD(instruct_msg4);           // Send first line
    writeLCD(0b11000000,CMD); // move cursor to 2nd row, 1st column
    inputLCD(instruct_msg1);           // Send second line
  
  }
   
  delay1ms(1000);
       
}

// pan and tilt functions
void panServo(int direction){
   if(direction == 1){
      PWMDTY67 -= 50;
      delay1ms(1);  
      
   } else if(direction == 0){
      PWMDTY67 += 50;
      delay1ms(1);
   }
   
   // ensuring never exceeds maximium or minimum limits
   if(PWMDTY67 < 1350){
     PWMDTY67 = 1350;
   }else if(PWMDTY67 > 3150){
     PWMDTY67 = 3150;
   }
  
  delay1ms(5);
}

void tiltServo(int direction){
    if(direction == 1){
      PWMDTY45 -= 50;
      delay1ms(1);
        
   } else if(direction == 0){
      PWMDTY45 += 50;
      delay1ms(1);
   }
   
   // ensuring never exceeds maximium or minimum limits
   if(PWMDTY45 < 1350){
     PWMDTY45 = 1350;
   }else if(PWMDTY45 > 3150){
     PWMDTY45 = 3150;
   }
  
  delay1ms(5);   
}
