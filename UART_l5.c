/*
 * File:   UART_l5.c
 * Author: acer
 *
 * Created on 12 de agosto de 2021, 02:46 PM
 */
#include <stdint.h>
#include <stdio.h>
#include <pic16f887.h>
#include <math.h>
#include <stdlib.h>
#define _XTAL_FREQ 4000000
//*****IMPORTACION DE LIBRERIAS******
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <pic16f887.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
uint8_t contador = 0;       /*Declaración variables*/
float v1;
float v2;
float v3;
char s[20];
#include "UART_l5.h"
void Envio_caracter(char caracter)
{
    while(!TXIF);       //Espera que envie dato TXIF = 1 siempre
    TXREG = caracter;   //Carga el caracter a TXREG y envía 
    return; 
}
void cadena_caracteres(char st[])
{
    int i = 0;          //i igual 0 posicion 
    while (st[i] !=0)   //revisar la posicion de valor de i 
    {
        Envio_caracter(st[i]); //enviar caracter de esa posicion 
        i++;                //incrementar variable para pasar a otra posicion 
    }                       //de cadena 
    return;
}
void valorsensores(void)
{
    //sprintf(s, "\r valorPORTD=%d", PORTD);
    //cadena_caracteres(s);
    
    sprintf(s,"%d", contador);
    cadena_caracteres(s);
}
void configuracionUART(void)
{
    TXSTAbits.SYNC = 0;             //Modo asíncrono
    TXSTAbits.BRGH = 1;             //Seleccion BAUD RATE
    BAUDCTLbits.BRG16 = 0; 
    
    SPBRG = 25;                     //Registros para valor BAUD RATE
    SPBRGH = 0; 
    
    RCSTAbits.SPEN = 1;         //Habilitar puerto serial asíncrono
    RCSTAbits.RX9 = 0;
    RCSTAbits.CREN = 1;         //Habilitar recepción de datos 

    TXSTAbits.TXEN = 1;         //Habilitar transmision
}