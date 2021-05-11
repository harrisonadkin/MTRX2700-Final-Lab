#ifndef SERIAL_FUNCTIONS_HEADER
#define SERIAL_FUNCTIONS_HEADER

// Serial Module Functions
typedef struct {
  int function;
  int interface;
  int baudRate;
}Serial;

void serialInitialise(int baudRate, int interface, int function, unsigned char ** dataLocation);
void setControl(void);
void readSerial(void);
void writeSerial(void);
void resetSerial(void);


// Serial interrupts definition
//#pragma CODE_SEG __NEAR_SEG NON_BANKED 
//__interrupt void SCI0_ISR(void);
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
__interrupt void SCI1_ISR(void);  


#endif