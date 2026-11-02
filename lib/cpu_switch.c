#include "cpu_switch.h"

// TODO: Обработчик прерываний
#if 0

void task_create(uint8_t id, uint8_t *stack, void (*foo)(void)) {
    SP = (uint16_t)(stack + STACK_SIZE);

    cli();

    asm volatile (
        ""
    );

    sei();

    tasks[id].stack_ptr = SP;
    tasks[id].state     = 1;
}

ISR(TIMER1_COMPA_vect, ISR_NAKED) {
    asm volatile (
        ""
    );
}

void os_start(void) {

}

#endif