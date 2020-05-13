#include "Intruction.h"
#include "Format.h"
#include "Method.h"


Intruction::Intruction(std::string name, int opcode, int mask, FormatType format) {
	_name = name;
	_opcode = opcode;
	_mask = mask;
	_type = format;
	_format = &FORMATS[format];
}

Intruction::Intruction(std::string name, int opcode, int mask, FormatType format, Method* method) : Intruction(name, opcode, mask, format)
{
	_method = method;
}

bool Intruction::Match(int op) {
	return (op & _mask) == _opcode;
}