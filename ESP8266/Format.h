#pragma once

#include <vector>

#include "Operand.h"


enum FormatType
{
	NONE,
	NNONE,
	RRR,
	RRR_extui,
	RRR_1imm,
	RRR_2imm,
	RRR_immr,
	RRR_2r,
	RRR_2rr,
	RRR_sll,
	RRR_slli,
	RRR_srai,
	RRR_sh,
	RRR_ssa,
	RRR_ssai,
	RRI8,
	RRI8_addmi,
	RRI8_i12,
	RRI8_disp,
	RRI8_disp16,
	RRI8_disp32,
	RRI8_b,
	RRI8_bb,
	RI16,
	BRI8,
	BRI8_imm,
	BRI8_immu,
	BRI12,
	CALL,
	CALL_sh,
	CALLX,
	RSR,
	RSR_spec,
	RRRN,
	RRRN_addi,
	RRRN_2r,
	RRRN_disp,
	RI6,
	RI7,
};

class Format
{
public:
	Format();

	Format(int size);

	Format(int size, Operand* o1);

	Format(int size, Operand* o1, Operand* o2);

	Format(int size, Operand* o1, Operand* o2, Operand* o3);

	Format(int size, Operand* o1, Operand* o2, Operand* o3, Operand* o4);

	int GetSize();

	std::vector<Operand*> _operands;
private:
	int _size;
};


/*
These magic lookup tables are defined in table 3-17 and 3-18 (p.41-42) in Xtensa Instruction Set Architecture Reference Manual
*/
static int b4const(int val) {
	static int magic[] = { -1, 1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 16, 32, 64, 128, 256 };
	return magic[val];
}

static int b4constu(int val) {
	static int magic[] = { 32768, 65536, 2, 3, 4, 5, 6, 7, 8, 10, 12, 16, 32, 64, 128, 256 };
	return magic[val];
}

static int movi_n(int val) {
	return (val & 0x60) != 0x60 ? val : -(0x20 - val & 0x1f);
}

static int addin(int val) {
	return val ? val : -1;
}

static int shimm(int val) {
	return 32 - val;
}

static Format FORMATS[] = {
	/*NONE*/		Format(3),
	/*NNONE*/		Format(2),

	/*RRR*/			Format(3, new Operand(REGISTER, 4, 12), new Operand(REGISTER, 4, 8), new Operand(REGISTER, 4, 4)),
	/*RRR_extui*/	Format(3, new Operand(REGISTER, 4, 12), new Operand(REGISTER, 4, 4), new Operand(IMMEDIATE, 4, 8, 1, 16), new Operand(IMMEDIATE, 4, 20, (short)1)),
	/*RRR_1imm*/	Format(3, new Operand(IMMEDIATE, 4, 8)),
	/*RRR_2imm*/	Format(3, new Operand(IMMEDIATE, 4, 8), new Operand(IMMEDIATE, 4, 4)),
	/*RRR_immr*/	Format(3, new Operand(REGISTER, 4, 4), new Operand(IMMEDIATE, 4, 8)),
	/*RRR_2r*/		Format(3, new Operand(REGISTER, 4, 4), new Operand(REGISTER, 4, 8)),
	/*RRR_2rr*/		Format(3, new Operand(REGISTER, 4, 12), new Operand(REGISTER, 4, 4)),
	/*RRR_sll*/		Format(3, new Operand(REGISTER, 4, 12), new Operand(REGISTER, 4, 8)),
	/*RRR_slli*/	Format(3, new Operand(REGISTER, 4, 12), new Operand(REGISTER, 4, 8), new Operand(IMMEDIATE, 4, 4, 1, 20, shimm)),
	/*RRR_srai*/	Format(3, new Operand(REGISTER, 4, 12), new Operand(REGISTER, 4, 4), new Operand(IMMEDIATE, 4, 8, 1, 20)),
	/*RRR_sh*/		Format(3, new Operand(REGISTER, 4, 12), new Operand(REGISTER, 4, 4), new Operand(IMMEDIATE, 4, 8)),
	/*RRR_ssa*/		Format(3, new Operand(REGISTER, 4, 8)),
	/*RRR_ssai*/	Format(3, new Operand(REGISTER, 4, 8, 1, 4)),

	/*RRI8*/		Format(3, new Operand(REGISTER, 4, 4), new Operand(REGISTER, 4, 8), new Operand(IMMEDIATE, 8, 16, true)),
	/*RRI8_addmi*/	Format(3, new Operand(REGISTER, 4, 4), new Operand(REGISTER, 4, 8), new Operand(IMMEDIATE, 8, 16, true, 8)),
	/*RRI8_i12*/	Format(3, new Operand(REGISTER, 4, 4), new Operand(IMMEDIATE, 8, 16, 4, 8)),

	/*RRI8_disp*/	Format(3, new Operand(REGISTER, 4, 4), new Operand(MEMORY_INDEX, 8, 16, 0, new int[2]{ 4, 8 })),
	/*RRI8_disp16*/	Format(3, new Operand(REGISTER, 4, 4), new Operand(MEMORY_INDEX, 8, 16, 1, new int[2]{ 4, 8 })),
	/*RRI8_disp32*/	Format(3, new Operand(REGISTER, 4, 4), new Operand(MEMORY_INDEX, 8, 16, 2, new int[2]{ 4, 8 })),
	/*RRI8_b*/		Format(3, new Operand(REGISTER, 4, 8), new Operand(REGISTER, 4, 4), new Operand(RELATIVE_PC, 8, 16)),
	/*RRI8_bb*/		Format(3, new Operand(REGISTER, 4, 8), new Operand(IMMEDIATE, 4, 4, 1, 12), new Operand(RELATIVE_PC, 8, 16)),

	/*RI16*/		Format(3, new Operand(REGISTER, 4, 4), new Operand(MEMORY, 16, 8)),

	/*BRI8*/		Format(3, new Operand(REGISTER, 4, 12), new Operand(REGISTER, 4, 8), new Operand(RELATIVE_PC, 8, 16)),
	/*BRI8_imm*/	Format(3, new Operand(REGISTER, 4, 8), new Operand(IMMEDIATE, 4, 12, b4const), new Operand(RELATIVE_PC, 8, 16)),
	/*BRI8_immu*/	Format(3, new Operand(REGISTER, 4, 8), new Operand(IMMEDIATE, 4, 12, b4constu), new Operand(RELATIVE_PC, 8, 16)),

	/*BRI12*/		Format(3, new Operand(REGISTER, 4, 8), new Operand(RELATIVE_PC, 12, 12)),

	/*CALL*/		Format(3, new Operand(RELATIVE_PC, 18, 6)),
	/*CALL_sh*/		Format(3, new Operand(RELATIVE_SHIFT_PC, 18, 6)),
	/*CALLX*/		Format(3, new Operand(REGISTER, 4, 8)),

	/*RSR*/			Format(3, new Operand(IMMEDIATE, 8, 8), new Operand(REGISTER, 4, 4)),
	/*RSR_spec*/	Format(3, new Operand(REGISTER, 4, 4)),

	/*RRRN*/		Format(2, new Operand(REGISTER, 4, 12), new Operand(REGISTER, 4, 8), new Operand(REGISTER, 4, 4)),
	/*RRRN_addi*/	Format(2, new Operand(REGISTER, 4, 12), new Operand(REGISTER, 4, 8), new Operand(IMMEDIATE, 4, 4, addin)),
	/*RRRN_2r*/		Format(2, new Operand(REGISTER, 4, 4), new Operand(REGISTER, 4, 8)),
	/*RRRN_disp*/	Format(2, new Operand(REGISTER, 4, 4), new Operand(MEMORY_INDEX, 4, 12, 2, new int[2]{ 4, 8 })),

	/*RI6*/			Format(2, new Operand(REGISTER, 4, 8), new Operand(UNSIGN_RELATIVE_PC, 4, 12, 2, 4)),
	/*RI7*/			Format(2, new Operand(REGISTER, 4, 8), new Operand(IMMEDIATE, 4, 12, 3, 4, movi_n))
};

