#ifndef CPU_SWITCH_H
#define CPU_SWITCH_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stddef.h>

#define MAX_TASKS      4
#define MAX_TASKS_MASK 3
#define STACK_SIZE     128

typedef struct {
    uint16_t stack_ptr;
    uint8_t  state; // TODO
} __attribute__((aligned(4))) tcb_t;

_Static_assert(sizeof(tcb_t) == 4, "tcb_t must be 4 bytes");

extern tcb_t   tasks[MAX_TASKS];
extern uint8_t current_task;

void task_create(uint8_t id, uint8_t *stack, void (*foo)(void));
void tcb_init(void);
void os_start(void);

#endif // CPU_SWITCH_H