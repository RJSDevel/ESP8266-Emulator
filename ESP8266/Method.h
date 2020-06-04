#pragma once

#include "Command.h"

class CPU8266;


class Method
{
public:
	Method();
	~Method();

	virtual void Execute(Command* cmd, CPU8266* cpu);
};

