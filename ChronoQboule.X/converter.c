
#include <stdio.h>
#include <stdlib.h>
#include <p18f25k80.h>
#include "converter.h"

#define SegmentA PORTCbits.RC1
#define SegmentB PORTCbits.RC2
#define SegmentC PORTCbits.RC3
#define SegmentD PORTCbits.RC4
#define SegmentE PORTCbits.RC5
#define SegmentF PORTCbits.RC6
#define SegmentG PORTCbits.RC7

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


    switch (figure) {
        case 0:
            SegmentA = 0;
            SegmentB = 0;
            SegmentC = 0;
            SegmentD = 0;
            SegmentE = 0;
            SegmentF = 0;
            SegmentG = 1;
            break;

        case 1:
            SegmentA = 1;
            SegmentB = 0;
            SegmentC = 0;
            SegmentD = 1;
            SegmentE = 1;
            SegmentF = 1;
            SegmentG = 1;
            break;
        case 2:
            SegmentA = 0;
            SegmentB = 0;
            SegmentC = 1;
            SegmentD = 0;
            SegmentE = 0;
            SegmentF = 1;
            SegmentG = 0;
            break;
        case 3:
            SegmentA = 0;
            SegmentB = 0;
            SegmentC = 0;
            SegmentD = 0;
            SegmentE = 1;
            SegmentF = 1;
            SegmentG = 0;
            break;

        case 4:
            SegmentA = 1;
            SegmentB = 0;
            SegmentC = 0;
            SegmentD = 1;
            SegmentE = 1;
            SegmentF = 0;
            SegmentG = 0;
            break;
        case 5: 
            SegmentA = 0;
            SegmentB = 1;
            SegmentC = 0;
            SegmentD = 0;
            SegmentE = 1;
            SegmentF = 0;
            SegmentG = 0;

            break;
        case 6:
            SegmentA = 0;
            SegmentB = 1;
            SegmentC = 0;
            SegmentD = 0;
            SegmentE = 0;
            SegmentF = 0;
            SegmentG = 0;
            break;

        case 7:
            SegmentA = 0;
            SegmentB = 0;
            SegmentC = 0;
            SegmentD = 1;
            SegmentE = 1;
            SegmentF = 1;
            SegmentG = 1;
            break;
        case 8:
            SegmentA = 0;
            SegmentB = 0;
            SegmentC = 0;
            SegmentD = 0;
            SegmentE = 0;
            SegmentF = 0;
            SegmentG = 0;
            break;
        case 9:
            SegmentA = 0;
            SegmentB = 0;
            SegmentC = 0;
            SegmentD = 0;
            SegmentE = 1;
            SegmentF = 0;
            SegmentG = 0;
            break;
        default:;
    }

}
