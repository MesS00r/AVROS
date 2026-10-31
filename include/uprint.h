#ifndef UPRINT_H
#define UPRINT_H

#define BAUD 9600
#define UBRR ((F_CPU / (16UL * BAUD)) - 1UL)

#include <avr/sfr_defs.h>
#include <avr/io.h>
#include <util/delay.h>

void ubegin(void);
void uputc(char ch);
void uputs(const char str[static 1]);

#endif // UPRINT_H