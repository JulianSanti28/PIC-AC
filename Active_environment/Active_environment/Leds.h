/*!
\file   Leds.h
\date   2021-10-04
\author Andrés Muñoz <andresdmunoz@unicauca.edu.co> 104618021296
        Paula Peña <ppena@unicauca.edu.co> 104618021314
		Julián Martinez <juliansmartinez@unicauca.edu.co> 104618021321
\brief  Configuración leds y sus elementos.
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

#ifndef LEDS_H
#define	LEDS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include "fuses.h"
#include <pic18f4550.h>

#define ON 1
#define OFF 0

#define INPUT 1
#define OUTPUT 0

#define LED_BLUE LATB6
#define LED_GREEN LATB5
#define LED_YELLOW LATB4
#define LED_RED LATB3

#define CFG_LED_POWER_B TRISB6
#define CFG_LED_POWER_G TRISB5
#define CFG_LED_POWER_Y TRISB4
#define CFG_LED_POWER_R TRISB3
#define TEMP_ALTA 30
#define TEMP_BAJA 17
#define DISTANCIA_OPTIMA 40
#define LUZ_ALTA_OPTIMA 60
#define LUZ_BAJA_OPTIMA 10
#define TODOS_BIEN 0
#define UN_VALOR_MAL 1
    


void delay_ms(unsigned int delay);
int validar(int temp,int distancia,int luz);
void encender_leds(int valor);
void init_leds(void); 


#ifdef	__cplusplus
}
#endif

#endif	/* LEDS_H */

