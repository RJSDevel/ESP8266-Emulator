#pragma once


class Command;


enum OperandType
{
	REGISTER,
	IMMEDIATE,		// literal, const
	MEMORY,
	RELATIVE_PC,		// PC Relative address 
	RELATIVE_SHIFT_PC,	// PC Relative address shift
	NO_SIGNEXT_RELATIVE_PC,	// Хуй знает
	MEMORY_INDEX
};

class OperandValue {
public:
	union Value {
		char byte;
		short word;
		int dword;
	} value;

	uint32_t reg;
	uint32_t address;
};

class Operand
{
public:
	Operand();

	Operand(OperandType type, int size);

	Operand(OperandType type, int size, int rshift);

	Operand(OperandType type, int size, int rshift, int(*xlate)(int));

	Operand(OperandType type, int size, int rshift, int vshift);

	Operand(OperandType type, int size, int rshift, int vshift, int regbase[2]);

	Operand(OperandType type, int size, int rshift, bool signext);

	Operand(OperandType type, int size, int rshift, short off);

	Operand(OperandType type, int size, int rshift, bool signext, int vshift);

	Operand(OperandType type, int size, int rshift, int size2, int rshift2);

	Operand(OperandType type, int size, int rshift, int size2, int rshift2, int(*xlate)(int));

	OperandValue* Parse(Command* cmd);

	OperandType _type;

private:
	int _size = 0;
	int _rshift = 0;
	int _rshift2 = 0;
	int _size2 = 0;
	int _vshift = 0;
	bool _signext = false;
	int(*_xlate)(int) = nullptr;
	int *_regbase = nullptr;
	short _off = 0;

	int bitfield(int op, int size, int rshift);
};