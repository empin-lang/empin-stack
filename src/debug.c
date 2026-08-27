#include <stdio.h>

#include "debug.h"
#include "value.h"

static epssize_t simple_instruction(const char *name, epssize_t offset)
{
	printf("%s\n", name);
	return offset + 1;
}
static epssize_t empin_constant_instruction(const char *name, EmpinChunk *chunk,
	epssize_t offset)
{
	EmpinSlot constant = chunk->code[offset+1];
	printf("%-16s %4d", name, constant);
	EmpinValue_print(chunk->constants.values[constant]);
	printf("\n");
	return offset + 2;
}

void empin_disassemble_EmpinChunk(EmpinChunk *self, const char *name)
{
	printf("== %s == \n", name);

	for (epssize_t offset = 0;offset < self->size;)
	{
		offset = empin_disassemble_instruction(self, offset);
	}
}

epssize_t empin_disassemble_instruction(EmpinChunk *self, epssize_t offset)
{
	printf("%04lld ", offset);

	EmpinSlot instruction = self->code[offset];

	switch (instruction)
	{
		case OP_CONSTANT:
			return empin_constant_instruction("OP_CONSTANT", self, offset); 
		case OP_HALT:
			return simple_instruction("OP_HALT", offset);
		default:
			printf("Unknown opcode %u\n", instruction);
			return offset + 1;
	}
}
