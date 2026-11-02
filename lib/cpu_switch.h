#ifndef DEBUG_UART_H
#define DEBUG_UART_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

// TODO: Обработчик прерываний
#if 0

#define MAX_TASKS  5
#define STACK_SIZE 64

typedef struct {
    uint16_t stack_ptr;
    uint8_t  state;
} tcb_t;

extern tcb_t tasks[MAX_TASKS];
extern uint8_t current_tasks;

void task_create(uint8_t id, uint8_t *stack, void (*foo)(void));
void os_start(void);

#endif

#endif