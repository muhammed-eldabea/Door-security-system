/*
 * 		[file name]   : hmi.h
 *  	[Created on]  : Jul 20, 2020
 *      [Author]      : Muhammed Eldabea Hashem
 *      [Description] : Function declarations and configuration used
 *
 */


#ifndef HMI_H_
#define HMI_H_



/*==========================> INCLUDES <===============================*/

#include "LCD/lcd.h"
#include "UART/uart.h"
#include "KEYPAD/keypad.h"

/*=========================> Definitions <=============================*/



/*===============> External Module shared configurations <===============*/

#define Check_ForSaverPassword		  20
#define NO_savedPassword              21
#define HMI_READY_TO_SEND             22
#define ControlECU_READY_TO_RECIVE    23
#define PASSWORD_size           	   8
#define OPEN_DOOR              		  24
#define CATCH_THIEF            		  25
#define WRONG_PASSWORD                26
#define VALID_DATA                    27
#define ECU_READY_TO_RECIVE           28
#define PASSWORD_is_acceptable        29
#define PASSWORD_is_NOTacceptable     30

/*=========================> Enumerations <============================*/


/*=====================> Structure and Unions <========================*/


/*============================> Macros <===============================*/


/*=====================> Function Declarations <========================*/
void HMI_welcomeScreen(void)  ;
void HMI_EnterPassword()  ;
void HMI_Enter_NEWPassWord(void) ;
void HMI_check_NEWPassWord(void) ;
void HMI_CHECKoldpassword () ;
#endif /* HMI_H_ */
