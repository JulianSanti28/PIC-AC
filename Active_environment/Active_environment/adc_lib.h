/*!
\file   adc_lib.h
\date   2021-10-04
\author Andrés Muñoz <andresdmunoz@unicauca.edu.co> 104618021296
        Paula Peña <ppena@unicauca.edu.co> 104618021314
		Julián Martinez <juliansmartinez@unicauca.edu.co> 104618021321
\brief  Archivo de cabacera del archivo adc_lib.c
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

/*Definiciones para una mejor comprensión del código*/
#define HACER_CONVERSION ADCON0bits.GO_DONE
#define RESULTADO ADRESH
#define CANAL_0 0b0000
#define CANAL_1 0b0001
#define CANAL_A_TRABAJAR ADCON0bits.CHS
#define ENTRADA_PUERTO ADCON1bits.PCFG
#define ENTRADA_ANALOGICA 0b1101
#define VOLTAJE_REFERENCIA ADCON1bits.VCFG
#define CERO_VOLTIOS_CINCO_VOLTIOS 0b00 
#define TIEMPO_ADQUISICION ADCON2bits.ACQT
#define TIEMPO_CONVERSION ADCON2bits.ADCS
#define MODULO_AD ADCON0bits.ADON
#define HABILITADO 1
#define DESHABILITADO 0
#define JUSTIFICACION ADCON2bits.ADFM
#define DERECHA 1
#define IZQUIERDA 0
#define INICIAR 1

#ifndef ADC_LIB_H
#define	ADC_LIB_H

#ifdef	__cplusplus
extern "C" {
#endif
    /*Inicialización de las funciones utilizadas*/
    void adc_init10Bits(int canal);  
    unsigned int adc_read10Bits();  
    void adc_config(); 
    
#ifdef	__cplusplus
}
#endif

#endif	/* ADC_LIB_H */

