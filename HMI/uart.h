/*
 * 		file name : uart.h
 *  	Created on: Jul 7, 2020
 *      Author: Muhammed Eldabea Hashem
 *      Description : Function declarations and configuration used
 *
 */

#ifndef UART_H_
#define UART_H_


/*==========================> INCLUDES <===============================*/
#include "avr/io.h"
#include "avr/interrupt.h"
#include "avr/delay.h"

/*=========================> Definitions <=============================*/
#define UART_BAUDRATE  9600
#define Uart_RX_interrupt_enable  0
#define Uart_TX_interrupt_enable  0
#define Uart_FrameError_Check_enable  0
#define Uart_DataOverRunError_Check_enable  0
#define Uart_ParityError_Check_enable  0
#define Uart_DataRegisterEmpty_interrupt_enable  0
#define Uart_Enable_multiProcessor_Communication_mode 0

/*===============> Extern Module shared configurations <===============*/


/*=========================> Enumerations <============================*/

typedef enum {
	/*configuration for the operation mode of the UART */
	Uart_AsynchrouncousOperationMode,Uart_SynchrounousoperationMode,
	Uart_AsynchrouncousOperationModeDoubleSpeedMode
}UART_operationMode;

typedef enum {
	/*configuration for the state of the UART  TX/RX*/
	UART_txmode,UART_RXmode,UART_TXRXmode
}UART_Operationstate;

typedef enum {
	/*Configuration the stop bit size used in frame */
	UART_1BITStop,UART_2BITStop
}UART_StopBitConfiguration;

typedef enum {
	/*configure the parity check method*/
	UART_DisableParityCheck,UART_ReservedBIT_PArityCHeck,
	UART_EnableParityEvenParity,UART_EnableOddEvenParity
}UARTParityCheck;

typedef enum {
	/*Configuration for the char size inside the frame */
	UART_5_bit,UART_6_bit,UART_7_bit,UART_8_bit
	,UART_Charsze_RESERVEDbit1,UART_Charsze_RESERVEDbit2,
	UART_Charsze_RESERVEDbit3,UART_9_bit
}UART_CharSize;

typedef enum {
	/*Configuration for the clock polarity TX */
	UART_RisingXCKedgeTX,UART_fallingXCKedgeTX
}UART_CLockPolarity_TX;

typedef enum {
	/*Configuration for the clock polarity RX */
	UART_fallingXCKedgeRX,UART_RisingXCKedgeRX
}UART_CLockPolarity_RX;


/*=====================> Structure and Unions <========================*/
typedef struct {
	/*----------------------------------------------------------------
	[Structure Name]  :  UART_configuration
	[Description]     :  used to select the configuration for UART
						 Like operation mode and clock polarity
						 char size and stop bit
	-----------------------------------------------------------------*/
	unsigned char Operationstate ;/*TX/RX*/
	unsigned char operationMode ; /*Asynch/synch*/
	unsigned char StopBitConfiguration ;
	unsigned char ParityCheck ;
	unsigned char CharSize ;
	unsigned char CLockPolarity_TXorRX ;

}UART_configuration;

/*============================> Macros <===============================*/


/*=====================> Function Declarations <========================*/

void UART_init(UART_configuration *ptr ) ;
void UART_SendData(unsigned short Data ) ;
unsigned short UART_GetData() ;
unsigned char  UART_checkParityError(void) ;
unsigned char  UART_checkDataOverRun(void) ;
unsigned char  UART_checkFrameError(void) ;
void UART_callBack(void (*ptr)(void)) ;


#endif /* UART_H_ */
