/*
 * 		[file name]   : hmi.c
 *  	[Created on]  : Jul 20, 2020
 *      [Author]      : Muhammed Eldabea Hashem
 *      [Description] : Function declarations and configuration used
 *
 */



/* =================================================================== *
      ------------------------>includes<----------------------------
 * =================================================================== */

#include "hmi.h"

/* =================================================================== *
       -------------------->Global Variable<--------------------------
 * =================================================================== */

/*a variable used to switch between function */
volatile unsigned char G_funID = 0 ;

/*create an array of pointer to function
 *
 *  */

/*===========================================================
 *
 *
 * 		 ************ 			 **************************
 * 	    | Function ID | 		|      Function name       |
 * 		 ************            **************************
 * 		     0						HMI_welcomeScreen
 * 			 1 						HMI_LOGINOPTIONmenu
 * 		     2 						HMI_EnterPassword
 * 		     3						HMI_Enter_NEWPassWord
 * 		     4						HMI_check_NEWPassWord
 * 		     5						HMI_CHECKoldpassword
 *
 * =========================================================== */



void (*PtrToFunc[6])(void) = {HMI_welcomeScreen,HMI_LOGINOPTIONmenu,
		HMI_EnterPassword,
		HMI_Enter_NEWPassWord,
		HMI_check_NEWPassWord,
		HMI_CHECKoldpassword} ;


/* ==================================================================== *
      ------------> Super loop and main application<---------------
 * ==================================================================== */


int main (void ) {
	/*configuration for the UART module */
	UART_configuration uartconfig = {UART_TXRXmode,
			Uart_AsynchrouncousOperationModeDoubleSpeedMode
	,UART_1BITStop,UART_EnableParityEvenParity,UART_8_bit,
	UART_fallingXCKedgeRX} ;

	/*initialize the UART with given configuration*/
	UART_init(&uartconfig) ;

	/*LCD initialization
	 *
	 * used Port
	 *    >> PORTC
	 *    >> PORTD
	 *
	 * */

	LCD_init() ;


while(1){

	/*the operation will run with Func_id = 0
	 *  it will start with the
	 *  HMI_welcome screen
	 * */

	(*PtrToFunc[G_funID])() ;

}

}

/* ==================================================================== *
      ----------------->Functions Definitions<--------------------
 * ==================================================================== */






void HMI_welcomeScreen(void) {

	/*--------------------------------------------------------------------------------------
	[FUNCTION NAME] : HMI_welcomeScreen

	[DESRIPTION]  : these function is used to show a welcome message to the user with next steps
						1-show message "Door locked"
						2-show message "press on to start"
						3-wait for the user to press on
						4-send a control signal to control_ECU to check for saved password
					  	5- the response of the previous will determinate the direction of the code
					  	   it will go to add a new password or show a menu
					  	   to login or change the password
	[Function ID]  : 0
	[ARGUMENT(S)]  :
	   [IN]  :void
	   [OUT] : void
	[Return]      : void
	---------------------------------------------------------------------------------------*/

	/*display a welcome message */
	lcd_DisplayStringInRow_colm("Door_locked", 0, 5) ;

	/*clear screen */
	LCD_clearSreen() ;

	/*show a start operation massage*/
	lcd_DisplayStringInRow_colm("press on to start", 0, 3) ;

	/*wait until ON key is pressed */
	while(KeyPad_getPressedKey() != 13) {} ;

	/*wait the pressed time */
	_delay_ms(300) ;

	LCD_clearSreen() ;

	UART_SendData(Check_ForSaverPassword) ;
	if(UART_GetData() == NO_savedPassword) {
		/*we will go to add new password*/
		G_funID = 3 ;
	}
	else{
		/*we will go to enter a old password*/
		G_funID = 1 ;
	}

}

void HMI_LOGINOPTIONmenu(void){

	/*--------------------------------------------------------------------------------------
	[FUNCTION NAME] :  HMI_LOGINOPTIONmenu()

	[DESRIPTION]   : show option menu for the user in case of we have  a saved password
						>> it will ask user to select between tow option :
						 1-> press on to login
						 2-> press 2 to change the password


	[Function ID]  : 1
	[ARGUMENT(S)]  :
	   [IN]  :void
	   [OUT] : void
	[Return]      : void
	---------------------------------------------------------------------------------------*/
	unsigned char  signal = 0 ;

	/*clear the screen and Display the instruction */
	LCD_clearSreen() ;
	lcd_DisplayStringInRow_colm("press <1> to login ", 0, 3) ;
	lcd_DisplayStringInRow_colm("press <2> to change the password ", 1, 3) ;

	/*wait for pressed KEY time */
	_delay_ms(200) ;
	signal = KeyPad_getPressedKey() ;

	if (signal == 1){
		UART_SendData(LOGIN_operation) ;
		G_funID = 2 ;

	}
	else if (signal == CHANGE_PASSWORD_operation) {
		UART_SendData(CHANGE_PASSWORD_operation) ;
		G_funID = 3 ;
	}

}



void HMI_EnterPassword() {
	/*--------------------------------------------------------------------------------------
	[FUNCTION NAME] : HMI_EnterPassword()

	[DESRIPTION]   : this function has the function and take operation of
	 	 	 	 	 1- ask user to enter the password
	 	 	 	 	 2-send a control signal to the Control_ECU to be ready
	 	 	 	 	 3-send password byte by byte
	 	 	 	 	 4-wait a signal from the Control_ECU with a KEY flag
	 	 	 	 	 	 to open the door or re-enter the password or
	 	 	 	 	 	 to call the police
						>> it will get her from the HMI_welcomeScreen()
						>> or by the function it self in case a wrong password
	[Function ID]  : 2
	[ARGUMENT(S)]  :
	   [IN]  :void
	   [OUT] : void
	[Return]      : void
	---------------------------------------------------------------------------------------*/

	/*this variable used to detrminate how many time the user
	 * enter a wrong password if he enter it three times wrong
	 *  a thieve alert will be run  */
	static unsigned char PASSWORD_WRING_COUNTER = 0  ;

	LCD_DisplyString("Enter your password to login") ;
	LCD_clearSreen() ;
	/*send a control to control_ecu to be ready */
	UART_SendData(HMI_READY_TO_SEND) ;


	/*loop to enter the password*/
	for (unsigned char inc = 0 ; inc<PASSWORD_size ; inc++){

		/*every time user pressed a key an gastric will be shown*/
		UART_SendData(KeyPad_getPressedKey()) ;
		LCD_DisplyString("*") ;

		/*wait pressing time */
		_delay_ms(300) ;

	}

	/* wait for the control signal */
	unsigned char KEY = UART_GetData() ;
	LCD_clearSreen() ;

	if (KEY==OPEN_DOOR){
		LCD_DisplyString("WELCOME") ;
		LCD_clearSreen() ;
		LCD_DisplyString("DoOr is Opening ") ;
		G_funID =0 ;
	}

	else {

		if ((KEY == WRONG_PASSWORD )&& ((PASSWORD_WRING_COUNTER %3)  != 0  )){
			LCD_DisplyString("Wrong password ") ;
			_delay_ms(200) ;
			lcd_clearScreen() ;
			PASSWORD_WRING_COUNTER++ ;
			G_funID = 2 ;

		}

		else if (KEY == Catch_A_thief){
			LCD_DisplyString("YOU ARE A THIEF !! ") ;
			_delay_ms(200) ;
			lcd_clearScreen() ;
			PASSWORD_WRING_COUNTER = 0 ;
			LCD_DisplyString("I will call police") ;
			lcd_clearScreen() ;
			_delay_ms(200) ;
			LCD_DisplyString("YOU ARE A THIEF !! ") ;
			/*wait for Buzzer */
			_delay_ms(500) ;
			_delay_ms(500) ;
			_delay_ms(500) ;
			G_funID = 0 ;

		}

	}

}

void HMI_Enter_NEWPassWord(void){
	/*--------------------------------------------------------------------------------------
	[FUNCTION NAME] : HMI_EnterPassword()

	[DESRIPTION]   : this function has the operation of handling the process of saving a new password
						it will work with the sequence
						1-send a signal to control_ECU saying "Ready"
						2-print a message for the user to "enter new password"
						3- send data byte by byte
						4-Go to Check new password

	[Function ID]  : 3
	[ARGUMENT(S)]  :
	   [IN]  :void
	   [OUT] : void
	[Return]      : void
	---------------------------------------------------------------------------------------*/
	/*clear screen and Display the message */
	LCD_clearSreen() ;
	LCD_DisplyString("Enter new password") ;
	_delay_ms(200) ;
	LCD_clearSreen() ;

	/*send a signal to check availability of Control_ECU*/
	UART_SendData(HMI_READY_TO_SEND) ;


	/*loop for password sending */
	for (unsigned char inc ; inc<PASSWORD_size ; inc++ )
	{
		/*get pressed key and sending it
		 * show Gastric sign every time key pressed
		 * wait for pressing time
		 * */
		UART_SendData(KeyPad_getPressedKey()) ;
		LCD_DisplyString("*") ;
		_delay_ms(300) ;
	}


	G_funID = 4 ;


}

void HMI_check_NEWPassWord(void){
	/*--------------------------------------------------------------------------------------
	[FUNCTION NAME] : HMI_checkPassword()

	[DESRIPTION]   : this function has the operation of handling the process of saving a new password
						it will work with the sequence
						1-send a signal to control_ECU saying "Ready"
						2-print a message for the user to "enter new password again"
						3- send data byte by byte
						4-Go to Check new password

	[Function ID]  : 4
	[ARGUMENT(S)]  :
	   [IN]  :void
	   [OUT] : void
	[Return]      : void
	---------------------------------------------------------------------------------------*/
	/*clear screen and Display the message */
	LCD_clearSreen() ;
	LCD_DisplyString("Enter password again ") ;
	_delay_ms(200) ;
	LCD_clearSreen() ;

	/*send a signal to check availability of Control_ECU*/
	UART_SendData(HMI_READY_TO_SEND) ;


	/*loop for password sending */
	for (unsigned char inc ; inc<PASSWORD_size ; inc++ )
	{
		/*get pressed key and sending it
		 * show Gastric sign every time key pressed
		 * wait for pressing time
		 * */
		UART_SendData(KeyPad_getPressedKey()) ;
		LCD_DisplyString("*") ;
		_delay_ms(300) ;
	}

	unsigned char Key = UART_GetData() ;
	if (Key == VALID_DATA){
		G_funID = 1 ;
	}
	else if (Key == UNVALID_DATA)
	{
		G_funID = 0 ;
	}

}

void HMI_CHECKoldpassword () {

	/*--------------------------------------------------------------------------------------
	[FUNCTION NAME] : HMI_CHECKoldpassword ()
	[DESRIPTION]   : used to check the old password that entered by the user to the goal of
					change the old one if password is Write it
					will go the ENTER new password  if it it Wrong  it will ask the user to

	[Function ID]  : 5
	[ARGUMENT(S)]  :
	   [IN]  :void
	   [OUT] : void
	[Return]      : void
	---------------------------------------------------------------------------------------*/

	/*hold the coming signal from control ECU*/
	unsigned char key ;


	/*ASK user to  enter the old password to change it*/
	LCD_DisplyString("Enter old password to change") ;
	_delay_ms(300) ;
	/*send a signal to the control ECU to be ready */
	UART_SendData(HMI_READY_TO_SEND) ;

	LCD_clearSreen() ;
	for (unsigned char inc ; inc<PASSWORD_size ; inc++) {
		/*send pressed key and wait for pressed key*/
		UART_SendData(KeyPad_getPressedKey()) ;
		LCD_DisplyString("*") ;
		_delay_ms(300) ;

	}

	LCD_clearSreen() ;


	unsigned char key=UART_GetData() ;
	if (key == PASSWORD_is_acceptable){
		LCD_DisplyString("Password is changed successfully") ;
		G_funID = 3 ; /*got to enter new password*/
	}
	else if (key == PASSWORD_is_NOTacceptable){
		LCD_DisplyString("a wrong password is entered ") ;
		G_funID=0/*go to main screen */ ;
	}

}

