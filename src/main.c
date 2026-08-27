#include <stdio.h>
#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, char *argv[])
{
	EmpinChunk chunk;
	EmpinChunk_init(&chunk);
	
	epssize_t constant = EmpinChunk_add_constant(&chunk, 1);
	EmpinChunk_write(&chunk, OP_CONSTANT);
	EmpinChunk_write(&chunk, (EmpinSlot) constant);
	EmpinChunk_write(&chunk, OP_HALT);
	empin_disassemble_EmpinChunk(&chunk, "test chunk");
	EmpinChunk_destroy(&chunk);
	return 0;
}
