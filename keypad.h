/*-------------------------------------------------------------------------------------
[FILE NAME]

[AUTHOR(S)]  : Muhammed Eldabea Hashem

[DATE CREATED] 17 April 2020


[DESCRIPTION]

-----------------------------------------------------------------------------------------*/



#ifndef KEYPAD_H_
#define KEYPAD_H_


/*---------------------------------------INCLUDES---------------------------------------*/
#include "micro_config.h"

/*-------------------------------Definitions and configuration---------------------------*/

#define NUM_of_Rows  4  /*select the number of rows */

#define NUM_of_col  4  /*select the number of rows */

#define KeyPad_ReadPORT PINA /*pins that is used to input to check which button in any row is pressed */

#define KeyPad_OutPort  PORTA /*pins used as input to check which button in any column is pressed  */

#define KeyPad_controlPort DDRA  /*select the port we will deal with */


/*----------------------------------------Enums-----------------------------------------*/

/*--------------------------------Structure and Unions----------------------------------*/

/*-----------------------------------------Macros---------------------------------------*/

/*--------------------------------Function Declarations--------------------------------*/


char  KeyPad_getPressedKey(void) ;









#endif /* KEYPAD_H_ */
