#ifndef MUSIC_FUNCTIONS_HEADER
#define MUSIC_FUNCTIONS_HEADER

// Music Module Functions
void delay10ms(int duration);
void playnote(unsigned int * score, unsigned int * duration);
void bootJingle(void);

void Init_TC5 (void);
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void TC5_ISR(void);

#endif