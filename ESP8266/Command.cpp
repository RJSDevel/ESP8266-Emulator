#pragma once

#include <vector>

#include "CPU8266.h"
#include "Command.h"
#include "Method.h"


Command::Command(uint32_t address, int op, Intruction* inst) 
{
	_address = address;
	_op = op;
	_inst = inst;
}

void Command::Parse()
{
	if (_inst->_type != NONE && _inst->_type != NNONE)
	{
		Format* format = _inst->_format;
		for (std::vector<Operand*>::iterator it = format->_operands.begin(); it != format->_operands.end(); ++it) {
			_values.push_back(std::pair<Operand*, OperandValue*>((*it), (*it)->Parse(this)));
		}
	}
}

void Command::Execute(CPU8266* cpu)
{
	if (_inst->_method)
	{
		if (cpu->pc == 0x40001081)
		{
			cin.get();
		}
		_inst->_method->Execute(this, cpu);
	}
	else
	{
		cout << "ATTENTION! - CALL DID NOT SET METHOD: " << _inst->_name << endl;
	}
}
