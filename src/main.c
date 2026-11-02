#ifndef F_CPU
    #define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#include <debug_uart.h>

int main (void) {
    debug_ubegin();

    debug_uputs("Hello World!\r\n");

    return 0;
}