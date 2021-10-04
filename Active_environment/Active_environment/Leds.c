#include "Leds.h"
#include "LCD.h"
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
*@brief Enciende los leds designados segun el numero de fallos 0 = green ; 1= yelloww ; 2 o mas = red
*@param valor 
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
*@brief Valida los valores temperatura, distancia, luz segun los indicadores optimos definidos 
*@param temp Valor de la temperatura según el sensor de temperatura
*@param distancia Lectura de la distancia según el sensor de distancia
*@param luz Lectura del porcentaje de luminisidad  según el sensor de luz
*@return 0 si no hay valores fuera de rango, 1 si existe un valor fuera de rango  , 2 si existe dos valores fuera de rango
*/

int validar(int temp, int distancia, int luz) {


    int contador = 0;

    // verde valores  normales ; amarillo 1  fallando ; rojo 2 o + fallando
    if (temp < TEMP_BAJA || temp > TEMP_ALTA) { //Mayor a 30 grados y Menor a 17 es un estado no óptimo
        mostrar_emoticon(5);
        contador++;
    }
    if (distancia < DISTANCIA_OPTIMA) {//optimo 65 70 //distancia > 100 ||
        mostrar_emoticon(6);
        contador++;
    }
    if (luz > LUZ_ALTA_OPTIMA || luz < LUZ_BAJA_OPTIMA) {
        mostrar_emoticon(7);
        contador++;
    }

    if (contador == 0) {
        mostrar_emoticon(4);
    }


    return contador;
}
