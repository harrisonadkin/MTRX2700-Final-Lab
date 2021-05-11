#ifndef TIMERS_HEADER
#define TIMERS_HEADER


// function to initialise the timer
void Init_TC5 (void);
void Init_Math (void);

// function for overflows
void clearTOF(void);
unsigned long calcTime(unsigned int time);

// Timer interrupt definition
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
__interrupt void TC5_ISR(void);
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
__interrupt void TOF_ISR(void); 


#endif