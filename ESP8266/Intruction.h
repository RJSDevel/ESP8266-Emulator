#pragma once

#include <string>


enum FormatType;
class Format;
class Method;

class Intruction {
public:
	Intruction(std::string name, int opcode, int mask, FormatType format);

	Intruction(std::string name, int opcode, int mask, FormatType format, Method* method);

	bool Match(int op);

	std::string _name;
	int _opcode;
	int _mask;
	Format* _format;
	FormatType _type;
	Method* _method;
};