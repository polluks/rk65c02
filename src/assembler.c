#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#include <assert.h>
#include <string.h>

#include <gc/gc.h>

#include "bus.h"
#include "rk65c02.h"
#include "log.h"
#include "assembler.h"
#include "instruction.h"

assembler_t
assemble_init(bus_t *b, uint16_t pc)
{
	assembler_t asmblr;

	asmblr.bus = b;
	asmblr.pc = pc;

	return asmblr;
}

bool
assemble_single_implied(assembler_t *a, char *mnemonic)
{
	return assemble_single(a, mnemonic, IMPLIED, 0, 0);
}

bool
assemble_single(assembler_t *a, char *mnemonic, addressing_t mode, uint8_t op1, uint8_t op2)
{
	uint8_t *asmbuf;
	uint8_t bsize;
	bool rv;

	rv = assemble_single_buf(&asmbuf, &bsize, mnemonic, mode, op1, op2);
	if (rv == false)
		return rv;

	rv = bus_load_buf(a->bus, a->pc, asmbuf, bsize);
	a->pc += bsize;

	return rv;
}

bool
assemble_single_buf_implied(uint8_t **buf, uint8_t *bsize, char *mnemonic)
{
	return assemble_single_buf(buf, bsize, mnemonic, IMPLIED, 0, 0);
}


bool
assemble_single_buf(uint8_t **buf, uint8_t *bsize, char *mnemonic, addressing_t mode, uint8_t op1, uint8_t op2)
{
	instrdef_t id;
	uint8_t opcode;
	bool found;

	opcode = 0;

	found = instruction_opcode_by_mnemonic(mnemonic, mode, &opcode, &id);

	if (!found) {
		rk65c02_log(LOG_ERROR,
		    "Couldn't find opcode for mnemonic %s mode %x.",
		    mnemonic, mode);
		return false;
	}

	*bsize = id.size;

	*buf = GC_MALLOC(id.size);
	assert(*buf != NULL);

	/* fill the buffer */
	memset(*buf, 0, id.size);
	(*buf)[0] = opcode;
	/* XXX */
	if (id.size > 1) 
		(*buf)[1] = op1;
	if (id.size > 2)
		(*buf)[2] = op2;

	return found;
}

