
/*!
\file   Principal.c
\date   2021-10-04
\author Andrés Muñoz <andresdmunoz@unicauca.edu.co> 104618021296
        Paula Peña <ppena@unicauca.edu.co> 104618021314
        Julián Martinez <juliansmartinez@unicauca.edu.co> 104618021321
\brief  Lanzamiento proyecto .

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
#include "fuses.h"
#include "LCD.h"
#include "sensores.h"
#include "Leds.h"
#include <stdint.h>  
#include "USART_Header_File.h"
#include "RTC.h"

#define OSCILADOR_INTERNO OSCCONbits.IRCF
#define OCHO_MHZ 0b111
#define OSCILADOR_DEL_SISTEMA OSCCONbits.SCS
#define PULL_UP RBPU 
#define ACTIVADO 0
#define OCHO_mHz 0x72

#define SELECTOR PORTAbits.RA4 
#define clt_selector TRISBbits.RB4
/*Declaración de funciones a usar*/
int estado; 

void imprimir(int dist, int temp, int luz);
void iniciar_emoticones();
void iniciar_pic();
void principal(); 

void main(void) { //Método main
    USART_Init(9600); //Inicializar el USART
    iniciar_pic(); //Inicializa valores del PIC
    inicializar_lcd(); //Inicializa configuración del LCD
    init_leds(); //Inicializa los pines para el manejo d eleds
    iniciar_emoticones(); //Carga los emoticones a usar
    ADCON1 = 0b1101;
    estado = 1; 
    while(1){
        principal(); 
    }
}//Fin método main
/*
 *@bref Inicializa los osciladores y el pull-up con los valores que requerimos para la implementación.
 *@return void
 */
void principal() {

    int s_dist = 0, s_temp = 0, s_luz = 0; //Variables para carga de información
    s_dist = sensor_distancia(); //Almacenando el valor de distancia retornado por la función
    s_temp = sensor_temperatura(); //Almacenando el valor de temperatura retornado por la función
    s_luz = sensor_luz(); //Almacenando el valor de luz retornado por la función
    while(SELECTOR == 1) {
        estado++;
        __delay_ms(200); 
    }
    if(estado > 2){
            estado = 1; 
    }
    if (estado == 1){
          imprimir(s_dist, s_temp, s_luz);  
    }
    encender_leds(validar(s_temp, s_dist, s_luz)); //Enciende o no los leds dependiendo del estado de cada sensor
    /*/else if(estado == 2){
          configurarHora();   
    }*/
}

void iniciar_pic() {
    OSCILADOR_INTERNO = OCHO_MHZ;
    OSCILADOR_DEL_SISTEMA = 0b10; //?
    OSCCON = OCHO_mHz;
    PULL_UP = ACTIVADO;
    init_rtc(); 
    pines_ConfigurarHora();
    clt_selector = 1;  //se determina el pin RA4 como entrada digital 
}

/*
 *@bref Inicializa los arreglos con la información de los emoticones, además los guarda previamente para luego ser consultados.
 *@return void
 */
void iniciar_emoticones() {


    unsigned char temperatura[8] = {//Emoticon de temperatura
        0b00100,
        0b10101,
        0b01110,
        0b11111,
        0b01110,
        0b10101,
        0b00100,
        0b00000,
    };

    unsigned char distancia[8] = {//Emoticon de distancia
        0b00000,
        0b00000,
        0b00100,
        0b00010,
        0b11111,
        0b00010,
        0b00100,
        0b00000,
    };

    unsigned char luz[8] = {//Emoticon de luminosidad
        0b01010,
        0b01010,
        0b01010,
        0b11111,
        0b10001,
        0b01110,
        0b00100,
        0b00100,
    };

    unsigned char todo_bien[8] = {//Emoticos de un estado óptimo en todos los sensores
        0b00000,
        0b01010,
        0b01010,
        0b00000,
        0b11111,
        0b01110,
        0b00100,
        0b00000,
    };

    //Agregando los emoticones a una posición distinta del lcd
    LCD_Custom_Char(4, todo_bien);
    LCD_Custom_Char(5, temperatura);
    LCD_Custom_Char(6, distancia);
    LCD_Custom_Char(7, luz);


}

/*
 *@bref Imprime un título para identificar cada uno de los valores (distancia, luz, temperatura), además muestra los valores en el LCD
 *@param dist Valor de la distancia capturado en cada iteración del ciclo infinito.
 *@param temp Valor de la temperatura capturado en cada iteración del ciclo infinito.
 *@param luz Valor de la luminosidad capturado en cada iteración del ciclo infinito.
 *@return void
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






















