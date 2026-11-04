#include "debug_uart.h"

#if (DEBUG != 0)

void debug_ubegin(void) {
    UBRR0  = UBRR;
    UCSR0A |= (1 << U2X0);
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
}

void debug_uputc(char ch) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = ch;
}

void debug_uputs(const char *str) {
    if (str == NULL) return;

    char ch;
    while ((ch = *str++)) {
        debug_uputc(ch);
    }
}

#endif