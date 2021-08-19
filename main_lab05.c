/*
 * File:   main_lab05.c
 * Author: acer
 *
 * Created on 12 de agosto de 2021, 01:40 PM
 */
/*
 * File:   main_slave2.c
 * Author: acer
 *
 * Created on 10 de agosto de 2021, 11:44 AM
 */
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)
// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Progra
//****DirectivasCompliador*****//
#define _XTAL_FREQ 4000000
//*****IMPORTACION DE LIBRERIAS******
#include <xc.h>
#include <stdint.h>
#include <pic16f887.h> 
#include "UART_l5.h"
uint8_t contador;
char Z1[2];
int banderas = 0;
/******PROTOTIPOS DE FUNCIONES */
void setup(void);       
void conv(uint8_t *var);
//**************Interrupciones**************
void __interrupt()isr(void) /*interrupciones*/
{
    if(RBIF == 1)           //Bandera IOCB
    {
        if(RB0 == 0)        //Si boton en RB0 esta presionado
        {
            PORTA++;        //Aumenta contador del PORTA
        }
        if(RB1 == 0)        //Boton en RB1 esta presionado
        {
            PORTA--;        //Decrementa PORTA
        }
    }
    INTCONbits.RBIF = 0;
}
//*********************************funcionPrincipal**********
void main(void) {
    setup();                /*funcion de configuracion principal*/
    configuracionUART();
    //*********************************LoopPrincipal*********
    while(1)
    {
        contador = PORTA; 
        valorsensores();
        //conv(contador);
        if (PIR1bits.RCIF)
        {
            //PORTD = 0; 
            __delay_ms(200);
            PORTD = RCREG;
        }
    }
}
//*************Funciones************************
void setup(void)
{ 
    //*******configuración io entradas y salidas****
    ANSEL = 0b00000000;
    ANSELH = 0x00;     //Salidas Digitales
     
    TRISB = 0x03;    
    TRISA = 0x00;
    TRISD = 0x00;
    OPTION_REGbits.nRBPU = 0; 
    WPUB = 0b00000011;      //Habilitar Pull interno 
    
    PORTA = 0x00; 
    PORTB = 0x00;
    PORTD = 0x00;
    //configuración IOC
    IOCBbits. IOCB0 = 1; 
    IOCBbits. IOCB1 = 1;
    //configuración del reloj (oscilador interno)
    OSCCONbits. IRCF2 = 1; 
    OSCCONbits. IRCF1 = 1;
    OSCCONbits. IRCF0 = 0;  //4Mhz
    OSCCONbits. SCS = 1;
    //configuración interrupción
    INTCONbits. GIE = 1;        //Globales
    INTCONbits. RBIE = 1;       //IOCB
    INTCONbits. RBIF = 0;
    INTCONbits.PEIE = 1;        //Perifericas
}
void conv(uint8_t *var)
{
    uint8_t unid;
    uint8_t dece;
    uint8_t cent;
    
    cent = (*var/100);
    dece = (*var-(cent*100)/10);
    unid = (*var-(cent*100))%10;
    
    Envio_caracter(cent + 48);
    Envio_caracter(dece + 48);
    Envio_caracter(unid + 48);
}