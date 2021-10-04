/* 
 * File:   Principal.c
 * Author: 57322
 *
 * Created on 9 de agosto de 2021, 09:54 AM
 */

#include <xc.h>
#include <stdio.h>
#include <pic18f4550.h>
#include "fuses.h"
#include "LCD.h"
#include "sensores.h"
#include "Leds.h"
#include <stdint.h>  

#define OSCILADOR_INTERNO OSCCONbits.IRCF
#define OCHO_MHZ 0b111
#define OSCILADOR_DEL_SISTEMA OSCCONbits.SCS
#define PULL_UP RBPU 
#define ACTIVADO 0
#define OCHO_mHz 0x72


//void imprimir(int val, char texto[]);
void imprimir(int val, int val_1, int val_2);
void iniciar_emoticones();
void iniciar_pic();

void main(void) {

    iniciar_pic();//Inicializa valores del PIC
    inicializar_lcd();//Inicializa configuración del LCD
    init_leds();//Inicializa los pines para el manejo d eleds
    iniciar_emoticones();//Carga los emoticones a usar
    
    int s_dist = 0, s_temp = 0, s_luz = 0;//Variables para carga de información
    while (1) {
        s_dist = sensor_distancia(); //Almacenando el valor de distancia retornado por la función
        s_temp = sensor_temperatura();//Almacenando el valor de temperatura retornado por la función
        s_luz = sensor_luz();//Almacenando el valor de luz retornado por la función
        encender_leds(validar(s_temp, s_dist, s_luz));//Enciende o no los leds dependiendo del estado de cada sensor
        imprimir(s_dist, s_temp, s_luz);//Imprime la información capturada en cada instante
    }

}

/*
 *@bref Inicializa los osciladores y el pull-up con los valores que requerimos para la implementación.
 *@return void
 */
void iniciar_pic() {
    OSCILADOR_INTERNO = OCHO_MHZ;
    OSCILADOR_DEL_SISTEMA = 0b10; //?
    OSCCON = OCHO_mHz;
    PULL_UP = ACTIVADO;
}


/*
 *@bref Inicializa los arreglos con la información de los emoticones, además los guarda previamente para luego ser consultados.
 *@return void
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






















