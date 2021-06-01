#ifndef LCD_FUNCTIONS_HEADER
#define LCD_FUNCTIONS_HEADER

#define LCD_DAT PORTK /* Port K drives LCD data pins, E, and RS */
#define LCD_DIR DDRK /* Direction of LCD port */
#define LCD_E  0b00000010 /* LCD E signal */
#define LCD_RS 0b00000001 /* LCD Register Select signal */
#define CMD  0 /* Command type for put2lcd */
#define DATA 1 /* Data type for put2lcd */

/* Prototypes for functions in lcd.c */
void InitLCD(void); /* Initialize LCD display */
void writeLCD(char string, char type); /* Write command or data to LCD controller */
void inputLCD (char *lcdString); /* Write a string to the LCD display */
void clearLCD(void);

#endif