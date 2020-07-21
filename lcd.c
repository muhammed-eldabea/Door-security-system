/*-------------------------------------------------------------------------------------
[FILE NAME]  : lcd.c

[AUTHOR(S)]  : Muhammed Eldabea Hashem

[DATE CREATED] 17 April 2020


[DESCRIPTION] :this file contain the implementation of functions related to the LCD module

-----------------------------------------------------------------------------------------*/








/*-----------------------------------------INCLUDES-------------------------------------*/

#include  "lcd.h"


/*--------------------------------------Global Variable---------------------------------*/


/*-----------------------------------Functions Definitions------------------------------*/





void LCD_init (void )
{
	/*----------------------------------------------------------------------------
	[FUNCTION NAME] :LCD_init

	[DESRIPTION] :used to initialize  the LCD module

	[ARGUMENT(S)]  :
	   [IN]  : void


	   [OUT] : void

	[Return]      : void

	-------------------------------------------------------------------------------*/

	SETBIT(lcd_controlRegister,LCD_enablePin) ; /*configure the enable pin as out */
	SETBIT(lcd_controlRegister,lcd_RxWpin) ; /*configure the  read or write  pin as out */
	SETBIT(lcd_controlRegister,LCD_RSpin) ;  /*configure the register select pin as out */


#if LCD_m_ModeSelect ==8
	lcd_DataRegister = 0xff ;
	LCD_sendCommand(lcd_8bit_2line) ;


#else

#if lcd_4_bit_pins_location = upper


	lcd_DataRegister |= 0xf0 ;
	LCD_sendCommand(lcd_4bit_2line) ;
#else

	lcd_DataRegister |= 0x0f ;
	LCD_sendCommand(lcd_4bit_2line) ;

#endif






#endif




	LCD_sendCommand(lcd_Diplay_courser_off) ;

	LCD_sendCommand(lcd_clearScreen) ; /*send an command to clear screen */













}








void LCD_DisplayData(unsigned char DATA)
{

	/*----------------------------------------------------------------------------
		[FUNCTION NAME] :LCD_DisplayData

		[DESRIPTION] :used to display a char on the screen

		[ARGUMENT(S)]  :
		   [IN]  :
		          1- unsigned char with name "DATA" -> used to define the displayed data
		   [OUT] : void

		[Return]      : void

		-------------------------------------------------------------------------------*/

	/*  -> note all these steps are dependent on the data sheet provided <-  */



	SETBIT(LCD_contrlPort,LCD_RSpin) ;   /*clear the register select pin  as we send instruction*/

	CLEARBIT(LCD_contrlPort,lcd_RxWpin) ;  /*be sure that the read write pin is cleared */

	_delay_ms(1) ;

	SETBIT(LCD_contrlPort,LCD_enablePin) ; /*set the enable pin */

	_delay_ms(1) ;
#if LCD_m_ModeSelect == 8

	LCD_DATAPort=DATA ; /*make the LCD writing port out the command data */

	_delay_ms(1) ;

	CLEARBIT(LCD_contrlPort,LCD_enablePin) ; /*clear the enable pin */

	_delay_ms(1) ;

#elif LCD_m_ModeSelect ==4

#if lcd_4_bit_pins_location == upper
	LCD_DATAPort = (LCD_DATAPort & 0x0f) | (DATA & 0xf0) ; /*send the first 4 bits */

#else

	LCD_DATAPort = (LCD_DATAPort & 0xf0) | ((DATA & 0xf0)>>4) ; /*send the last 4 bits first */

#endif

	_delay_ms(1) ;
	CLEARBIT(LCD_contrlPort,LCD_enablePin) ;
	_delay_ms(1) ;
	SETBIT(LCD_contrlPort,LCD_enablePin) ;
	_delay_ms(1) ;

#if lcd_4_bit_pins_location == upper

	LCD_DATAPort = (LCD_DATAPort & 0x0f) | ((DATA & 0xf0)<<4) ; /*send the first 4 bits */

#else

	LCD_DATAPort = (LCD_DATAPort & 0xf0) | (DATA & 0xf0) ; /*send the last 4 bits first */

#endif


#endif

}





void LCD_sendCommand(unsigned char command)
{

	/*----------------------------------------------------------------------------
		[FUNCTION NAME] :LCD_sendCommand

		[DESRIPTION] :used to send command to the LCD module so you can clear the screen an show the courser etc

		[ARGUMENT(S)]  :
		   [IN]  :
		          1- unsigned char with name "command" -> used to define the command
		   [OUT] : void

		[Return]      : void

		-------------------------------------------------------------------------------*/

	/*  -> note all these steps are dependent on the data sheet provided <-  */



	CLEARBIT(LCD_contrlPort,LCD_RSpin) ;   /*clear the register select pin  as we send instruction*/

	CLEARBIT(LCD_contrlPort,lcd_RxWpin) ;  /*be sure that the read write pin is cleared */

	_delay_ms(1) ;

	SETBIT(LCD_contrlPort,LCD_enablePin) ; /*set the enable pin */

	_delay_ms(1) ;

#if LCD_m_ModeSelect == 8

	LCD_DATAPort=command ; /*make the LCD writing port out the command data */

	_delay_ms(1) ;

	CLEARBIT(LCD_contrlPort,LCD_enablePin) ; /*clear the enable pin */

	_delay_ms(1) ;

#elif LCD_m_ModeSelect ==4

#if lcd_4_bit_pins_location == upper
	LCD_DATAPort = (LCD_DATAPort & 0x0f) | (command & 0xf0) ; /*send the first 4 bits */

#else

	LCD_DATAPort = (LCD_DATAPort & 0xf0) | ((command & 0xf0)>>4) ; /*send the last 4 bits first */

#endif

	_delay_ms(1) ;
	CLEARBIT(LCD_contrlPort,LCD_enablePin) ;
	_delay_ms(1) ;
	SETBIT(LCD_contrlPort,LCD_enablePin) ;
	_delay_ms(1) ;
#if lcd_4_bit_pins_location == upper
	LCD_DATAPort = (LCD_DATAPort & 0x0f) | ((command & 0xf0)<<4) ; /*send the first 4 bits */

#else

	LCD_DATAPort = (LCD_DATAPort & 0xf0) | (command & 0xf0) ; /*send the last 4 bits first */

#endif


#endif

}


void LCD_DisplyString(char str[])
{

	/*----------------------------------------------------------------------------
			[FUNCTION NAME] : LCD_DisplyString

			[DESRIPTION] :used to Display a string on the screen

			[ARGUMENT(S)]  :
			   [IN]  :
			          1-  pointer to array of character "str" -> used to define the string that will be shown
			   [OUT] : void

			[Return]      : void

			-------------------------------------------------------------------------------*/

	while(*str != '\0')
	{
		LCD_DisplayData(*str) ;
		str++ ;
	}
}



void LCD_DisplayInteger(unsigned char Int_data)
{

	/*----------------------------------------------------------------------------
				[FUNCTION NAME] : LCD_Displyinteger

				[DESRIPTION] :used to Display a integer on the screen by converting it into a string

				[ARGUMENT(S)]  :
				   [IN]  :
				          1-  integer value "int_data" -> used to define the integer value that will be converted

				          2- local variables to the function are :
				              1- char buffer used as a buffer to store the returned values from the itoa function
				   [OUT] : void

				[Return]      : void

				-------------------------------------------------------------------------------*/

	char buff[16]; /* String to hold the ASCII result */
	   itoa(Int_data,buff,10); /* 10 for decimal */
	   LCD_DisplyString(buff);
}


void lcd_GotoRowANDcoulm(unsigned char row , unsigned char col)
{

	/*----------------------------------------------------------------------------
				[FUNCTION NAME] : LCD_Displyinteger

				[DESRIPTION] :used to move the courser to a specific position on the screen

				[ARGUMENT(S)]  :
				   [IN]  :
				           1- unsigned char ->  "row"  -> used to define the row at which data will be shown
				           2- unsigned char ->  "col"  -> used to define the column  at which data will be shown
				   [OUT] : void

				[Return]      : void

				-------------------------------------------------------------------------------*/

	unsigned char  Address;

		/* first of all calculate the required address */
		switch(row)
		{
			case 0:
					Address=col;
					break;
			case 1:
					Address=col+0x40;
					break;
			case 2:
					Address=col+0x10;
					break;
			case 3:
					Address=col+0x50;
					break;
		}
		/* to write to a specific address in the LCD
		 * we need to apply the corresponding command 0b10000000+Address */
		LCD_sendCommand(Address | 0x80);
}



void lcd_DisplayStringInRow_colm(char str[] ,unsigned char row , unsigned char col )
{

	/*----------------------------------------------------------------------------
				[FUNCTION NAME] : LCD_Displyinteger

				[DESRIPTION] :used to Display a string on a specific position on the screen  the screen

				[ARGUMENT(S)]  :
				   [IN]  :
				          1-  pointer to array of char "str" -> used to define the string data that will be shown
				          2- unsigned char ->  "row"  -> used to define the row at which data will be shown
				          3- unsigned char ->  "col"  -> used to define the column  at which data will be shown
				   [OUT] : void

				[Return]      : void

				-------------------------------------------------------------------------------*/

	lcd_GotoRowANDcoulm(row , col) ;
	LCD_DisplyString(str) ;

}


void LCD_clearSreen()
{
	/*----------------------------------------------------------------------------
				[FUNCTION NAME] : lcd_clearScreen

				[DESRIPTION] :used to clear the  Display

				[ARGUMENT(S)]  :
				   [IN]  : void

				[Return]      : void

				-------------------------------------------------------------------------------*/



	LCD_sendCommand(lcd_clearScreen) ;
}
