/*!
\file   Leds.c
\date   2021-10-04
\author Andrés Muñoz <andresdmunoz@unicauca.edu.co> 104618021296
        Paula Peña <ppena@unicauca.edu.co> 104618021314
        Julián Martinez <juliansmartinez@unicauca.edu.co> 104618021321
\brief  logica para encender leds .
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

#include "Leds.h"
#include "LCD.h"
#include "RTC.h"
#include "USART_Header_File.h"
#include <string.h>

/*
 *@init_leds 
 *@brief Inicializa la configuracion de los leds definidos en leds.h
 *@param void 
 *@return void
 */
void init_leds(void) {

    CFG_LED_POWER_B = OUTPUT;
    CFG_LED_POWER_G = OUTPUT;
    CFG_LED_POWER_R = OUTPUT;
    CFG_LED_POWER_Y = OUTPUT;
}

/*
 *@encender_leds
 *@brief Enciende los leds designados segun el numero de fallos (valor) 0 = green ; 1= yelloww ; 2 o mas = red
 *@param valor Numero de fallos
 *@return void
 */
void encender_leds(int valor) {

    if (valor == TODOS_BIEN) { //TODOS BIEN
        LED_GREEN = ON;
        LED_YELLOW = OFF;
        LED_RED = OFF;
    } else if (valor == UN_VALOR_MAL) {//1 FALLANDO
        LED_GREEN = OFF;
        LED_YELLOW = ON;
        LED_RED = OFF;
    } else if (valor >= UN_VALOR_MAL && valor < 4) { // 2 O MAS FALLANDO
        LED_GREEN = OFF;
        LED_YELLOW = OFF;
        LED_RED = ON;
    } else {
        LED_GREEN = ON;
        LED_YELLOW = ON;
        LED_RED = ON;
    }
}

/*
 *@validar
 *@brief Valida los valores temperatura, distancia, luz segun los indicadores optimos definidos. Si falla muestra el emoticón correspondiente al fallo.
 *@param temp Valor de la temperatura según el sensor de temperatura.
 *@param distancia Lectura de la distancia según el sensor de distancia.
 *@param luz Lectura del porcentaje de luminisidad  según el sensor de luz.
 *@return int Valores fuera de rango, 0 si no existe ningun valor fuera de rango, 1 si existe un valor fuera de rango, 2 si existe dos valores fuera de rango.
 */


int validar(int temp, int distancia, int luz, int mostrar_emoji) {
    int contador = 0;
    // verde valores  normales ; amarillo 1  fallando ; rojo 2 o + fallando
    if (temp < TEMP_BAJA || temp > TEMP_ALTA) { //Mayor a 30 grados y Menor a 17 es un estado no óptimo

        if (temp != temp_ant) {
            char valor_usart[30];
            sprintf(valor_usart, "%d", temp);
            mostrar_estadistica(1, valor_usart);
            temp_ant = temp;
        }

        if (mostrar_emoji == 1) {
            mostrar_emoticon(5);
        }


        contador++;
    }
    if (distancia < DISTANCIA_OPTIMA) {//optimo 65 70 //distancia > 100 ||

        if (distancia != dist_ant) {
            char valor_usart[30];
            sprintf(valor_usart, "%d", distancia);
            mostrar_estadistica(2, valor_usart);
            dist_ant = distancia;
        }

          if (mostrar_emoji == 1) {
            mostrar_emoticon(6);
        }

        contador++;
    }
    if (luz > LUZ_ALTA_OPTIMA || luz < LUZ_BAJA_OPTIMA) {


        if (luz != lum_ant) {
            char valor_usart[30];
            sprintf(valor_usart, "%d", luz);
            mostrar_estadistica(3, valor_usart);
            lum_ant = luz;
        }


          if (mostrar_emoji == 1) {
            mostrar_emoticon(7);
        }


        contador++;
    }

    /*Cuando todos los valores est�n bien*/
    if (contador == 0 && mostrar_emoji == 1) {
        mostrar_emoticon(4);
    }


    return contador;
}

void mostrar_estadistica(int sensor, char *valor_usart) {

    if (sensor == 1) {


        char mensaje_usart[100];
        sprintf(mensaje_usart, "%s Alerta de Temperatura: %s G \r\n", obtener_tiempo_fecha(), valor_usart);
        USART_SendString(mensaje_usart);

    }
    if (sensor == 2) {

        char mensaje_usart[100];
        sprintf(mensaje_usart, "%s Alerta de Distancia: %s Cm \r\n", obtener_tiempo_fecha(), valor_usart);
        USART_SendString(mensaje_usart);

    }
    if (sensor == 3) {

        char mensaje_usart[100];
        sprintf(mensaje_usart, "%s Alerta de Luminosidad: %s Porciento \r\n", obtener_tiempo_fecha(), valor_usart);
        USART_SendString(mensaje_usart);

    }


}