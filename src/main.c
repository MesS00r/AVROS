#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include <debug_uart.h>
#include <cpu_switch.h>

uint8_t stack0[STACK_SIZE];
uint8_t stack1[STACK_SIZE];
uint8_t stack2[STACK_SIZE];

void task0(void) {
    debug_uputs("FIN0\n");
    while (1);
}

void task1(void) {
    debug_uputs("FIN1\n");
    while (1);
}

void task2(void) {
    debug_uputs("FIN2\n");
    while (1);
}

int main (void) {
    debug_ubegin();
    tcb_init();

    task_create(0, stack0, task0);
    task_create(1, stack1, task1);
    task_create(2, stack2, task2);

    os_start();
    while(1);

    return 0;
}