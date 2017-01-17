#ifndef _RK6502_H_
#define _RK6502_H_

typedef enum {
	IMPLIED,
	IMMEDIATE,
	ZP,
	ZPX,
	ZPY,
	IZP,
	IZPX,
	IZPY,
	RELATIVE,
	ABSOLUTE,
	ABSOLUTEX,
	ABSOLUTEY,
	IABSOLUTE,
	IABSOLUTEX
} addressing_t;

typedef enum {
	STOPPED,
	RUNNIG,
	STEPPING
} emu_state_t;

struct reg_state {
	uint8_t A;      /* accumulator */
	uint8_t X;      /* index X */
	uint8_t Y;      /* index Y */

	uint16_t PC;    /* program counter */
	uint8_t SP;     /* stack pointer */
	uint8_t P;      /* status */
};

typedef struct reg_state reg_state_t;

struct instrdef {
        uint8_t opcode;
	const char *mnemonic;
	addressing_t mode;
	uint8_t size;
};

typedef struct instrdef instrdef_t;

struct instruction {
	uint8_t opcode;
	instrdef_t def;
	uint8_t op1;
	uint8_t op2;
};

typedef struct instruction instruction_t;

struct rk65c02emu {
	emu_state_t state;
	bus_t bus;
	reg_state_t regs;
}

typedef struct rk65c02emu rk65c02emu_t;

#define OP_BRK 0x00
#define OP_TSB_ZP 0x04
#define OP_JSR 0x20
#define OP_LDY_IMM 0xA0
#define OP_STP 0xDB
#define OP_INX 0xE8
#define OP_NOP 0xEA

#define OP_UNIMPL 0xFF

const struct instrdef instrs[] = {
	{	OP_BRK, "brk", IMPLIED, 1 },
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_NOP, "nop", IMMEDIATE, 2},	/* inv */
	{	OP_NOP, "nop", IMPLIED, 1},	/* inv */
	{	OP_TSB_ZP, "tsb", ZP, 2},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_JSR, "jsr", ABSOLUTE, 3},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_LDY_IMM, "ldy", IMMEDIATE, 2},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_STP, "stp", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_INX, "inx", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_NOP, "nop", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpl", IMPLIED, 1},
	{	OP_UNIMPL, "unimpllast", IMPLIED, 1}
};


#endif /* _RK6502_H_ */

