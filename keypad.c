/*-------------------------------------------------------------------------------------
[FILE NAME]

[AUTHOR(S)]  : Muhammed Eldabea Hashem

[DATE CREATED] 17 April 2020


[DESCRIPTION]

-----------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------INCLUDES-----------------------------------------------------------------------*/

#include "keypad.h"


/*--------------------------------------------------------------------Function Macros---------------------------------------------------------------*/

#if NUM_of_col ==3
static unsigned char KEYpad_4x3(unsigned char buttun) ;
#elif NUM_of_col ==4
static  unsigned char KEYpad_4x4(unsigned char buttun) ;

#endif






/*--------------------------------------------------------------Functions Definations----------------------------------------------------------------*/


char  KeyPad_getPressedKey(void)
{

	/*--------------------------------------------------------------------------------------
	[FUNCTION NAME]  :KeyPad_getPressedKey

	[DESRIPTION]  :used to initialize the I\O register ,return the position of pressed button

	[ARGUMENT(S)]  :
	   [IN]  : void
	   [OUT] : the position of the button
	[Return]      : position

	---------------------------------------------------------------------------------------*/

	unsigned char col,row ;
	while (1)
	{

		for (col=0 ; col<NUM_of_col;col++)
		{

			KeyPad_controlPort=(0b000010000<<col) ; /*set only one column pin as output */

			KeyPad_OutPort = (~(0b000010000<<col)) ;/*this line have tow task first one is to Set all output pins to high and enable the internal resistance */

			for (row=0 ; row<NUM_of_Rows ; row++)
			{
				if(!(KeyPad_ReadPORT &(1<<row)))
				{


#if NUM_of_col==3

					return KEYpad_4x3((row*NUM_of_col)+col+1) ; /*this line will return the position of the button as we assumed a multiplexed matrix  */

#elif NUM_of_col==4

					return KEYpad_4x4((row*NUM_of_col)+col+1) ; /*this line will return the position of the button as we assumed a multiplexed matrix  */
#endif
				}



			}




		}
	}

}








#if NUM_of_col==3




static   unsigned char KEYpad_4x3(unsigned char buttun)
{
	/*--------------------------------------------------------------------------------------
	[FUNCTION NAME]  :keypad_4x3

	[DESRIPTION]  :used to customize the button with specific data

	[ARGUMENT(S)]  :
	   [IN]  :
	          -button : this argument represent the position of the button in the matrix


	   [OUT] : the customized value of the button

	[Return]      : customized value of the button

	---------------------------------------------------------------------------------------*/



	switch (buttun) {
	case 10:
		return '*' ;
		break;
	case 12 :
		return '#' ;
		break ;
	default:
		return buttun ;
		break;
	}
}








#else





static  unsigned char KEYpad_4x4(unsigned char buttun)
{
	/*--------------------------------------------------------------------------------------
	 	[FUNCTION NAME]  :keypad_4x4

	 	[DESRIPTION]  :used to customize the button with specific data

	 	[ARGUMENT(S)]  :
	 	   [IN]  :
	 	          -button : this argument represent the position of the button in the matrix


	 	   [OUT] : the customized value of the button

	 	[Return]      : customized value of the button

	 	---------------------------------------------------------------------------------------*/



	switch (buttun)
	{
	case 1: return 7;
	break;
	case 2: return 8;
	break;
	case 3: return 9;
	break;
	case 4: return '%'; // ASCII Code of %
	break;
	case 5: return 4;
	break;
	case 6: return 5;
	break;
	case 7: return 6;
	break;
	case 8: return '*'; /* ASCII Code of '*' */
	break;
	case 9: return 1;
	break;
	case 10: return 2;
	break;
	case 11: return 3;
	break;
	case 12: return '-'; /* ASCII Code of '-' */
	break;
	case 13: return 13;  /* ASCII of Enter */
	break;
	case 14: return 0;
	break;
	case 15: return '='; /* ASCII Code of '=' */
	break;
	case 16: return '+'; /* ASCII Code of '+' */
	break;
	default:
		return buttun  ;
	}


}

#endif


