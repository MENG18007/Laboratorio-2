//******************************************************************************
/*
 * File:   CODIGO_ADC.c
 * Author: RENATO MENDIZABAL
 *
 * Created on February 25, 2021, 10:38 AM
 */
//******************************************************************************
// LIBRERIAS
//******************************************************************************
#include <xc.h>
// CONFIG1
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#define _XTAL_FREQ 8000000

//******************************************************************************
// VARIABLES
//******************************************************************************
char counter_Bin = 0;
char counter_ADC = 0;

//******************************************************************************
// VOIDS
//******************************************************************************
void setup(void);
void count_up(void);
void count_down(void);
void PBinario (void);
void Alarma (void);

//******************************************************************************
// CICLO PRINCIPAL
//******************************************************************************
void main(void) {
    
    setup();
    
    while (1){
        if (PORTBbits.RB1 == 1){
            count_up();         // Aumentamos la cuenta del contador binario
            PBinario();
        }
        if (PORTBbits.RB2 == 1){
            count_down();       // Decrementamos la cuenta del contador binario
            PBinario();
        }
        if (counter_ADC == counter_Bin){
            Alarma();
        }
    }
    
    return;
}

//******************************************************************************
// CONFIGURACION
//******************************************************************************
void setup(void) {
    TRISE = 0;
    PORTE = 0;
    ANSEL = 0;
    ANSELH = 0;
    TRISB = 0b00000110;
    PORTB = 0;
    TRISC = 0;
    PORTC = 0;              // Especificamos entradas y salidas
    counter_ADC = 3;
}
//******************************************************************************
// FUNCIONES
//******************************************************************************

void count_up(void){
    __delay_ms(100);
    counter_Bin += 1;          // Se incrementa la cuenta del contador binario
//    PORTC++;
}

void count_down(void){
    __delay_ms(100);
    counter_Bin -= 1;          // Se decrementa la cuenta del contador binario
//    PORTC--;
}

void PBinario(void){
    PORTC = counter_Bin;
}

void Alarma(void){
    PORTEbits.RE2 = 1;
    __delay_ms(400);
    counter_Bin = 0;
    PORTEbits.RE2 = 0;
    PORTC = 0;
}