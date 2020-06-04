#pragma once


class Command;


enum OperandType
{
	REGISTER,
	IMMEDIATE,		// literal, const
	MEMORY,
	RELATIVE_PC,		// PC Relative address 
	RELATIVE_SHIFT_PC,	// PC Relative address shift
	UNSIGN_RELATIVE_PC,	// Хуй знает
	MEMORY_INDEX
};

class OperandValue {
public:
	union Value {
		int8_t byte;
		int16_t word;
		int32_t dword;
	} value;

	uint32_t reg;
	int32_t address;
};

class Operand
{
public:
	Operand();

	Operand(OperandType type, int32_t size);

	Operand(OperandType type, int32_t size, int32_t rshift);

	Operand(OperandType type, int32_t size, int32_t rshift, int32_t(*xlate)(int32_t));

	Operand(OperandType type, int32_t size, int32_t rshift, int32_t vshift);

	Operand(OperandType type, int32_t size, int32_t rshift, int32_t vshift, int32_t regbase[2]);

	Operand(OperandType type, int32_t size, int32_t rshift, bool signext);

	Operand(OperandType type, int32_t size, int32_t rshift, short off);

	Operand(OperandType type, int32_t size, int32_t rshift, bool signext, int32_t vshift);

	Operand(OperandType type, int32_t size, int32_t rshift, int32_t size2, int32_t rshift2);

	Operand(OperandType type, int32_t size, int32_t rshift, int32_t size2, int32_t rshift2, int32_t(*xlate)(int32_t));

	OperandValue* Parse(Command* cmd);

	OperandType _type;

private:
	int32_t _size = 0;
	int32_t _rshift = 0;
	int32_t _rshift2 = 0;
	int32_t _size2 = 0;
	int32_t _vshift = 0;
	bool _signext = false;
	int32_t(*_xlate)(int32_t) = nullptr;
	int32_t *_regbase = nullptr;
	short _off = 0;

	int32_t bitfield(int32_t op, int32_t size, int32_t rshift);
};