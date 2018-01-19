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
#include <stdio.h>
#include <string.h>

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
    ANSELC&=0x3F;
    // enable EUSART1 receive interrupt
  //  PIE1bits.RC1IE = 1;
}

/**************************/
/* SPI init                                                                  */
/**************************/
#define CS LATCbits.LATC2
#define WP LATCbits.LATC3

void init_spi(void) {
    //init SPI
        
    SSP1STATbits.SMP = 1;
    SSP1STATbits.CKE = 1;
    SSPCON1 = 0x20; // 00100000
    
    PIR1bits.SSPIF = 0;
    
    CS = 1;
    WP = 0;
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
   // if(PIR1bits.RC1IF)  ;
        return RCREG1;
}

void UART_Read_Text(char *Output, unsigned int length)
{
    for (int unsigned i=0;i<length;i++)
        Output[i] = UART_Read();
}

/**************************/
/* EEPROM functions                                                               */
/**************************/
unsigned char spiReadWrite(unsigned char data){
    SSPBUF = data;
    while(!SSP1STATbits.BF);
    return SSPBUF;
}

unsigned char EReadData (unsigned long addr) {
    unsigned char data;
    
    CS = 0;
    // send READ instruction
    spiReadWrite(0x03); 
    // send address in 24 bits
    spiReadWrite(addr>>16);
    spiReadWrite(addr>>8);
    spiReadWrite((unsigned char) addr);
    // read the data
    data = spiReadWrite(0xFF); //Data 
    
    CS = 1;
 
    return data;
}

void EWriteData (unsigned char data, unsigned long addr) {
    unsigned char poubelle;
    
    CS = 0;
    poubelle = spiReadWrite(0x06);
    WP = 1;    
    CS = 1;
    
    CS = 0;
    // send WRITE instruction
    poubelle = spiReadWrite(0x03);
    // send address in 24 bits
    poubelle = spiReadWrite(addr>>16);
    poubelle = spiReadWrite(addr>>8);
    poubelle = spiReadWrite((unsigned char) addr);
    //send the data
    poubelle = spiReadWrite(data);  
    CS = 1;
}

/**************************/
/* GPS                    */
/**************************/


/**************************/
/* Main Program                                                               */
/**************************/
void gestionserie(void)
{ unsigned char ch;
    static unsigned char mae_serie=0;
    //static unsigned int heureprov=0;
    static unsigned int heureDizaineprov=0;
    static unsigned int heureUniteprov=0;
    static unsigned int minuteUniteprov=0;
    static unsigned int minuteDizaineprov=0;  
    static unsigned int minuteUniteprov=0;
    //static unsigned int secondeprov=0;
    static unsigned int secondeDizaineprov=0;
    static unsigned int secondeUniteprov=0;
    static unsigned char valideprov=0;
    //static unsigned int lat1prov=0;
    static unsigned int lat1prov1=0;
    static unsigned int lat1prov2=0;
    static unsigned int lat1prov3=0;
    static unsigned int lat1prov4=0;
    static unsigned int lat1provP=0;
    static unsigned int lat1prov5=0;
    static unsigned int lat1prov6=0;
    static unsigned int lat1prov7=0;
    static unsigned int lat1prov8=0;
    //static unsigned int lat2prov=0;
    //static unsigned int long1prov=0;
    //static unsigned int long2prov=0;
    static unsigned int long1prov1=0;
    static unsigned int long1prov2=0;
    static unsigned int long1prov3=0;
    static unsigned int long1prov4=0;
    static unsigned int long1prov5=0;
    static unsigned int long1provP=0;
    static unsigned int long1prov6=0;
    static unsigned int long1prov7=0;
    static unsigned int long1prov8=0;
    static unsigned int long1prov9=0;
    static unsigned char E_Wprov=0;
    static unsigned char N_Sprov=0;
    //static unsigned int yearprov=0;
    static unsigned int dayDizaineprov=0;
    static unsigned int dayUniteprov=0;
    //static unsigned int monthprov=0;
    static unsigned int monthDizaineprov=0;
    static unsigned int monthUniteprov=0;
    //static unsigned int dayprov=0;
    static unsigned int yearDizaineprov=0;
    static unsigned int yearUniteprov=0;
    
    unsigned char trame_write[24];
       
    
    ch=RCREG1;

    if (ch=='$'){mae_serie=1;return;}

    switch(mae_serie)
    {
        case 0: //attente synchro
            TXREG1 = '0';
            TXREG1 = '\n';
            TXREG1 = '\r';
            

            break;
        case 1://attente message gps GPMRC
            TXREG1 = '1';
            if(ch=='G'){mae_serie++;break;}
            mae_serie=0;
            break;
        case 2:
            TXREG1 = '2';
            if(ch=='P'){mae_serie++;break;}
            mae_serie=0;
            break;
        case 3:
            TXREG1 = '3';
            if(ch=='R'){mae_serie++;break;}
            mae_serie=0;
            break;
        case 4:
            TXREG1 = '4';
            if(ch==','){mae_serie++;break;}
            break;
        case 5: //heure dizaine
            TXREG1 = '5';
            if((ch<'0')||(ch>'2')){mae_serie=0;break;}
            //heureprov=ch-'0';
            //heureprov *= 10;
            heureDizaineprov=ch;
            mae_serie++;
            break;
        case 6: // heure unite
            TXREG1 = '6';
             if((ch<'0')||(ch>'9')){mae_serie=0;break;}
            //heureprov+=ch-'0';
            heureUniteprov=ch+1;
            mae_serie++;
            break;
        case 7: // minute dizaine
            TXREG1 = '7';
            if((ch<'0')||(ch>'5')){mae_serie=0;break;}
            minuteDizaineprov=ch;
            mae_serie++;
            break;
        case 8:  // minute unite
            TXREG1 = '8';
            if((ch<'0')||(ch>'9')){mae_serie=0;break;}
            minuteUniteprov=ch;
            mae_serie++;
            break;
        case 9:  // seconde dizaine
            TXREG1 = '9';
            if((ch<'0')||(ch>'5')){mae_serie=0;break;}
            //secondeprov=ch-'0';
            //secondeprov*=10;
            secondeDizaineprov=ch;
            mae_serie++;
            break;
        case 10:  // seconde unite
            TXREG1 = 'A';
            if((ch<'0')||(ch>'9')){mae_serie=0;break;}
            //secondeprov+=ch-'0';
            secondeUniteprov=ch;
            mae_serie++;
            break;
        case 11:  
            TXREG1 = 'B';
            if(ch==','){mae_serie++;break;}
            break;
        case 12:  
            TXREG1 = 'C';
            if(ch!='A'){mae_serie=0;break;}
            valideprov=ch;
            mae_serie++;
            break;
        case 13:
            TXREG1 = 'D';
            if(ch==','){mae_serie++;break;}
            mae_serie=0;
            break;
        case 14: // Latitude 1er caractère
            TXREG1 = 'E';
            if((ch<'0')||(ch>'9')){mae_serie=0;break;}
            //lat1prov=ch-'0';
            //lat1prov*=1000;
            lat1prov1=ch;
            mae_serie++;
            break;
        case 15: // Latitude 2eme caractère
            TXREG1 = 'F';
            if((ch<'0')||(ch>'9')){mae_serie=0;break;}
            //lat1prov+=(ch-'0')*100;
            lat1prov2=ch;
            mae_serie++;
            break;
        case 16: // Latitude 3eme caractère
            TXREG1 = 'G';
            if((ch<'0')||(ch>'9')){mae_serie=0;break;}
            //lat1prov+=(ch-'0')*10;
            lat1prov3=ch;
            mae_serie++;
            break;
        case 17: // Latitude 4eme caractère
            TXREG1 = 'H';
            if((ch<'0')||(ch>'9')){mae_serie=0;break;}
            //lat1prov+=ch-'0';
            lat1prov4=ch;            
            mae_serie++;
            break;
        case 18:
            TXREG1 = 'I';
            if(ch!='.'){mae_serie=0;break;}
            lat1provP=ch;
            mae_serie++;
            break;
        case 19: // Latitude2 1er caractère
            TXREG1 = 'J';
            if((ch<'0')||(ch>'9')){mae_serie=0;break;}
            //lat2prov=ch-'0';
            //lat2prov*=1000;
            lat1prov5=ch;
            mae_serie++;
            break;
        case 20: // Latitude2 2eme caractère
            TXREG1 = 'K';
            if((ch<'0')||(ch>'9')){mae_serie=0;break;}
            //lat2prov+=(ch-'0')*100;
            lat1prov6=ch;
            mae_serie++;
            break;
        case 21: // Latitude2 3eme caractère
            TXREG1 = 'L';
            if((ch<'0')||(ch>'9')){mae_serie=0;break;}
            //lat2prov+=(ch-'0')*10;
            lat1prov7=ch;
            mae_serie++;
            break;
        case 22: // Latitude2 4eme caractère
            TXREG1 = 'M';
            if((ch<'0')||(ch>'9')){mae_serie=0;break;}
            //lat2prov+=ch-'0';
            lat1prov8=ch;
            mae_serie++;
            break;
        case 23:
            TXREG1 = 'N';
            if(ch!=','){mae_serie=0;break;}
            mae_serie++;
            break;
        case 24:
            TXREG1 = 'O';
            if((ch!='N')&&(ch!='S')){mae_serie=0;break;}
            N_Sprov=ch;
            mae_serie++;
            break;
        case 25:
            TXREG1 = 'P';
            if(ch=','){mae_serie++;break;}
            break;
        case 26: // Longitude 1er caractère
            TXREG1 = 'Q';
            if((ch<'0')||(ch>'9')){mae_serie=0;break;}
            //long1prov=ch-'0';
            //long1prov*=10000;
            long1prov1=ch;
            mae_serie++;    
            break;
        case 27: // Longitude 2eme caractère
            TXREG1 = 'R';
            if((ch<'0')||(ch>'9')){mae_serie=0;break;}
            //long1prov+=(ch-'0')*1000;
            long1prov2=ch;
            mae_serie++;  
            break;
        case 28: // Longitude 3eme caractère
            TXREG1 = 'S';
            if((ch<'0')||(ch>'9')){mae_serie=0;break;}
            //long1prov+=(ch-'0')*100;
            long1prov3=ch;
            mae_serie++;   
            break;
        case 29: // Longitude 4eme caractère
            TXREG1 = 'T';
            if((ch<'0')||(ch>'9')){mae_serie=0;break;}
            //long1prov+=(ch-'0')*10;
            long1prov4=ch;
            mae_serie++;  
            break;
        case 30: // Longitude 5eme caractère
            TXREG1 = 'U';
            if((ch<'0')||(ch>'9')){mae_serie=0;break;}
            //long1prov+=ch-'0';
            long1prov5=ch;
            mae_serie++;  
            break;
        case 31:
            TXREG1 = 'V';
            if(ch!='.'){mae_serie=0;break;}
            long1provP=ch;
            mae_serie++;
            break;                    
        case 32: // Longitude2 1er caractère
            TXREG1 = 'W';
            if((ch<'0')||(ch>'9')){mae_serie=0;break;}
            //long2prov=ch-'0';
            //long2prov*=1000;
            long1prov6=ch;
            mae_serie++;
            break;
        case 33: // Longitude2 2eme caractère
            TXREG1 = 'X';
            if((ch<'0')||(ch>'9')){mae_serie=0;break;}
            //long2prov+=(ch-'0')*100;
            long1prov7=ch;
            mae_serie++;
            break;
        case 34: // Longitude2 3eme caractère
            TXREG1 = 'Y';
            if((ch<'0')||(ch>'9')){mae_serie=0;break;}
            //long2prov+=(ch-'0')*10;
            long1prov8=ch;
            mae_serie++;
            break;
        case 35: // Longitude2 4eme caractère
            TXREG1 = 'Z';
            if((ch<'0')||(ch>'9')){mae_serie=0;break;}
            //long2prov+=ch-'0';
            long1prov9=ch;
            mae_serie++;
            break;
        case 36:
            TXREG1 = 'a';
            if(ch!=','){mae_serie=0;break;}
            mae_serie++;
            break;
        case 37:
            TXREG1 = 'b';
            if((ch!='E')&&(ch!='W')){mae_serie=0;break;}
            E_Wprov=ch;
            mae_serie++;
            break;
        case 38:
            TXREG1 = 'c';
            if(ch==','){mae_serie++;break;}
            break;
        case 39:
            TXREG1 = 'd';
            if(ch==','){mae_serie++;break;}
            break;
        case 40:
            TXREG1 = 'e';
            if(ch==','){mae_serie++;break;}
            break;
        case 41: // jour dizaine
            TXREG1 = 'f';
            if((ch<'0')||(ch>'9')){mae_serie=0;break;}
            //dayprov=ch-'0';
            //dayprov*=10;
            dayDizaineprov=ch;
            mae_serie++;
            break;
        case 42: // jour unite
            TXREG1 = 'g';
            if((ch<'0')||(ch>'9')){mae_serie=0;break;}
            //dayprov+=ch-'0';
            dayUniteprov=ch;
            mae_serie++;
            break;
        case 43: // mois dizaine
            TXREG1 = 'h';
            if((ch<'0')||(ch>'9')){mae_serie=0;break;}
            //monthprov=ch-'0';
            //monthprov*=10;
            monthDizaineprov=ch;
            mae_serie++;
            break;
        case 44: // mois unite
            TXREG1 = 'i';
            if((ch<'0')||(ch>'9')){mae_serie=0;break;}
            //monthprov+=ch-'0';
            monthUniteprov=ch;
            mae_serie++;
            break;
        case 45: // année dizaine
            TXREG1 = 'j';
            if((ch<'0')||(ch>'9')){mae_serie=0;break;}
            //yearprov=ch-'0';
            //yearprov*=10;
            yearDizaineprov=ch;
            mae_serie++;
            break;
        case 46: // année unite
            TXREG1 = 'k';
            if((ch<'0')||(ch>'9')){mae_serie=0;TXREG1 = '!';break;}
            //yearprov+=ch-'0';
            yearUniteprov=ch;
//            TXREG1 = '\n';
//            TXREG1 = '\r';
//            unsigned char heure = heureprov + '0';
//            TXREG1 = heure;
//            unsigned char minute = minuteprov + '0';
            
            TXREG1 = '|';
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = heureDizaineprov;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = heureUniteprov;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = 'H';
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = minuteDizaineprov;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = minuteUniteprov;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = 'm';
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = secondeDizaineprov;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = secondeUniteprov;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = 's';
            
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = '|';
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = lat1prov1;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = lat1prov2;            
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = lat1prov3;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = lat1prov4;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = lat1provP;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = lat1prov5;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = lat1prov6;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = lat1prov7;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = lat1prov8;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = N_Sprov;
            
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = '|';
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = long1prov1;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = long1prov2;            
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = long1prov3;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = long1prov4;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = long1prov5;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = long1provP;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = long1prov6;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = long1prov7;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = long1prov8;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = long1prov9;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = E_Wprov;
            
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = '|';
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = dayDizaineprov;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = dayUniteprov;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = '/';
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = monthDizaineprov;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = monthUniteprov;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = '/';
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = yearDizaineprov;
            for(unsigned int i=0; i<5000; i++);
            TXREG1 = yearUniteprov;
            
            
//            unsigned char seconde = secondeprov + '0';
//            TXREG1 = seconde;
//            unsigned int lat1prov=0;
//            unsigned int lat2prov=0;
//            unsigned int long1prov=0;
//            unsigned int long2prov=0;
//            unsigned int yearprov=0;
//            unsigned int monthprov=0;
//            unsigned int dayprov=0;
            
//            trame_write[0] = heureprov;
//            trame_write[1] = "H"; 
//            trame_write[2] = minuteprov;
//            trame_write[3] = "m";
//            trame_write[4] = secondeprov;
//            trame_write[5] = "s";
//            trame_write[6] = valideprov;
//            trame_write[7] = ",";
//            trame_write[8] = lat1prov;
//            trame_write[9] = ".";
//            trame_write[10] = lat2prov;
//            trame_write[11] = ",";
//            trame_write[12] = N_Sprov;
//            trame_write[13] = ",";
//            trame_write[14] = long1prov;
//            trame_write[15] = ".";
//            trame_write[16] = long2prov;
//            trame_write[17] = ",";
//            trame_write[18] = E_Wprov;
//            trame_write[19] = ",";
//            trame_write[20] = dayprov;
//            trame_write[21] = monthprov;
//            trame_write[22] = yearprov;
//            trame_write[23] = "*";
//            
//            for (unsigned int i=0;trame_write[i]!='*';i++){
//                TXREG1=trame_write[i]; 
//                for(unsigned int i=0; i<50; i++);
//            }
            
            
            mae_serie=0;
//            heureprov=0;
//            minuteprov=0;
//            secondeprov=0;
            valideprov=0;
			//lat1prov=0;
			//lat2prov=0;
			//long1prov=0;
			//long2prov=0;
			E_Wprov=0;
			N_Sprov=0;
			//yearprov=0;
			//monthprov=0;
			//dayprov=0;
            
            break;
        default :
            mae_serie=0;
    }
    return;


}

void main(void) {
    char* heure=0;
    char* minute=0;
    char* seconde=0;
    char* valide=0;
    char* lat1=0;
    char* lat2=0;
    char* long1=0;
    char* long2=0;
    char* E_W=0;
    char* N_S=0;
    char* year=0;
    char* month=0;
    char* day=0;
    
    unsigned int cpt = 0;
    unsigned char Data = 0;
    
    //unsigned int test;
//    unsigned char test[2];
//    test[0] = 'a';
//    test[1] = 'b';
//    test[2] = 'c';
    
    //unsigned char data;

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize Timer */
    init_Timer();
    
    /* Initialize I/O and Peripherals for application */
    init();
    
    /* Initialize EUSART */
    init_eusart();
    
    /* Initialize SPI */
    init_spi();

//    char dataGPS;
//    char dataGPS_GNRMC[6] = {0};
//    char data[30];

    while(1) { 
        /* TEST EUSART */
        //UART_Write(0xFF);
         if(PIR1bits.RC1IF) {gestionserie();}
        
        /* TEST EEPROM 
        if (cpt == 0) {
            TXREG1 = '1';
            EWriteData ('A', 0x000001);
            for(unsigned int i=0; i<50000; i++) ;
            cpt++;
        }
         
        TXREG1 = EReadData (0x000001);
        for(unsigned int i=0; i<50000; i++);
        */

        
        /*
        EWriteData('a', 0x000000);
        for(unsigned int i=0; i<50000; i++) ;
        data = EReadData(0x000000);
        for(unsigned int i=0; i<50000; i++) ;
        */

        /*UART_Read_Text(data, strlen(data));
        for(unsigned int i=0; i<50000; i++);
        UART_Write_Text(data);
        for(unsigned int i=0; i<50000; i++);
        UART_Write(0x00);
        for(unsigned int i=0; i<50000; i++) ;*/

        /*dataGPS = (char)UART_Read_Text((char *)PORTCbits.RC6, (char)strlen((char *)PORTCbits.RC6));
        for(unsigned int i=0; i<50000; i++);
        UART_Write_Text((char *)dataGPS);
        for(unsigned int i=0; i<50000; i++);
        receivedGPS((char *)dataGPS);
        for(unsigned int i=0; i<50000; i++);
        UART_Write_Text((char *)dataGPS_GNRMC);*/
        
    }
}