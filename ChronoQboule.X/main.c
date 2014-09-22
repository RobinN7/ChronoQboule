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

////////////////////////////////////DEFINE /////////////////////////////////
#define SegmentA PORTBbits.PORTB7
#define SegmentB PORTBbits.PORTB6
#define SegmentC PORTBbits.PORTB5
#define SegmentD PORTBbits.PORTB4
#define SegmentE PORTBbits.PORTB3
#define SegmentF PORTBbits.PORTB2
#define SegmentG PORTBbits.PORTB1
#define SegmentH PORTBbits.PORTB0
#define Afficheur1 PORTAbits.RA1
#define Afficheur2 PORTAbits.RA2
#define Afficheur3 PORTAbits.RA3
#define Afficheur4 PORTAbits.RA4
#define Afficheur5 PORTAbits.RA5


////////////////////////////////VARIABLES GLOBALES////////////////////////////////////////////

int time;

char milliseconde =0 ;
char dizaine_milliseconde = 0;
char centaine_milliseconde = 0;
char seconde = 0;
char dizaine_seconde =0;
char balayage = 0;
char front_montant = 0;
char old_state = 0;

void rafraichissement (int);
void initialisation (void);
void time_converter(int);



//Main Interrupt Service Routine (ISR)
/*void interrupt high_interrupt()
{

}
*/
//Main Interrupt Service Routine (ISR)
void interrupt low_interrupt()
{
   //Check if it is TMR0 Overflow ISR
   if(TMR0IE && TMR0IF)
   {
      //TMR0 Overflow ISR
       TMR0=14; ///offset
       if(front_montant && old_state)
       {
           time++;
       }

       if (balayage ==4)
       {
           balayage = 0;
       }
       else
       {
           balayage++;  //Increment Over Flow Counter
       }

       rafraichissement(balayage);
      //Clear Flag
      TMR0IF=0;
   }
}






int main(int argc, char** argv) {

    initialisation();


          
    while (1) {
        time_converter(time);
    }

    return (EXIT_SUCCESS);
}


void rafraichissement (int afficheur)
{

       
    switch(afficheur)
    {

        case 0 :    PORTA =0b00000001; break;
        case 1 :    PORTA =0b00000010; break;
        case 2 :    PORTA =0b00000100; break;
        case 3 :    PORTA =0b00001000; break;
        case 4 :    PORTA =0b00100000; break;
        default : ;
    }
}

//intcon tmr4IP IPRX

void initialisation (void)
{
        ///////////////////////CONFIGURATION///////////////////////////////////////////
    INTCON  =  0b11100000;
    TRISB = 0; // mets les ports B en sortie
    TRISA = 0; // mets les ports A en sortie


       //Setup Timer0 la persistance retinienne
   T0PS0=0; //Prescaler is divide by 256
   T0PS1=1;
   T0PS2=0;
   PSA=0;      //Timer Clock Source is from Prescaler
   T0CS=0;     //Prescaler gets clock from FCPU
   T08BIT=1;   //8 BIT MODE
   TMR0IE=1;   //Enable TIMER0 Interrupt
   PEIE=1;     //Enable Peripheral Interrupt
   GIE=1;      //Enable INTs globally


   TMR0ON=1;      //Now start the timer!


}



void time_converter(int time)
{
    milliseconde = time%10;
    dizaine_milliseconde = (time/10)%10;
    centaine_milliseconde = (time/100)%10;
    seconde = (time/1000)%10;
    dizaine_seconde = (time/10000)%10;

}
