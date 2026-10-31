#include "uprint.h"

void ubegin(void) {
    UBRR0  = UBRR;
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
}

void uputc(char ch) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = ch;
}

void uputs(const char str[static 1]) {
    char ch;
    while ((ch = *str)) {
        uputc(ch);
        str++;
    }
}