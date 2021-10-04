/*!
\file   LCD.h
\date   2021-10-04
\author Andrés Muñoz <andresdmunoz@unicauca.edu.co> 104618021296
        Paula Peña <ppena@unicauca.edu.co> 104618021314
		Julián Martinez <juliansmartinez@unicauca.edu.co> 104618021321
\brief  Archivo de cabecera de LCD.c.

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

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h> //incluir archivos de procesador: cada archivo de procesador está protegido.  
#include <pic18f4550.h> //Incluir la librería del PIC18F4550
#include "fuses.h" //Incluye la configuración general del PIC

    /***********************Definición de puertos*******************************/

#define RS LATD0                    /*El PIN 0 de PORTB se asigna para el pin de selección de registro de la pantalla LCD*/
#define EN LATD1                    /*El PIN 1 de PORTB se asigna para habilitar el Pin de la pantalla LCD*/
#define ldata LATD                  /*PORTB (PB4-PB7) está asignado para salida de datos LCD*/ 
#define LCD_Port TRISD   
#define CMD_CLEAR_LCD 0x01
    
void inicializar_lcd();             /*Inicializa el LCD*/
void LCD_Command(unsigned char );   /*Enviar comando a la pantalla LCD*/
void LCD_Char(unsigned char x);     /*Enviar datos a la pantalla LCD*/
void LCD_String(const char * );     /*Mostrar cadena de datos en la pantalla LCD*/
void LCD_String_xy(char, char , const char *);
void LCD_Clear();/*Limpiar pantalla del LCD*/
void LCD_Custom_Char(unsigned char loc, unsigned char *msg); /*Función para escribir en el LCD */
void mostrar_emoticon(char i);/*Función para mostrar un emoticón*/



#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

