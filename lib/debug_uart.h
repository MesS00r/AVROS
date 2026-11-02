#ifndef DEBUG_UART_H
#define DEBUG_UART_H

#ifndef DEBUG
    #define DEBUG 1
#endif

#ifndef BAUD
    #define BAUD 115200
#endif

#if (DEBUG != 0)

    #define UBRR ((F_CPU / (8UL * BAUD)) - 1UL)

    #include <avr/sfr_defs.h>
    #include <avr/io.h>
    #include <util/delay.h>

    void debug_ubegin(void);
    void debug_uputc(char ch);
    void debug_uputs(const char str[static 1]);

#else

    #define debug_ubegin()   do {} while(0)
    #define debug_uputc(ch)  do {} while(0)
    #define debug_uputs(str) do {} while(0)

#endif

#endif // DEBUG_UART_H