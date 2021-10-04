#include "Leds.h"
#include "LCD.h"
/*
*@init_leds 
*@brief 
*@param void no recibe parametros
*@return void
*/
void init_leds(void) {

    CFG_LED_POWER_B = OUTPUT;
    CFG_LED_POWER_G = OUTPUT;
    CFG_LED_POWER_R = OUTPUT;
    CFG_LED_POWER_Y = OUTPUT;
}

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
// validar los resultados ;

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
