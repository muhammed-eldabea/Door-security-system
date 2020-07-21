/*********************************************************************
 * 		[file name] : uart.c
 *  	[Created on]: Jul 7, 2020
 *      [Author]: Muhammed Eldabea Hashem
 *      [Description] : Function definition and all API that
 *      			  Needed for UART
 *
 *********************************************************************/





/* =================================================================== *
      ------------------------>includes<----------------------------
 * =================================================================== */

#include "uart.h"


/* =================================================================== *
       -------------------->Global Variable<--------------------------
 * =================================================================== */
#define NULL_ptr (void*)0

volatile void (*G_ptrFunc)(void) = NULL_ptr ;


/* ==================================================================== *
      	  	  	 ----------------->ISR<--------------------
 * ==================================================================== */

ISR(USART_RXC_vect)
{
	if(G_ptrFunc !=NULL_ptr)
	{
		(*G_ptrFunc)() ;
	}
}


ISR(USART_TXC_vect)
{
	if(G_ptrFunc !=NULL_ptr)
		{
			(*G_ptrFunc)() ;
		}
}

ISR(USART_UDRE_vect)
{
	if(G_ptrFunc !=NULL_ptr)
		{
			(*G_ptrFunc)() ;
		}
}



/* ==================================================================== *
      ----------------->Functions Definitions<--------------------
 * ==================================================================== */

void UART_init(UART_configuration *ptr )
{

	unsigned short UBRR_value = 0 ;

	if(ptr->operationMode ==Uart_AsynchrouncousOperationModeDoubleSpeedMode){
		UCSRA |=(1<<1) ; /*set the U2X bit */
	}


	switch (ptr->Operationstate) {
	/*configuration for RX/TX mode of UART*/
	case (UART_txmode) :
												UCSRB |=(1<<3) ; /*enable TX*/
	break ;
	case (UART_RXmode) :
												UCSRB |=(1<<4) ; /*enable RX*/
	break ;
	case (UART_TXRXmode) :
												UCSRB |=(1<<3) ; /*enable TX*/
	UCSRB |=(1<<4) ; /*enable RX*/
	break ;
	}


#if Uart_Enable_multiProcessor_Communication_mode ==1
	UCSRA |=(1<<0) ; /*enable multi proccecor comuniction */
#endif


#if Uart_RX_interrupt_enable ==1
	SREG |=(1<<7) ;
	UCSRB |=(1<<7) ; /*RX interrupt*/
#endif

#if Uart_TX_interrupt_enable ==1
	SREG |=(1<<7) ;
	UCSRB |=(1<<6) ; /*RX interrupt*/
#endif

#if Uart_DataRegisterEmpty_interrupt_enable ==1
	SREG |=(1<<7) ;
	UCSRB |=(1<<5) ; /*RX interrupt*/
#endif

	UCSRB = (UCSRB & 0xFB) | (ptr->CharSize & 0x04) ; /*UCZ2*/
	UCSRC = (UCSRC & 0xBF) | ((ptr->operationMode & 0x01)<<6) ; /*mode select*/
	UCSRC = (UCSRC & 0xCF) | ((ptr->operationMode & 0x03)<<4) ; /*parity mode */
	UCSRC = (UCSRC & 0xF7) | ((ptr->StopBitConfiguration & 0x01)<<3) ;/*stop bit */
	UCSRC = (UCSRC & 0xF9) | ((ptr->operationMode & 0x03)<<1) ; /*CZ0/CZ1*/
	UCSRC = (UCSRC & 0xFE) | (ptr->operationMode & 0x01) ; /*polarity*/


	switch(ptr->operationMode) {
	/*calculate the UBRR value*/
	case (Uart_AsynchrouncousOperationMode) :
							UBRR_value = ((F_CPU/(16*UART_BAUDRATE))-1) ;
	break ;
	case (Uart_AsynchrouncousOperationModeDoubleSpeedMode) :
								UBRR_value = ((F_CPU/(8*UART_BAUDRATE))-1) ;
	break ;
	case (Uart_SynchrounousoperationMode) :
								UBRR_value = ((F_CPU/(2*UART_BAUDRATE))-1) ;
	break ;

	}



	UBRRH = UBRR_value>>8 ;
	UBRRL = (unsigned char )UBRR_value ;


}






void UART_SendData(unsigned short Data )

{
	UDR = Data ;
	while((!(UCSRA &(1<<6)))){}
	/*clear the TX bit */
	UCSRA |=(1<<6) ;



}

unsigned short UART_GetData()
{
	/*used to get the data by
	 * using  UART module*/


	/*wait until the bit is set */
	while((!(UCSRA &(1<<7)))){}
	/*clear the bit by sitting it */
	UCSRA |=(1<<7) ;
	return UDR ;

}


unsigned char  UART_checkParityError(void)
{
	/*return one when the parity calculation error*/
	return (UCSRA & (1<<2) ) ;
}


unsigned char  UART_checkDataOverRun(void)
{
	/*return one when the over-run occur*/
	return (UCSRA & (1<<3) ) ;
}


unsigned char  UART_checkFrameError(void)
{
	/*return one if the frame error happen */
	return (UCSRA & (1<<4) ) ;
}

void UART_callBack(void (*ptr)(void))
{
	/*Work as a call back function to USART
	 * make a function called when ISR of USART
	 * happen
	 * */

	G_ptrFunc = ptr ;
}
