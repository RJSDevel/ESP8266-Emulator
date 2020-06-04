#include "Intruction.h"
#include "Format.h"
#include "Method.h"


Intruction::Intruction(std::string name, uint32_t opcode, uint32_t mask, FormatType format) {
	_name = name;
	_opcode = opcode;
	_mask = mask;
	_type = format;
	_format = &FORMATS[format];
}

Intruction::Intruction(std::string name, uint32_t opcode, uint32_t mask, FormatType format, Method* method) : Intruction(name, opcode, mask, format)
{
	_method = method;
}

bool Intruction::Match(uint32_t op) {
	return (op & _mask) == _opcode;
}