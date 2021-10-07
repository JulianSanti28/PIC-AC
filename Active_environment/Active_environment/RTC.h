/* 
 * File:   RTC.h
 * Author: ASUS
 *
 * Created on 6 de octubre de 2021, 9:30
 */

#ifndef RTC_H
#define	RTC_H


#ifdef	__cplusplus
extern "C" {
#endif
#include <xc.h>
#include <stdio.h>
#include <pic18f4550.h>
#include <string.h>
#include <stdint.h>
#include "I2C_Master_File.h"
#include "fuses.h"
#include "LCD.h"

#define Pulsador_1  (PORTAbits.RA2)        // Pulsador 1 será asignado al pin RB0.
#define Pulsador_2  (PORTAbits.RA3)        // Pulsador 2 será asignado al pin RB1.

#define _XTAL_FREQ 8000000
#define BAUD 9600

#define device_id_write 0xD0 // direccion de memoria sobre la que se escribe
#define device_id_read 0xD1 // direccion de memoria sobre la que se lee 

int sec, min, hour;
int Day, Date, Month, Year;

char date[60];
char time[60];

unsigned char var[120];

uint8_t hours;                             // Variable de 8 bits para las horas.
uint8_t minutes;                           // Variable de 8 bits para los minutos.
uint8_t seconds;                           // Variable de 8 bits para los segundos.
uint8_t year;                              // Variable de 8 bits para los año.
uint8_t month;                             // Variable de 8 bits para el mes.
uint8_t day;                               // Variable de 8 bits para el dia.
uint8_t i;                                 // Variable de 8 bits.

void init_rtc(); 
void pines_ConfigurarHora(void);  

void RTC_Clock_Write(char sec, char min, char hour, char AM_PM); 
void RTC_Calendar_Write(char day, char date, char month, char year); 
char * obtener_tiempo_fecha();
void RTC_Read_Clock(char read_clock_address);
void RTC_Read_Calendar(char read_calendar_address);
void RTC_obtener_hora();
void RTC_obtener_fecha();


void Reloj_Calendario (void);                //Función de visualización de HORA Y FECHA.
void configurarHora (void);                 // Función rutina de configuración horaria
uint8_t Establecer_Hora_Fecha(uint8_t x, uint8_t y, uint8_t parametro); // Función para establecer Hora y Fecha.
uint8_t BCD_a_Decimal (uint8_t numero); //Funcion que retornna un numero decimal  
uint8_t Decimal_a_BCD (uint8_t numero); //funcion que retorna un BCD
void Parpadeo (void);                         // Función Parpadeo().
__bit Anti_rebote (void);                    // Función antirebote Pulsador_1 (RB0)


#ifdef	__cplusplus
}
#endif

#endif	/* RTC_H */

