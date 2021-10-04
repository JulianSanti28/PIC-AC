/*!
\file   LCD.c
\date   2021-10-04
\author Andrés Muñoz <andresdmunoz@unicauca.edu.co> 104618021296
        Paula Peña <ppena@unicauca.edu.co> 104618021314
		Julián Martinez <juliansmartinez@unicauca.edu.co> 104618021321
\brief  Funcionalidades LCD.

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


#include "LCD.h"

/*
*@bref Inicializa el LCD con los valores necesarios para el proyecto
*@return void
*/
void inicializar_lcd() {
    LCD_Port = 0; /*PORT as Output Port*/
    __delay_ms(15); /*15ms,16x2 LCD Power on delay*/
    LCD_Command(0x02); /*send for initialization of LCD*/
    /*for nibble (4-bit) mode */
    LCD_Command(0x28); /*use 2 line and 
                                     initialize 5*8 matrix in (4-bit mode)*/
    LCD_Command(CMD_CLEAR_LCD); /*clear display screen*/
    LCD_Command(0x0c); /*display on cursor off*/
    LCD_Command(0x06); /*increment cursor (shift cursor to right)*/
}

void LCD_Command(unsigned char cmd) {
    ldata = (ldata & 0x0f) | (0xF0 & cmd); /*Send higher nibble of command first to PORT*/
    RS = 0; /*Command Register is selected i.e.RS=0*/
    EN = 1; /*High-to-low pulse on Enable pin to latch data*/
    NOP();
    EN = 0;
    __delay_ms(1);
    ldata = (ldata & 0x0f) | (cmd << 4); /*Send lower nibble of command to PORT */
    EN = 1;
    NOP();
    EN = 0;
    __delay_ms(3);
}

/*
*@bref Escribe un dato de tipo char que ingresa como parámetro.
*@param dat Dato que será escrito en el LCD 
*@return void
*/
void LCD_Char(unsigned char dat) {
    
    ldata = (ldata & 0x0f) | (0xF0 & dat); /*Envía un nibble mayor de datos primero a PORT*/
    RS = 1; /*El registro de datos está seleccionado*/
    EN = 1; /*Pulso de alto a bajo en Activar pin para bloquear datos*/
    NOP();
    EN = 0;
    __delay_ms(1);
    ldata = (ldata & 0x0f) | (dat << 4); /*Envía una pequeña cantidad de datos a PORT*/
    EN = 1; /*Pulso de alto a bajo en Activar pin para bloquear datos*/
    NOP();
    EN = 0;
    __delay_ms(3);


}

/*
*@bref Escribe un mensaje de tipo dirección de memoria char que ingresa como parámetro.
*@param msg Mensaje que será escrito en el LCD 
*@return void
*/
void LCD_String(const char *msg) {
    while ((*msg) != 0) {
        LCD_Char(*msg);
        msg++;
    }

}

/*
*@bref Escribe un mensaje de tipo char que ingresa como parámetro en una posición específica del LCD 16 x 2.
*@param row Fila en la que será escrito el mensaje en el LCD
*@param pos Posición dentro de la fila en donde será escrito el mensaje en el LCD 
*@param msg Mensaje que será escrito en el LCD 
*@return void
*/
void LCD_String_xy(char row, char pos, const char *msg) {
    char location = 0;
    if (row <= 1) {
        location = (0x80) | ((pos) & 0x0f); /*Imprimir mensaje en la 1ra fila y ubicación deseada*/
        LCD_Command(location);
    } else {
        location = (0xc0) | ((pos) & 0x0f); /*Imprima el mensaje en la segunda fila y la ubicación deseada*/
        LCD_Command(location);
    }

    LCD_String(msg);

}

/*
*@bref Permite ubicarse en una posición específica del LCD 16 x 2.
*@param row Fila en la se requiere la ubicación.
*@param pos Posición dentro de la fila en donde se requiere la ubicación
*@return void
*/
void LCD_xy(char row, char pos) {
    char location = 0;
    if (row <= 1) {
        location = (0x80) | ((pos) & 0x0f); /*Imprimir mensaje en la 1ra fila y ubicación deseada*/
        LCD_Command(location);
    } else {
        location = (0xC0) | ((pos) & 0x0f); /*Imprima el mensaje en la segunda fila y la ubicación deseada*/
        LCD_Command(location);
    }
}

/*
*@bref Permite limpiar la información del LCD 16 x 2.
*@return void
*/
void LCD_Clear() {
    LCD_Command(CMD_CLEAR_LCD); /*Limpia la pantalla del display*/
}

/*
*@bref Permite mostrar un emoticon guardado previamente en el LCD 16x2.
*@param i ubicación del emoticón guardado previamente.
*@return void
*/
void mostrar_emoticon(char i) {

    LCD_Command(0x80 | (i * 2)); /*Accede directamente el emoticón con la ubicación dada y la ubica en la primera fila del LCD*/
    LCD_Char(i);/*Envía el dato para ser mostrado en el LCD*/

}

/*
*@bref Permite almacenar un emoticon descrito en un arreglo.
*@param loc Posición dentro de la primera fila del LCD.
*@return void
*/
void LCD_Custom_Char(unsigned char loc, unsigned char *msg) {

    unsigned char i;
    if (loc < 8) {
        LCD_Command(0x40 + (loc * 8)); /*El comando 0x40 y en adelante obliga al dispositivo a señalar la dirección CGRAM*/
        for (i = 0; i < 8; i++) /*Escriba 8 bytes para la generación de 1 carácter (emoticon)*/
            LCD_Char(msg[i]);
    }

}


