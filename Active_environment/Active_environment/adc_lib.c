/*!
\file   adc_lib.c
\date   2021-10-04
\author Andrés Muñoz <andresdmunoz@unicauca.edu.co> 104618021296
        Paula Peña <ppena@unicauca.edu.co> 104618021314
		Julián Martinez <juliansmartinez@unicauca.edu.co> 104618021321
\brief  Inicialización y configuración del conversor analógico digital..
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
#include "adc_lib.h"

/*
*@adc_config
*@brief Configura el ADC según la documentación.
*@param canal Canal que se inicializa como entrada analógica. Sólo se usa el acanal 1 y el canal 0.
*@return void
*/
void adc_config(int canal){
    ENTRADA_PUERTO = ENTRADA_ANALOGICA; 
    VOLTAJE_REFERENCIA = CERO_VOLTIOS_CINCO_VOLTIOS;
    if(canal == 0) { CANAL_A_TRABAJAR = CANAL_0; } else{ CANAL_A_TRABAJAR = CANAL_1;};  
    TIEMPO_ADQUISICION = 0b010; 
    TIEMPO_CONVERSION = 0b001; 
    MODULO_AD = HABILITADO; 
}

/*
*@adc_init10Bits
*@brief Envía información del canal para inicializar los valores del ADC.
*@param canal Canal que se envía a la función de configuración.
*@return void
*/
void adc_init10Bits(int canal){
    
    adc_config(canal);  
    JUSTIFICACION = DERECHA; 
} 

/*
*@adc_config
*@brief Retorna el valor que se lee del canal analógico.
*@return int Valor convertido después de la lectura.
*/
unsigned int adc_read10Bits() {
    unsigned int value_adc = 0;
    HACER_CONVERSION = INICIAR; 
    while (HACER_CONVERSION); 
    value_adc = RESULTADO; 
    value_adc = (value_adc << 8) + ADRESL;
    return value_adc;  
}
