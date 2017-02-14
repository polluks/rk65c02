#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include <assert.h>
#include <string.h>

#include "bus.h"
#include "instruction.h"
#include "rk65c02.h"
#include "debug.h"

void rk65c02_exec(rk65c02emu_t *);

/*
 * Prepare the emulator for use, set initial CPU state.
 */
rk65c02emu_t
rk65c02_init(bus_t *b)
{
	rk65c02emu_t e;

	e.bus = b;
	e.state = STOPPED;
	e.stopreason = HOST;
	e.regs.P = P_UNDEFINED|P_IRQ_DISABLE;
	/* reset also clears the decimal flag */
	e.regs.P &= ~P_DECIMAL;

	e.irq = false;

	e.bps_head = NULL;

	return e;
}

/*
 * Assert the IRQ line.
 */
void
rk65c02_assert_irq(rk65c02emu_t *e)
{
	/* 
	 * Clearly this is too simpleton'ish, because more than one device
	 * might want to assert the interrupt line (on hardware level it is
	 * active low, so can just be pulled down by any device connected
	 * to it.
	 */
	e->irq = true;

	if ((e->state == STOPPED) && (e->stopreason == WAI))
		rk65c02_start(e);
}

/*
 * Respond to interrupt and start the interrupt service routine.
 */
void
rk65c02_irq(rk65c02emu_t *e)
{
	/* push return address to the stack */
	stack_push(e, e->regs.PC >> 8);
	stack_push(e, e->regs.PC & 0xFF);
	/* push processor status to the stack with break flag set */
	stack_push(e, e->regs.P);

	/* 
	 * The IRQ disable is set, decimal flags is cleared _after_ pushing
	 * the P register to the stack.
	 */
	e->regs.P |= P_IRQ_DISABLE;
	e->regs.P &= ~P_DECIMAL;

	/* break flag is only saved to the stack, it is not present in the ISR... */
	e->regs.P &= ~P_BREAK;

	/* load address from IRQ vector into program counter */
	e->regs.PC = bus_read_1(e->bus, VECTOR_IRQ);
	e->regs.PC |= bus_read_1(e->bus, VECTOR_IRQ + 1) << 8;
}

/*
 * Execute a single instruction within emulator.
 */
void
rk65c02_exec(rk65c02emu_t *e)
{
	instruction_t i;
	instrdef_t id;

	if (e->irq && (!(e->regs.P & P_IRQ_DISABLE)))
		rk65c02_irq(e);

	/* XXX: handle watchpoints toos */
	if (debug_PC_is_breakpoint(e)) {
		e->state = STOPPED;
		e->stopreason = BREAKPOINT;
	}

	/* if disassembly-when-running enabled */
	disassemble(e->bus, e->regs.PC);

	i = instruction_fetch(e->bus, e->regs.PC);
	id = instruction_decode(i.opcode);

	if (id.emul != NULL) {
		id.emul(e, &id, &i);
		if (!instruction_modify_pc(&id)) 
			program_counter_increment(e, &id);
	} else {
		printf("unimplemented opcode %X @ %X\n", i.opcode,
		    e->regs.PC);
		e->state = STOPPED;
		e->stopreason = EMUERROR;
	}
}

/*
 * Start the emulator.
 */
void
rk65c02_start(rk65c02emu_t *e) {

	assert(e != NULL);

	e->state = RUNNING;
	while (e->state == RUNNING) {
		rk65c02_exec(e);
	}
}

/*
 * Execute as many instructions as specified in steps argument.
 */
void
rk65c02_step(rk65c02emu_t *e, uint16_t steps) {

	uint16_t i = 0;

	assert(e != NULL);

	e->state = STEPPING;
	while ((e->state == STEPPING) && (i < steps)) {
		rk65c02_exec(e);
		i++;
	}

	e->state = STOPPED;
	e->stopreason = STEPPED;
}

void
rk65c02_dump_stack(rk65c02emu_t *e, uint8_t n)
{
	uint16_t stackaddr;

	stackaddr = STACK_END-n;

	while (stackaddr <= STACK_END) {

		if ((stackaddr == STACK_END-n) || !((stackaddr % 0x10)))
			printf("stack %#02x: ", stackaddr);

		printf("%#02x ", bus_read_1(e->bus, stackaddr));

		stackaddr++;

		if (!(stackaddr % 0x10))
			printf("\n");
	}
}

void
rk65c02_dump_regs(rk65c02emu_t *e)
{
	printf("A: %X X: %X Y: %X PC: %X SP: %X P: ", 
	    e->regs.A, e->regs.X, e->regs.Y, e->regs.PC, e->regs.SP);

	if (e->regs.P & P_NEGATIVE)
		printf("N");
	else
		printf("-");

	if (e->regs.P & P_SIGN_OVERFLOW)
		printf("V");
	else
		printf("-");

	if (e->regs.P & P_UNDEFINED)
		printf("1");
	else
		printf("-");

	if (e->regs.P & P_BREAK)
		printf("B");
	else
		printf("-");

	if (e->regs.P & P_DECIMAL)
		printf("D");
	else
		printf("-");

	if (e->regs.P & P_IRQ_DISABLE)
		printf("I");
	else
		printf("-");

	if (e->regs.P & P_ZERO)
		printf("Z");
	else
		printf("-");

	if (e->regs.P & P_CARRY)
		printf("C");
	else
		printf("-");

	printf("\n");
}
/*
int
main(void)
{
	bus_t b;

	b = bus_init();

	bus_write_1(&b, 0, OP_INX);
	bus_write_1(&b, 1, OP_NOP);
	bus_write_1(&b, 2, OP_LDY_IMM);
	bus_write_1(&b, 3, 0x1);
	bus_write_1(&b, 4, OP_TSB_ZP);
	bus_write_1(&b, 5, 0x3);
	bus_write_1(&b, 6, OP_JSR);
	bus_write_1(&b, 7, 0x09);
	bus_write_1(&b, 8, 0x0);
	bus_write_1(&b, 9, OP_STP);

	rk6502_start(&b, 0);

	bus_finish(&b);
}
*/
