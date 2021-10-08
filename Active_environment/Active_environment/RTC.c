/*!
\file   RTC.c
\date   2021-10-04
\author Andrés Muñoz <andresdmunoz@unicauca.edu.co> 104618021296
        Paula Peña <ppena@unicauca.edu.co> 104618021314
		Julián Martinez <juliansmartinez@unicauca.edu.co> 104618021321
\brief  rtc del proyecto.
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
/*
 * PIC18F4550 interfacing with RTC DS1307
 * http://www.electronicwings.com
 */

#include "RTC.h"

/*
*@RTC_Clock_Write
*@brief escribe sobre el LCD la hora en formato HH:MM:SS
*@param sec segundos 
*@param min minutos 
*@param hour horas 
*@param AM_PM antes del meridiano o despues del meridiano
*@return void
*/
void RTC_Clock_Write(char sec, char min, char hour, char AM_PM)
/* function for clock */ {
    hour = (hour | AM_PM); /* whether it is AM or PM */
    I2C_Start(device_id_write); /* start I2C comm. with device slave address*/
    I2C_Write(0); /* write 0 location for sec value */
    I2C_Write(sec); /* write second value on 00 location */
    I2C_Write(min); /* write min value on 01 location */
    I2C_Write(hour); /* write hour value on 02 location */
    I2C_Stop(); /* stop I2C communication */
}

/*
*@RTC_Calendar_Write
*@brief escribe sobre el LCD la fecha en formato DD:MM:YYYY
*@param day dia 
*@param date cadena de texto "date" 
*@param month mes 
*@param year año
*@return void
*/
void RTC_Calendar_Write(char day, char date, char month, char year) {
    I2C_Start(device_id_write); /* iniciar la comunicación I2C. con dirección slave del dispositivo */
    I2C_Write(3); /* escribe el valor del dia en la posicion 3  */
    I2C_Write(day); /* escribe el valor del dia en la posicion 3 */
    I2C_Write(date); /* escribe el valor de date  en la posicion 4  */
    I2C_Write(month); /* escribe el valor del mes  en la posicion 5  */
    I2C_Write(year); /* escribe el valor de año en la posicion 6  */
    I2C_Stop();

}

/*
*@RTC_Calendar_Write
*@brief 
*@param day dia 
*@param date cadena de texto "date" 
*@param month mes 
*@param year año
*@return void
*/
void RTC_Read_Clock(char read_clock_address) {
    I2C_Start(device_id_write);
    I2C_Write(read_clock_address); /* direccion donde la hora necesita ser leida */
    I2C_Repeated_Start(device_id_read);
    sec = I2C_Read(0); /* leer data y enviar ack para seguir leyendo */
    min = I2C_Read(0); /*leer data y enviar ack para seguir leyendo*/
    hour = I2C_Read(1); /*leer data y enviar nack para indicar que pare de leer */
    I2C_Stop();
}
/*
*@RTC_Read_Calendar
*@brief escribe sobre el LCD la fecha en formato DD:MM:YYYY
*@param day dia 
*@param date cadena de texto "date" 
*@param month mes 
*@param year año
*@return void
*/
void RTC_Read_Calendar(char read_calendar_address) {
    I2C_Start(device_id_write);
    I2C_Write(read_calendar_address); /* direccion donde la hora necesita ser leida*/
    I2C_Repeated_Start(device_id_read);
    Day = I2C_Read(0); /*leer data y enviar ack para seguir leyendo*/
    Date = I2C_Read(0); /*leer data y enviar ack para seguir leyendo*/
    Month = I2C_Read(0); /*leer data y enviar ack para seguir leyendo*/
    Year = I2C_Read(1); /*leer data y enviar nack para indicar que pare de leer*/
    I2C_Stop();
}

/*
*@RTC_obtener_hora
*@brief escribe sobre el LCD la fecha en formato DD:MM:YYYY con los datos de la funcion read_clock
*@return void
*/
void RTC_obtener_hora() {
    char Clock_type = 0x06;
    char AM_PM = 0x05;
    RTC_Read_Clock(0); /*da segundos, minutos y hora */
    I2C_Stop();
    if (hour & (1 << Clock_type)) { /* check si el reloj es 12h o 24h  */
        if (hour & (1 << AM_PM)) { /* check AM o PM */
            hour = hour & (0x1f);
            sprintf(time, "Time: %x:%x:%x PM", hour, min, sec); /*%x for reading BCD format from RTC DS1307*/
        } else {
            sprintf(time, "Time: %x:%x:%x AM", hour, min, sec);
        }
    } else {
        hour = hour & (0x3f);
        sprintf(time, "Time: %x:%x:%x ", hour, min, sec);
    }
}
/*
*@RTC_obtener_fecha
*@brief lee la fecha de la funcion read_calendar y la escribe en el LCD 
*@return void 
*/
void RTC_obtener_fecha() {
    RTC_Read_Calendar(3); /*gives day, date, month, year*/
    sprintf(date, "Date: %x/%x/%x ", Date, Month, Year);
}

/*
*@obtener_tiempo_fecha
*@brief obtiene fecha y hora en un apuntador
*@return char -> fecha y hora
*/
char * obtener_tiempo_fecha() {
    I2C_Init();
    RTC_obtener_hora();
    RTC_obtener_fecha();
    return strcat(date, time);
}
/*
*@BCD_a_Decimal
*@brief Funcion que convierte un numero BCD a decimal
*@return int8
*/
uint8_t BCD_a_Decimal(uint8_t numero) .
{
    return ((numero >> 4) * 10 + (numero & 0x0F)); //  la variable "numero" desplazado 4 posiciones a la izquierda, multiplicado por 10 m�s "numero" &&  1111.
}

/*
*@Decimal_a_BCD
*@brief Funcion que convierte un numero decimal a BCD  
*@return int8
*/
uint8_t Decimal_a_BCD(uint8_t numero) // Funci�n que convierte un n�mero decimal a BCD. 
{
    return (((numero / 10) << 4) + (numero % 10)); // Retornamos la decena de la variable "numero" desplazado 4 bits a la derecha y las unidades de la variable "numero" en el nibble menos significativo
}

__bit Anti_rebote(void) // Funci�n antirebote Pulsador_1 (RB2).
{
    uint8_t contador = 0; // Variable tipo entero de 8 bits.
    for (uint8_t i = 0; i < 5; i++) // Bucle for para generar como m�ximo 50ms de retardo.
    {
        if (Pulsador_1 == 0) // Si Pulsador_1 fue presionado.
            contador++; // Incrementamos en una unidad la variable "contador".
        __delay_ms(10); // Retardo de 10 ms.
    }
    if (contador > 2) // Si "contador" es mayor a 2.  
    {
        return 1; // Retornamos 1.
    }
    else // De lo contrario.
    {
        return 0; // Retornamos 0.
    }
}

void Parpadeo(void) // Funci�n Parpadeo().
{
    uint8_t j = 0; // Variable entera de 8 bits.
    while (j < 100 && Pulsador_1 && Pulsador_2)// Mientras j sea menor que 100 y Pulsador_1 y Pulsador_2 sean igual a 1.
    {
        j++; // Incrementamos el valor de j en una unidad.
        __delay_ms(5); // 5 milisegundos.
    }
}

uint8_t Establecer_Hora_Fecha(uint8_t x, uint8_t y, uint8_t parametro) // Funci�n para establecer Hora y Fecha.
{
    while (Anti_rebote()); // Mientras la  funci�n Anti_rebote() devuelva un 1.
    while (1) // Bucle infinito.
    {
        while (!Pulsador_2) // Mientras Pulsador_2 este presionado. pin RB2.  
        {
            parametro++; // Incrementamos en una unidad el valor de la variable "parametro".
            if (i == 0 && parametro > 23) // Si i=0 y "parametro" es mayor a 23 (horas).
            {
                parametro = 0; // parametro = 0.
            }
            if (i == 1 && parametro > 59) // Si i=1 y "parametro" es mayor a 59 (minutos).
            {
                parametro = 0; // parametro = 0.
            }
            if (i == 2 && parametro > 31) // Si i=2 y "parametro" es mayor a 31 (dias).
            {
                parametro = 1; // parametro = 1.
            }
            if (i == 3 && parametro > 12) // Si i=3 y parametro es mayor a 12 (meses).
            {
                parametro = 1; // parametro = 1.
            }
            if (i == 4 && parametro > 99) // Si i=4 y "parametro" es mayor a 99 (a�o).
            {
                parametro = 0; // parametro = 0.
            }
            LCD_xy(x, y); // Cursos de la pantalla LCD en columna "x", fila "y".
            LCD_Char(parametro / 10 + '0'); // Imprimimos en la pantalla LCD las decenas de la variable "parametro". 
            LCD_Char(parametro % 10 + '0'); // Imprimimos en la pantala LCD las unidades de la variable "parametro".
            __delay_ms(300); // Retardo de 200 ms.
        }

        LCD_xy(x, y); // Cursos de la pantalla LCD en columna "x", fila "y".                    
        LCD_Char("  "); // Inprimimos en la pantalla LCD 2 espacios vacios.
        LCD_xy(x, y+1); // Cursos de la pantalla LCD en columna "x", fila "y".                    
        LCD_Char("  "); // Inprimimos en la pantalla LCD 2 espacios vacios.
        Parpadeo(); // Llamamos a la funci�n Parpadeo().
        
        LCD_xy(x, y); // Cursos de la pantalla LCD en columna "x", fila "y".
        LCD_Char(parametro / 10 + '0'); // Imprimimos en la pantalla LCD las decenas de la variable "parametro". 
        LCD_Char(parametro % 10 + '0'); // Imprimimos en la pantalla LCD las unidades de la variable "parametro". 
        Parpadeo(); // Llamamos a la funci�n Parpadeo().

        if (!Pulsador_1) // Si el Pulsador_1 es presionado.
            if (Anti_rebote()) // Si la funci�n Anti_rebote() devuelve un 1.
            {
                i++; // Incrementamos el valor de i en una unidad.
                return parametro; // Retornamos el valor de la variable "parametro".
            }
    }
}

void init_rtc() {
    I2C_Init(); // Inicializamos la comunicaci�n I2C con una frecuencia de 100KHz. para el DS1307.
}

void pines_ConfigurarHora(void) {
    ADCON1bits.PCFG = 0b1101; //Puertos analogicos AN0, AN1
    TRISAbits.RA2 = 1; // Configuramos los pines RA2 y RA3 como entradas digitales.
    TRISAbits.RA3 = 1;
    inicializar_lcd(); // Inicializamos la pantalla LCD 16x2. 
}

void configurarHora(void) {

    if (!Pulsador_1) // Si Pulsador_1 es presionado.
        if (Anti_rebote()) // Si la funci�n Anti_rebote() devuelve un 1.
        {
            i = 0; // La variable i = 0.          
            hours = Establecer_Hora_Fecha(1, 6, hours); //  Llamamos a la funci�n Establecer_Hora_Fecha con x=7; y=1; parametro=hours.
            minutes = Establecer_Hora_Fecha(1, 9, minutes); //  Llamamos a la funci�n Establecer_Hora_Fecha con x=10; y=1; parametro=minutes.
            day = Establecer_Hora_Fecha(2, 6, day); //  Llamamos a la funci�n Establecer_Hora_Fecha con x=7; y=2; parametro=day.
            month = Establecer_Hora_Fecha(2, 9, month); //  Llamamos a la funci�n Establecer_Hora_Fecha con x=10; y=2; parametro=month.
            year = Establecer_Hora_Fecha(2,14, year); //  Llamamos a la funci�n Establecer_Hora_Fecha con x=15; y=2; parametro=year..
            while (Anti_rebote()); // Esperamos mientras Anti_rebote() sea 1.
            minutes = Decimal_a_BCD(minutes); // Llamamos a la funci�n Decimal_a_BCD(numero=minutes).
            hours = Decimal_a_BCD(hours); // Llamamos a la funci�n Decimal_a_BCD(numero=hours).
            day = Decimal_a_BCD(day); // Llamamos a la funci�n Decimal_a_BCD(numero=day).
            month = Decimal_a_BCD(month); // Llamamos a la funci�n Decimal_a_BCD(numero=mes). 
            year = Decimal_a_BCD(year); // Llamamos a la funci�n Decimal_a_BCD(numero=a�o).

            RTC_Clock_Write(0x00, minutes, hours, 0x05);
            RTC_Calendar_Write(0x01, day, month, year);
            __delay_ms(200); // Retardo de 200 ms.
        }
    
    RTC_Read_Clock(0); /*gives second,minute and hour*/
    RTC_Read_Calendar(3); /*gives day, date, month, year*/

    Reloj_Calendario(); // Llamamos a la funci�n Reloj_Calendario().x|
    __delay_ms(50); // Retardo de 50 ms.
}

void Reloj_Calendario(void) //Funci�n de visualizaci�n de HORA Y FECHA.
{
    static char Time[] = "TIME: 00:00:00"; // Arreglo est�tico char "Time". 
    static char Date_var[] = "DATE: 00/00/2000"; // Arreglo est�tico char "Date".

    seconds = BCD_a_Decimal(sec); // Llamamos a la funci�n de conversi�n de BCD a Decimal.
    minutes = BCD_a_Decimal(min); // Llamamos a la funci�n de conversi�n de BCD a Decimal.
    hours = BCD_a_Decimal(hour); // Llamamos a la funci�n de conversi�n de BCD a Decimal.
    day = BCD_a_Decimal(Date); // Llamamos a la funci�n de conversi�n de BCD a Decimal.
    month = BCD_a_Decimal(Month); // Llamamos a la funci�n de conversi�n de BCD a Decimal.
    year = BCD_a_Decimal(Year); // Llamamos a la funci�n de conversi�n de BCD a Decimal.

    Time[6] = hours / 10 + '0'; // Guardamos las decenas de la variable "hours" en la posici�n 6 del arreglo "Time".
    Time[7] = hours % 10 + '0'; // Guardamos las unidades de la variable "hours" en la posici�n 7 del arreglo "Time".
    Time[9] = minutes / 10 + '0'; // Guardamos las decenas de la variable "minutes" en la posici�n 9 del arreglo "Time".
    Time[10] = minutes % 10 + '0'; // Guardamos las unidades de la variable "minutes" en la posici�n 10 del arreglo "Time".
    Time[12] = seconds / 10 + '0'; // Guardamos las decenas de la variable "seconds" en la posici�n 12 del arreglo "Time".
    Time[13] = seconds % 10 + '0'; // Guardamos las unidades de la variable "secods" en la posici�n 13 del arreglo "Time".

    Date_var[6] = day / 10 + '0'; // Guardamos las decenas de la variable "day" en la posici�n 6 del arreglo "Date".
    Date_var[7] = day % 10 + '0'; // Guardamos las unidades de la variable "day" en la posici�n 7 del arreglo "Date".
    Date_var[9] = month / 10 + '0'; // Guardamos las decenas de la variable "month" en la posici�n 9 del arreglo "Date".
    Date_var[10] = month % 10 + '0'; // Guardamos las unidades de la variable "month" en la posici�n 10 del arreglo "Date".
    Date_var[14] = year / 10 + '0'; // Guardamos las decenas de la variable "year" en la posici�n 14 del arreglo "Date".
    Date_var[15] = year % 10 + '0'; // Guardamos las unidades de la variable "year" en la posici�n 15 del arreglo "Date".
    
    LCD_String_xy(1, 0, Time);
    
    LCD_String_xy(2, 0, Date_var); 
}


