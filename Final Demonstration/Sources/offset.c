#include "l3g4200d.h"
#include "offset.h"
#include "iic.h"
#include "serialModule.h"
#include "musicModule.h"
#include "string.h"
#include "simple_serial.h"

int i, j;


void calibrateGyro(GyroRaw *raw_data, GyroRaw *gyro_offset)
{
  
  for (i = 0; i < 20; i++) {
    
    getRawDataGyro(raw_data);
    
    gyro_offset->x = gyro_offset->x + raw_data->x;
    gyro_offset->y = gyro_offset->y + raw_data->y;
    gyro_offset->z = gyro_offset->z + raw_data->z;
    delay1ms(10);
    //sprintf(buffer1, "%d, %d, %d\r\n", gyro_offset->x,  gyro_offset->y,  gyro_offset->z);  
    //SCI1_OutString(buffer1);
    
  }
  
  gyro_offset->x = gyro_offset->x*0.05;
  gyro_offset->y = gyro_offset->y*0.05;
  gyro_offset->z = gyro_offset->z*0.05;
    
}

void convertUnits(AccelRaw *raw_data, AccelScaled *scaled_data, AccelRaw* accel_offset){
    scaled_data->x = (float)(raw_data->x - accel_offset->x)/250;
    scaled_data->y = (float)(raw_data->y - accel_offset->y)/250;
    scaled_data->z = (float)(raw_data->z - accel_offset->z)/250;
} 

void calibrateAccel(AccelRaw *raw_data, AccelRaw *accel_offset)
{
  
  for (j = 0; j < 20; j++) {
    
    getRawDataAccel(raw_data);
    accel_offset->x = accel_offset->x + raw_data->x;
    accel_offset->y = accel_offset->y + raw_data->y;
    accel_offset->z = accel_offset->z + raw_data->z - 250;
    delay1ms(10);
  
  }
  
  accel_offset->x = accel_offset->x*0.05;
  accel_offset->y = accel_offset->y*0.05;
  accel_offset->z = accel_offset->z*0.05;
    
}