/*!
\file   funcionalidades.c
\date   2021-10-04
\author Andrés Muñoz <andresdmunoz@unicauca.edu.co> 104618021296
        Paula Peña <ppena@unicauca.edu.co> 104618021314
		Julián Martinez <juliansmartinez@unicauca.edu.co> 104618021321
\brief  funcionalidades del proyecto .
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
#include <xc.h>
#include <stdio.h>
#include <pic18f4550.h>

/*
@iniciar_pic 
@brief inicializa el pic 18f4550
@param void
@return void
*/
//Hola mundo 2 
//hola tu 
void iniciar_pic() {
    OSCILADOR_INTERNO = OCHO_MHZ;
    OSCILADOR_DEL_SISTEMA = 0b10; //?
    OSCCON = OCHO_mHz;
    PULL_UP = ACTIVADO;
}

/*
@iniciar_emoticones 
@brief Define y carga en el programa los emoticones a usar para temperatura, distancia, luz.
@param void
@return void
*/

void iniciar_emoticones() {

    unsigned char temperatura[8] = {
        0b00100,
        0b10101,
        0b01110,
        0b11111,
        0b01110,
        0b10101,
        0b00100,
        0b00000,
    };

    /*Emoticon a mostrar*/
    unsigned char distancia[8] = {
        0b00000,
        0b00000,
        0b00100,
        0b00010,
        0b11111,
        0b00010,
        0b00100,
        0b00000,
    };

    unsigned char luz[8] = {
        0b01010,
        0b01010,
        0b01010,
        0b11111,
        0b10001,
        0b01110,
        0b00100,
        0b00100,
    };

    unsigned char todo_bien[8] = {
        0b00000,
        0b01010,
        0b01010,
        0b00000,
        0b11111,
        0b01110,
        0b00100,
        0b00000,
    };


    LCD_Custom_Char(4, todo_bien);
    LCD_Custom_Char(5, temperatura);
    LCD_Custom_Char(6, distancia);
    LCD_Custom_Char(7, luz);


}

/*
@imprimir 
@brief imprime los valores de la lectura hecha por los sensores en el lcd
@param dist lectura de la distancia según el sensor de distancia
@param temp lectura de la temperatura según el sensor de temperatura
@param luz lectura del porcentaje de luminosidad según el sensor de luz
@return void
*/
void imprimir(int dist, int temp, int luz) {

    // imprimir_emoticon();
    LCD_String_xy(0, 0, "D:T:L:");
    /*Distancia*/
    char aux_dist[16] = "";
    sprintf(aux_dist, "%dcm", dist);
    /*Temp*/
    char aux_temp[16] = "";
    sprintf(aux_temp, "%dG", temp);
    /*Luz*/
    char aux_luz[16] = "";
    sprintf(aux_luz, "%dP", luz);
    //__delay_ms(100);
    LCD_Command(0xC0);
    LCD_String_xy(3, 0, aux_dist);
    LCD_String_xy(3, 6, aux_temp);
    LCD_String_xy(3, 11, aux_luz);
    __delay_ms(900);
    LCD_Clear();
}

