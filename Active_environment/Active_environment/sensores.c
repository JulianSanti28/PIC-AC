/*!
\file   sensores.c
\date   2021-10-04
\author Andrés Muñoz <andresdmunoz@unicauca.edu.co> 104618021296
        Paula Peña <ppena@unicauca.edu.co> 104618021314
		Julián Martinez <juliansmartinez@unicauca.edu.co> 104618021321
\brief  Lectura de los sensores utilizados en el simulador.
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
#include "sensores.h"

/*
@sensor_distancia
@brief ajusta el valor de la distancia leido por el sensor del simulador.
@param void
@return valor de la distancia en centimetros convertido en entero.
*/
int sensor_distancia(void) {
    init_ports();
    val_distancia = obtener_distancia();
    if (val_distancia <= 38 && val_distancia > 12)
        val_distancia += 2;
    else if (val_distancia > 38)
        val_distancia += 3;
    else if (val_distancia <= 12)
        val_distancia--;
    return (int) val_distancia;
}
/*
@init_ports
@brief inicia los puertos donde se conectaron los sensores
@param void
@return void
*/
void init_ports() {
    ADCON1bits.PCFG = 0xF; //
    ESC_ECHO = 0;//
    ESC_TRIG = 0;//
    ECHO = 1; //Echo
    TRIG = 0; //Trigger
}
/*
@obtener_distancia
@brief lee el valor hecho por el sensor de distancia en el simulador.
@param void
@return valor de la distancia en centimetros convertido en entero.
*/
unsigned int obtener_distancia(void) {
    unsigned int cm = 0;
    ESC_TRIG = 1;
    __delay_us(10); /*Generación de ondas (Pulsos para la lectura)*/
    ESC_TRIG = 0;
    while (LEC_PULSOECHO == 0) {
    };
    while (LEC_PULSOECHO == 1) {
        cm++;
        __delay_us(58);
    }
    return cm;
}
/*
@sensor_temperatura
@brief Lee el valor hecho por el sensor de temperatura en el simulador.
@param void
@return Valor de la temperatura en grados  casteado a entero.
*/
int sensor_temperatura(void) {
    TRISAbits.RA0 = 1; //Pin_A0 puesto en ALTO. 
    adc_init10Bits(0);
    value_adc = adc_read10Bits(); //  Lectura de valor AD.*/; 
    val_temp = (int) value_adc * 0.4887;
    return val_temp;
}

/*
@sensor_luz
@brief Lee el valor hecho por el sensor de luminocidad en el simulador.
@param void
@return porcentaje de luminocidad del entorno casteado a entero.
*/

int sensor_luz(void) {

    TRISAbits.TRISA1 = 1; //entrada puerto A1 

    adc_init10Bits(1);

    val_intensidad = adc_read10Bits(); //  Lectura de valor AD.*/; 
    val_intensidad = (val_intensidad * 5) / 1024;
    val_luminosidad = (val_intensidad * 100) / 5;

    return val_luminosidad;
}

