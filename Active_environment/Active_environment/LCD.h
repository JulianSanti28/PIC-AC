/* 
 * File:   LCD.h
 * Author: ASUS
 *
 * Created on 29 de septiembre de 2021, 13:43
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h> // include processor files - each processor file is guarded.  
#include <pic18f4550.h>
#include "fuses.h"

    /********Definition of Ports***********/

#define RS LATD0                    /*PIN 0 of PORTB is assigned for register select Pin of LCD*/
#define EN LATD1                    /*PIN 1 of PORTB is assigned for enable Pin of LCD */
#define ldata LATD                  /*PORTB(PB4-PB7) is assigned for LCD Data Output*/ 
#define LCD_Port TRISD   
#define CMD_CLEAR_LCD 0x01
    
void inicializar_lcd();                    /*Initialize LCD*/
void LCD_Command(unsigned char );   /*Send command to LCD*/
void LCD_Char(unsigned char x);     /*Send data to LCD*/
void LCD_String(const char * );      /*Display data string on LCD*/
void LCD_String_xy(char, char , const char *);
void LCD_Clear();/*Clear LCD Screen*/
void LCD_Custom_Char(unsigned char loc, unsigned char *msg);
void mostrar_emoticon(char i);



#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

