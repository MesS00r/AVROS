#include "cpu_switch.h"

tcb_t   tasks[MAX_TASKS] __attribute__((used)) = {0};
uint8_t current_task     __attribute__((used)) = 0;

void task_create(uint8_t id, uint8_t *stack, void (*foo)(void)) {
    if (stack == NULL) return;
    if (id >= MAX_TASKS) return;

    cli();

    uint16_t old_stack = SP;
    SP = (uint16_t)(stack + STACK_SIZE);

    asm volatile (
        "push %0            \n\t"
        "push %1            \n\t"
        "push r0            \n\t"
        "in   r16, __SREG__ \n\t"
        "ori  r16, 0x08     \n\t"
        "mov  r0, r16       \n\t"
        "push r0            \n\t"
        "push r1            \n\t"
        "clr  r1            \n\t"
        
        "push r2            \n\t"
        "push r3            \n\t"
        "push r4            \n\t"
        "push r5            \n\t"
        "push r6            \n\t"
        "push r7            \n\t"
        "push r8            \n\t"
        "push r9            \n\t"
        "push r10           \n\t"
        "push r11           \n\t"
        "push r12           \n\t"
        "push r13           \n\t"
        "push r14           \n\t"
        "push r15           \n\t"
        "push r16           \n\t"
        "push r17           \n\t"
        "push r18           \n\t"
        "push r19           \n\t"
        "push r20           \n\t"
        "push r21           \n\t"
        "push r22           \n\t"
        "push r23           \n\t"
        "push r24           \n\t"
        "push r25           \n\t"
        "push r26           \n\t"
        "push r27           \n\t"
        "push r28           \n\t"
        "push r29           \n\t"
        "push r30           \n\t"
        "push r31           \n\t"
        ::  "r" ((uint8_t)((uint16_t)foo & 0xFF)),
            "r" ((uint8_t)((uint16_t)foo >> 8))
    );

    tasks[id].stack_ptr = SP;
    tasks[id].state     = 1;
    SP                  = old_stack;

    sei();
}

ISR(TIMER1_COMPA_vect, ISR_NAKED) {
    asm volatile (
        "push r0           \n\t"
        "in   r0, __SREG__ \n\t"
        "push r0           \n\t"
        "push r1           \n\t"
        "clr  r1           \n\t"
        
        "push r2           \n\t"
        "push r3           \n\t"
        "push r4           \n\t"
        "push r5           \n\t"
        "push r6           \n\t"
        "push r7           \n\t"
        "push r8           \n\t"
        "push r9           \n\t"
        "push r10          \n\t"
        "push r11          \n\t"
        "push r12          \n\t"
        "push r13          \n\t"
        "push r14          \n\t"
        "push r15          \n\t"
        "push r16          \n\t"
        "push r17          \n\t"
        "push r18          \n\t"
        "push r19          \n\t"
        "push r20          \n\t"
        "push r21          \n\t"
        "push r22          \n\t"
        "push r23          \n\t"
        "push r24          \n\t"
        "push r25          \n\t"
        "push r26          \n\t"
        "push r27          \n\t"
        "push r28          \n\t"
        "push r29          \n\t"
        "push r30          \n\t"
        "push r31          \n\t"
    );

    asm volatile (
        "lds  r30, current_task  \n\t"
        "ldi  r31, 0             \n\t"
        "lsl  r30                \n\t"
        "lsl  r30                \n\t"
        "subi r30, lo8(-(tasks)) \n\t"
        "sbci r31, hi8(-(tasks)) \n\t"
        "in   r0, __SP_L__       \n\t"
        "st   Z+, r0             \n\t"
        "in   r0, __SP_H__       \n\t"
        "st   Z, r0              \n\t"
    );

    asm volatile (
        "lds  r30, current_task \n\t"
        "inc  r30               \n\t"
        "andi r30, %0           \n\t"
        "sts  current_task, r30 \n\t"
        :: "i" (MAX_TASKS_MASK) : "r30"
    );

    asm volatile (
        "lds  r30, current_task  \n\t"
        "ldi  r31, 0             \n\t"
        "lsl  r30                \n\t"
        "lsl  r30                \n\t"
        "subi r30, lo8(-(tasks)) \n\t"
        "sbci r31, hi8(-(tasks)) \n\t"
        "ld   r0, Z+             \n\t"
        "out  __SP_L__, r0       \n\t"
        "ld   r0, Z              \n\t"
        "out  __SP_H__, r0       \n\t"
    );

    asm volatile (
        "pop r31          \n\t"
        "pop r30          \n\t"
        "pop r29          \n\t"
        "pop r28          \n\t"
        "pop r27          \n\t"
        "pop r26          \n\t"
        "pop r25          \n\t"
        "pop r24          \n\t"
        "pop r23          \n\t"
        "pop r22          \n\t"
        "pop r21          \n\t"
        "pop r20          \n\t"
        "pop r19          \n\t"
        "pop r18          \n\t"
        "pop r17          \n\t"
        "pop r16          \n\t"
        "pop r15          \n\t"
        "pop r14          \n\t"
        "pop r13          \n\t"
        "pop r12          \n\t"
        "pop r11          \n\t"
        "pop r10          \n\t"
        "pop r9           \n\t"
        "pop r8           \n\t"
        "pop r7           \n\t"
        "pop r6           \n\t"
        "pop r5           \n\t"
        "pop r4           \n\t"
        "pop r3           \n\t"
        "pop r2           \n\t"
        "pop r1           \n\t"
        "pop r0           \n\t"

        "out __SREG__, r0 \n\t"
        "pop r0           \n\t"
        "reti             \n\t"
    );
}

void tcb_init(void) {
    OCR1A  = 15;
    TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
    TIMSK1 |= (1 << OCIE1A);
}

void os_start(void) {
    cli();

    SP           = tasks[0].stack_ptr;
    current_task = 0;

    asm volatile (
        "pop r31          \n\t"
        "pop r30          \n\t"
        "pop r29          \n\t"
        "pop r28          \n\t"
        "pop r27          \n\t"
        "pop r26          \n\t"
        "pop r25          \n\t"
        "pop r24          \n\t"
        "pop r23          \n\t"
        "pop r22          \n\t"
        "pop r21          \n\t"
        "pop r20          \n\t"
        "pop r19          \n\t"
        "pop r18          \n\t"
        "pop r17          \n\t"
        "pop r16          \n\t"
        "pop r15          \n\t"
        "pop r14          \n\t"
        "pop r13          \n\t"
        "pop r12          \n\t"
        "pop r11          \n\t"
        "pop r10          \n\t"
        "pop r9           \n\t"
        "pop r8           \n\t"
        "pop r7           \n\t"
        "pop r6           \n\t"
        "pop r5           \n\t"
        "pop r4           \n\t"
        "pop r3           \n\t"
        "pop r2           \n\t"
        "pop r1           \n\t"
        "pop r0           \n\t"

        "out __SREG__, r0 \n\t"
        "pop r0           \n\t"
        "reti             \n\t"
    );
}