#pragma once

#include <vector>
#include <utility>

#include "Intruction.h"
#include "Format.h"
#include "Operand.h"

class CPU8266;

class Command {
public:
	Command(uint32_t address, int op, Intruction* inst);

	void Parse();

	void Execute(CPU8266* cpu);

	int _address;
	int _op;
	Intruction* _inst;
	std::vector<std::pair<Operand*, OperandValue*>> _values;
};
