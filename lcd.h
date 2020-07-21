/*-------------------------------------------------------------------------------------
[FILE NAME]    :lcd.h

[AUTHOR(S)]    : Muhammed Eldabea Hashem

[DATE CREATED] : 17 April 2020


[DESCRIPTION]  : this file is containing the declarations of needed function to use LCD
                 it also contain the configuration

-----------------------------------------------------------------------------------------*/



#ifndef LCD_H_
#define LCD_H_

/*---------------------------------------INCLUDES---------------------------------------*/

#include "micro_config.h"
#include <stdlib.h>

/*-------------------------------Definitions and configuration---------------------------*/
#define lcd_DataRegister DDRC /*chose the data register port */
#define lcd_controlRegister DDRD /*chose the control register port */
#define LCD_contrlPort PORTD /*chose the control port */
#define LCD_DATAPort  PORTC  /*chose the data port */
#define LCD_m_ModeSelect 8 /* the mode by which the LCD will run  we have tow mode 4_bit / 8_bit */
#define LCD_enablePin 0 /*enable pin */
#define LCD_RSpin 2  /*register select pin to  configure  the data we send as instruction or a data we will display */
#define lcd_RxWpin 1 /*read write  mode select */
#define lcd_4_bit_pins_location upper /* in case we use the 4_bit mode we could configure that we will use upper or lower pin in the register */
#define lcd_Diplay_courser_on 0x0E  /*use this command to display the courser on the screen */
#define lcd_Diplay_courser_off 0x0C /*use this command to hide the courser on the screen */
#define lcd_clearScreen 0x01  /*use this command to clear  the screen */
#define lcd_8bit_1line 0x30 /*set a 8_bit mode with only 1 line  */
#define lcd_8bit_2line 0x38/*set a 8_bit mode with  2 line  */
#define lcd_4bit_1line 0x20/*set a 4_bit mode with only 1 line  */

/*-----------------------------------------Macros---------------------------------------*/

#define SETBIT(REG,BIT)       ( REG |=(1<<BIT))
#define CLEARBIT(REG,BIT)     ( REG &=(~(1<<BIT)))
#define ToggleBIT(REG,BIT)    ( REG ^=(1<<BIT))
#define CHECKifSET(REG,BIT)   ( REG & (1<<BIT))
#define CHECKifClear(REG,BIT) (!( REG & (1<<BIT)))
#define LCD_setPosition(POS) ((0x80)+(POS)


/*--------------------------------Function Declarations--------------------------------*/


void LCD_init (void ) ;
void LCD_DisplayData(unsigned char DATA) ;
void LCD_sendCommand(unsigned char command) ;
void LCD_DisplayInteger(unsigned char Int_data) ;
void LCD_DisplyString(char str[]) ;
void LCD_clearSreen();
void lcd_DisplayStringInRow_colm(char str[] ,unsigned char row , unsigned char col ) ;
void lcd_GotoRowANDcoulm(unsigned char row , unsigned char col) ;






#endif /* LCD_H_ */
