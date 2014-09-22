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
#include "converter.h"

////////////////////////////////////DEFINE /////////////////////////////////
#define SegmentA PORTCbits.RC7
#define SegmentB PORTCbits.RC6
#define SegmentC PORTCbits.RC5
#define SegmentD PORTCbits.RC4
#define SegmentE PORTCbits.RC3
#define SegmentF PORTCbits.RC2
#define SegmentG PORTCbits.RC1
#define SegmentH PORTCbits.RC0
#define Afficheur1 PORTAbits.RA1
#define Afficheur2 PORTAbits.RA2
#define Afficheur3 PORTAbits.RA3
#define Afficheur4 PORTAbits.RA4
#define Afficheur5 PORTAbits.RA5
#define Bouton PORTBbits.RB5

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

void rafraichissement(int);
void initialisation(void);
void time_converter(int);


//Main Interrupt Service Routine (ISR)

void interrupt low_interrupt() {
    //Check if it is TMR0 Overflow ISR
    if (TMR0IE && TMR0IF) {
        //TMR0 Overflow ISR
        TMR0 = 14; ///offset
        if (front_montant && old_state) {
            time++;
        }

        if (balayage == 4) {
            balayage = 0;
        } else {
            balayage++; //Increment Over Flow Counter
        }

        rafraichissement(balayage);
        //Clear Flag
        TMR0IF = 0;
    }
}

int main(int argc, char** argv) {

    initialisation();



    while (1) {

        if ((PORTBbits.RB5 == 1) /*&& (old_state == 0)*/) {
            old_state = 1;
            PORTBbits.RB4 = 1;
            if (stance < 2) {
                stance++;
            } else {
                stance = 0;
            }
        } 
        else if ((PORTBbits.RB5 == 0 ) /*&& (old_state == 1)*/) {
            PORTBbits.RB4 = 1;
            old_state = 0;
        }
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
        }
    }

    return (EXIT_SUCCESS);
}

void rafraichissement(int afficheur) {


    switch (afficheur) {

        case 0: PORTA = 0b00000001;
        segments(dizaine_seconde);
            break;
        case 1: PORTA = 0b00000010;
        segments(seconde);
            break;
        case 2: PORTA = 0b00000100;
        segments(centaine_milliseconde);
            break;
        case 3: PORTA = 0b00001000;
        segments(dizaine_milliseconde);
            break;
        case 4: PORTA = 0b00100000;
        segments(milliseconde);
            break;
        default:;
    }
}

//intcon tmr4IP IPRX

void initialisation(void) {
    ///////////////////////CONFIGURATION///////////////////////////////////////////
    INTCON = 0b11100000;

    TRISA =0; // mets les ports A en sortie
    TRISC = 0; // mets les ports C en sortie
    TRISB = 1; // entrée pour le bouton
    TRISBbits.TRISB4 = 0;
   // ANSELH = 0; //configure les entrées, 0=digitales
    //ANSEL = 0; //configure les entrées, 0=digitales

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
