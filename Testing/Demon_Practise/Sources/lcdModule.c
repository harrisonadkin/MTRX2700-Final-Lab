#include "derivative.h"
#include "lcdModule.h"
#include "musicModule.h"

void InitLCD(void){
  
  LCD_DIR = 0b11111111;     /* configure LCD_DAT port for output */
  delay1ms(100);            /* Wait for LCD to be ready */
  writeLCD(0b00101000,CMD); /* set 4-bit data, 2-line display, 5x7 font */
  writeLCD(0b00001100,CMD); /* turn on display, (bit 2 for cursor, bit 1 for blinking) */
  clearLCD();               /* clear screen, move cursor to home */
  delay1ms(1); 
}

void inputLCD(char *lcdString)
{
  while (*lcdString) { /* While character to send */
    writeLCD(*lcdString,DATA); /* Write data to LCD */
    lcdString++; /* Go to next character */
  }
}


void writeLCD(char string, char type)
{
  char string_lo, string_hi;        /* Split input string into high and low */
  string_hi = (string & 0b11110000) >> 2; /* Upper 4 bits of c */
  string_lo = (string & 0b00001111) << 2; /* Lower 4 bits of c */
  
  if (type == DATA) LCD_DAT |= LCD_RS; /* select LCD data register */
  else LCD_DAT &= (~LCD_RS); /* select LCD command register */
  
  if (type == DATA)
    LCD_DAT = string_hi|LCD_E|LCD_RS; /* output upper 4 bits, E, RS high */
  else
    LCD_DAT = string_hi|LCD_E; /* output upper 4 bits, E, RS low */
  
  LCD_DAT |= LCD_E; /* pull E signal to high */
  LCD_DAT &= (~LCD_E); /* pull E to low */
  
  if (type == DATA)
    LCD_DAT = string_lo|LCD_E|LCD_RS; /* output lower 4 bits, E, RS high */
  else
    LCD_DAT = string_lo|LCD_E; /* output lower 4 bits, E, RS low */

  LCD_DAT |= LCD_E; /* pull E to high */
  LCD_DAT &= (~LCD_E); /* pull E to low */
  delay1ms(1); /* Wait for command to execute */
}


void clearLCD(void){
  writeLCD(0b00000001,CMD); /* clear screen, move cursor to home */  
}

