#pragma once

#include <algorithm> 

#include "Operand.h"
#include "Command.h"


Operand::Operand()
{
}

Operand::Operand(OperandType type, int32_t size)
{
	_type = type;
	_size = size;
}

Operand::Operand(OperandType type, int32_t size, int32_t rshift) : Operand(type, size)
{
	_rshift = rshift;
}

Operand::Operand(OperandType type, int32_t size, int32_t rshift, int32_t(*xlate)(int32_t)) : Operand(type, size, rshift)
{
	_xlate = xlate;
}

Operand::Operand(OperandType type, int32_t size, int32_t rshift, int32_t vshift) : Operand(type, size, rshift)
{
	_vshift = vshift;
}

Operand::Operand(OperandType type, int32_t size, int32_t rshift, int32_t vshift, int32_t regbase[2]) : Operand(type, size, rshift)
{
	_vshift = vshift;
	_regbase = regbase;
}

Operand::Operand(OperandType type, int32_t size, int32_t rshift, bool signext) : Operand(type, size, rshift)
{
	_signext = signext;
}

Operand::Operand(OperandType type, int32_t size, int32_t rshift, short off) : Operand(type, size, rshift)
{
	_off = off;
}

Operand::Operand(OperandType type, int32_t size, int32_t rshift, bool signext, int32_t vshift) : Operand(type, size, rshift, signext)
{
	_vshift = vshift;
}

Operand::Operand(OperandType type, int32_t size, int32_t rshift, int32_t size2, int32_t rshift2) : Operand(type, size, rshift)
{
	_size2 = size2;
	_rshift2 = rshift2;
}

Operand::Operand(OperandType type, int32_t size, int32_t rshift, int32_t size2, int32_t rshift2, int32_t(*xlate)(int32_t)) : Operand(type, size, rshift, size2, rshift2)
{
	_xlate = xlate;
}

int32_t Operand::bitfield(int32_t op, int32_t size, int32_t rshift) {
	int32_t val = (op >> rshift) & (0xffffffff >> (32 - size));
	return val;
}

OperandValue* Operand::Parse(Command* cmd) {
	int32_t val = bitfield(cmd->_op, _size, _rshift);

	if (_size2) {
		val |= bitfield(cmd->_op, _size2, _rshift2) << _size;
	}

	if (!_signext)
	{
		switch (_type) {
			case RELATIVE_PC:
			case RELATIVE_SHIFT_PC:
			case MEMORY:
				_signext = true;
				break;
		}
	}

	if (_signext && (val & (1 << (_size + _size2 - 1)))) {
		val = -(~val & ((1 << (_size + _size2 - 1)) - 1)) - 1;
	}

	val <<= _vshift;
	val += _off;

	if (_xlate)
	{
		val = _xlate(val);
	}

	OperandValue* value = new OperandValue();

	switch (_type)
	{
	case REGISTER:
		value->reg = std::min(val, 15);
		break;
	case IMMEDIATE:
		value->value.dword = val;
		break;
	case MEMORY:
		if (val < 0)
		{
			value->address = (cmd->_address + 3 + (val << 2)) & 0xfffffffc;
		}
		else
		{
			value->address = (cmd->_address + 3 + (val << 2) - 0x40000) & 0xfffffffc;
		}
		break;
	case MEMORY_INDEX:
		value->reg = bitfield(cmd->_op, _regbase[0], _regbase[1]);
		value->address = val;
		break;
	case RELATIVE_PC:
	case UNSIGN_RELATIVE_PC:
		value->address = val + cmd->_address + 4;
		break;
	case RELATIVE_SHIFT_PC:
		value->address = (cmd->_address & 0xfffffffc) + 4 + (val << 2);
		break;
	}
	
	return value;
}
