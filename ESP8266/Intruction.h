#pragma once

#include <string>


enum FormatType;
class Format;
class Method;

class Intruction {
public:
	Intruction(std::string name, uint32_t opcode, uint32_t mask, FormatType format);

	Intruction(std::string name, uint32_t opcode, uint32_t mask, FormatType format, Method* method);

	bool Match(uint32_t op);

	std::string _name;
	uint32_t _opcode;
	uint32_t _mask;
	Format* _format;
	FormatType _type;
	Method* _method;
};