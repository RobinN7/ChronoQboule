
#include <stdio.h>
#include <stdlib.h>
#include <p18f25k80.h>
#include "converter.h"

void segments(char figure) {

/*
    0= a b c d e f .                     a
    1= . b c . . . .                __________
    2= a b . d e . g               /         /
    3= a b c d . . g          f   /         /  b
    4= . b c . . f g             /_________/
    5= a . c d . f g            /    g    /
    6= a . c d e f g       e   /         /  c
    7= a b c . . . .          /_________/
    8= a b c d e f g 
    9= a b c d . f g               d
*/
            
switch(figure)
    {
        case 0 :    PORTC =0b1111110; break;
        case 1 :    PORTC =0b0110000; break;
        case 2 :    PORTC =0b1101101; break;
        case 3 :    PORTC =0b1111001; break;
        case 4 :    PORTC =0b0110011; break;
        case 5 :    PORTC =0b1011011; break;
        case 6 :    PORTC =0b1011111; break;
        case 7 :    PORTC =0b1110000; break;
        case 8 :    PORTC =0b1111111; break;
        case 9 :    PORTC =0b1111011; break;
        default : ;
    }    

}
