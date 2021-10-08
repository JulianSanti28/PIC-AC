

/*!
\file   USART_Header_File.h
\date   2021-10-04
\author Andrés Muñoz <andresdmunoz@unicauca.edu.co> 104618021296
        Paula Peña <ppena@unicauca.edu.co> 104618021314
		Julián Martinez <juliansmartinez@unicauca.edu.co> 104618021321
\brief  Transmisor receptor as�ncrono
\par Copyright
Information contained herein is proprietary to and constitutes valuable
confidential trade secrets of unicauca, and
is subject to restrictions on use and disclosure.
\par
Copyright (c) unicauca 2021. All rights reserved.
\par
The copyright notices above do not evidence any actual or
intended publication of this material.
 ******************************************************************************
 */


// This is a guard condition so that contents of this file are not included
// more than once.  

#ifndef USART_HEADER_FILE_H
#define	USART_HEADER_FILE_H

#include <pic18f4550.h>
#include <xc.h>
#include <string.h>

void USART_Init(long);
void USART_TxChar(char);
void USART_SendString(const char *);
char USART_RxChar();

#define F_CPU 8000000/64
//#define Baud_value(baud_rate) (((float)(F_CPU)/(float)baud_rate)-1)
#define Baud_value (((float)(F_CPU)/(float)baud_rate)-1)

#endif	/* USART_HEADER_FILE_H */

