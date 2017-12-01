// PIC18F26K22 Configuration Bit Settings

// 'C' source line config statements
// CONFIG1H
#pragma config FOSC = INTIO67   // Oscillator Selection bits (Internal oscillator block)
#pragma config PLLCFG = OFF     // 4X PLL Enable (Oscillator used directly)
#pragma config PRICLKEN = ON    // Primary clock enable bit (Primary clock enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRTEN = OFF     // Power-up Timer Enable bit (Power up timer disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 190       // Brown Out Reset Voltage bits (VBOR set to 1.90 V nominal)

// CONFIG2H
#pragma config WDTEN = OFF      // Watchdog Timer Enable bits (Watch dog timer is always disabled. SWDTEN has no effect.)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC1  // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<5:0> pins are configured as analog input channels on Reset)
#pragma config CCP3MX = PORTB5  // P3A/CCP3 Mux bit (P3A/CCP3 input/output is multiplexed with RB5)
#pragma config HFOFST = ON      // HFINTOSC Fast Start-up (HFINTOSC output and ready status are not delayed by the oscillator stable status)
#pragma config T3CMX = PORTC0   // Timer3 Clock input mux bit (T3CKI is on RC0)
#pragma config P2BMX = PORTB5   // ECCP2 B output mux bit (P2B is on RB5)
#pragma config MCLRE = INTMCLR  // MCLR Pin Enable bit (RE3 input pin enabled; MCLR disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection Block 0 (Block 0 (000800-003FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection Block 1 (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection Block 2 (Block 2 (008000-00BFFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection Block 3 (Block 3 (00C000-00FFFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection Block 0 (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection Block 1 (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection Block 2 (Block 2 (008000-00BFFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection Block 3 (Block 3 (00C000-00FFFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection Block 0 (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection Block 1 (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection Block 2 (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection Block 3 (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


/**************************/
/* Files to Include                                                           */
/**************************/

#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#endif

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */


/**************************/
/* User Global Variable Declaration                                           */
/**************************/

/**************************/
/* Initialize I/O and Peripherals for application */
/**************************/
void init(void) {
    //init PORTS
    TRISA = 0b00100000;        //    all outputs, except RA5(SS1 for SPI)
    TRISB = 0b11000010;        //    all outputs, except RX on RB7 & TX on RB6
    TRISC = 0b11010000;        //    all outputs, except RX on RC7 & TX on RC6 & RC4 (SDI1 for SPI)
};
    
    
/**************************/
/* UART init                                                                  */
/**************************/

void init_eusart(void) {
    //init EUSART
    BAUDCON1 = 0b00000000;     //   BRG16=0 (bit 3 -> 8 bits), WUE=0 (bit 1), ABDEN=0 (bit 0))
    TXSTA1 = 0b00100100;       //   8-bit, tx-enb, TXEN=1 (bit 5), SYNC=0 (bit 4) , brgh =1 bit 2
    RCSTA1 = 0b10010000;       //   SPEN=1 (bit 7), CREN=1 (bit 4)
    SPBRG1 = 0b00011001;       //  25 --> to have a 9600 baude rate
    
    // enable EUSART1 receive interrupt
    PIE1bits.RC1IE = 1;
}

/**************************/
/* SPI init                                                                  */
/**************************/
void init_spi(void) {
    //init SPI
    SSPxSTAT.bits.SMP = 1;
    SSPxSTAT.bits.CKE = 1;
    SSPCON1 = 0x20; // 00100000
    
    PIR1bits.SSPIF = 0;
}

void init_Timer(void)
{
    //init TMR0
    T0CON = 0xC7;
    TMR0L = (256-195);
}

/**************************/
/* Write Value                                                               */
/**************************/
void UART_Write(unsigned char Data) {
    while(! TXSTA1bits.TRMT) ;
    
    TXREG1 = Data;

}


void UART_Write_Text(char *text)
{
    for (unsigned int i=0;text[i]!='\0';i++)
        UART_Write(text[i]);
}

/**************************/
/* ReadValue                                                                  */
/**************************/


unsigned char UART_Read()
{
    if(PIR1bits.RC1IF)  ;
        return RCREG1;
}

void UART_Read_Text(char *Output, unsigned int length)
{
    int i;
    for (int i=0;i<length;i++)
        Output[i] = UART_Read();
}

/**************************/
/* EEPROM functions                                                               */
/**************************/

unsigned char spiRead(){
    SSPBUF = data_;
    while(!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;
    return SSPBUF;
}

unsigned char spiWrite(unsigned char data_){
    SSPBUF = data_;
    while(!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;
    return SSPBUF;
}

unsigned char EReadStatus () {
    unsigned char c;
    spiWrite(0x05);
    c = spiRead();
    return c;
}

unsigned char EWriting() {
    unsigned char c;
    spiWrite(0x05);
    c = spiRead();
    return c & 1;
}

/**************************/
/* Main Program                                                               */
/**************************/

void main(void) {
    //unsigned int test;
    unsigned char test[3];

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize Timer */
    init_Timer();
    
    /* Initialize I/O and Peripherals for application */
    init();
    
    /* Initialize EUSART */
    init_eusart();

    /* TODO <INSERT USER APPLICATION CODE HERE> */
    
    /* Initialize SPI */
    init_spi();

    while(1) { 
       /* TEST EUSART */
        /*
        UART_Read_Text(test, 3);
        for(unsigned int i=0; i<50000; i++) ;
        UART_Write_Text(test);
        for(unsigned int i=0; i<50000; i++) ;
        UART_Write(0x00);
        for(unsigned int i=0; i<50000; i++) ;
        */
       
        
        
    }
}