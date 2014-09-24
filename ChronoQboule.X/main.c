/*
 * File:   main.c
 * Author: 7Robot
 *
 * Created on 15 septembre 2014, 20:06
 */

//configuration

#pragma config XINST = OFF
//#pragma config FOSC = INTIO2


#include <stdio.h>
#include <stdlib.h>
#include <p18f25k80.h>
#include <xc.h>
#include <timers.h>
#include <p18cxxx.h>
#include <portb.h>
#include "converter.h"

////////////////////////////////////DEFINE /////////////////////////////////

#define Afficheur1 PORTAbits.RA1
#define Afficheur2 PORTAbits.RA2
#define Afficheur3 PORTAbits.RA3
#define Afficheur4 PORTAbits.RA4
#define Afficheur5 PORTAbits.RA5


////////////////////////////////VARIABLES GLOBALES////////////////////////////////////////////

int time;

char milliseconde = 0;
char dizaine_milliseconde = 0;
char centaine_milliseconde = 0;
char seconde = 0;
char dizaine_seconde = 0;
char balayage = 0;
char front_montant = 0;
char old_state = 0;
char stance = 0;
char valeur = 0;

void rafraichissement(int);
void initialisation(void);
void time_converter(int);


//Main Interrupt Service Routine (ISR)

void interrupt low_interrupt() {
    //Check if it is TMR0 Overflow ISR
    if (TMR0IE && TMR0IF) {
        //TMR0 Overflow ISR
        TMR0 = 14; ///offset
      //  if (front_montant && old_state) {
        //    time++;
       // }

        if (balayage == 4) {
            balayage = 0;
        } else {
            balayage++; //Increment Over Flow Counter
        }
        time_converter(time);
        rafraichissement(balayage);
        //Clear Flag
        TMR0IF = 0;
    }
}
/*
void interrupt bouton(){

    if(INTCONbits.INT0IF == 1) {
        
        PORTBbits.RB3 =~ PORTBbits.RB3;

    }
    INTCONbits.INT0IF = 0;

}
*/








int main(int argc, char** argv) {
    initialisation();
    PORTC=0b11111111;



    while (1) {
       // PORTA=0b00000000;
        //PORTA=0b11111111;
        for (int a=0 ; a <11111 ;a++)
        {
        for( int k=0 ; k<7000;k++){}
        time =a;
        }

       // if ((PORTCbits.RC0 == 1) ) {
         //   PORTBbits.RB3 = 1;
          //  old_state = 1;
         /*
            if (stance < 2) {
                stance++;
            } else {
                stance = 0;
            }*/
       // }
       // else if ((PORTCbits.RC0 == 0 ) ) {
       //     PORTBbits.RB3 = 0;
       //     old_state = 0;
       // }
             
        /*
        time_converter(time);

        switch (stance) {
            case 0:
            {
                time = 0;

            }
                break; //affichage d'accueil en attente d'un appui
            case 1:;
                break; //départ du chrono
            case 2:;
                break; //arret du chrono
            default : ;
        }
*/


    }

    return (EXIT_SUCCESS);
}

void rafraichissement(int afficheur) {


    switch (afficheur) {

        case 0:
        segments(milliseconde);
        PORTA = 0b00000001;
            break;
        case 1: 
        segments(dizaine_milliseconde);
        PORTA = 0b00000010;
            break;
        case 2: 
        segments(centaine_milliseconde);
        PORTA = 0b00000100;
            break;
        case 3: 
        segments(seconde);
        PORTA = 0b00001000;
            break;
        case 4: 
        segments(dizaine_seconde);
        PORTA = 0b00100000;
            break;
        default:;
    }
}

//intcon tmr4IP IPRX

void initialisation(void) {
    //unsigned char config=0;
    ///////////////////////CONFIGURATION///////////////////////////////////////////
    INTCON = 0b11100000;

    TRISA = 0; // mets les ports A en sortie
    TRISC = 0; // mets les ports C en sortie sauf le bouton en entrée (RC0)
    TRISB = 0; // entrée pour le bouton
    PORTC = 0b00000000;




    //WPUBbits.WPUB4 = 1;
    // ANSELH = 0; //configure les entrées, 0=digitales
    //ANSEL = 0; //configure les entrées, 0=digitales

    /////////////////////INTERRUPTION SUR CHANGEMENT DETAT BOUTON//////////////////////////
    //INT0IE=1; // enable interruption
   // RBIE =1; // enable port B interrupt

    //**************** configure INT0 with pullups enabled, falling edge *********************************
	//	config = PORTB_CHANGE_INT_ON | FALLING_EDGE_INT | PORTB_PULLUPS_ON;
	//    OpenRB0INT(config );					//configures INT0 & enables it

   // INTCON2bits.RBPU = 0;

    //Setup Timer0 la persistance retinienne
    T0PS0 = 0; //Prescaler is divide by 256
    T0PS1 = 1;
    T0PS2 = 0;
    PSA = 0; //Timer Clock Source is from Prescaler
    T0CS = 0; //Prescaler gets clock from FCPU
    T08BIT = 1; //8 BIT MODE
    TMR0IE = 1; //Enable TIMER0 Interrupt
    PEIE = 1; //Enable Peripheral Interrupt
    GIE = 1; //Enable INTs globally

    TMR0ON = 1; //Now start the timer!

}

void time_converter(int time) {
    milliseconde = time % 10;
    dizaine_milliseconde = (time / 10) % 10;
    centaine_milliseconde = (time / 100) % 10;
    seconde = (time / 1000) % 10;
    dizaine_seconde = (time / 10000) % 10;

}
