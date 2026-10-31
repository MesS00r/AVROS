#ifndef F_CPU
    #define F_CPU 16000000UL
#endif

#undef BAUD
#define BAUD 9600

#include <avr/io.h>
#include <util/delay.h>

#include <uprint.h>

int main (void) {
    ubegin();

    uputs("Hello World!\r\n");

    return 0;
}