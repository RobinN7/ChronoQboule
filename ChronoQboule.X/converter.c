
#include <stdio.h>
#include <stdlib.h>
#include <p18f25k80.h>
#include "converter.h"

void segments(char figure) {

/*
    0= a b c d e f .
    1= . b c . . . .
    2= a b . d e . g
    3= a b c d . . g
    4= . b c . . f g
    5= a . c d . f g
    6= a . c d e f g
    7= a b c . . . . 
    8= a b c d e f g  
    9= a b c d . f g
*/
            
switch(figure)
    {
        case 0 :    PORTB =0b1111110; break;
        case 1 :    PORTB =0b0110000; break;
        case 2 :    PORTB =0b1101101; break;
        case 3 :    PORTB =0b1111001; break;
        case 4 :    PORTB =0b0110011; break;
        case 5 :    PORTB =0b1011011; break;
        case 6 :    PORTB =0b1011111; break;
        case 7 :    PORTB =0b1110000; break;
        case 8 :    PORTB =0b1111111; break;
        case 9 :    PORTB =0b1111011; break;
        default : ;
    }    

}