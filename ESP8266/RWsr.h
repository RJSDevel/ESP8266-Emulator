#pragma once
#include "Method.h"
#include "Memory\Register.h"


enum Mode
{
	READ,
	WRITE
};

class RWsr : public Method
{
public:
	RWsr(Mode mode);
	RWsr(Register<int32_t>& sr, Mode mode);

	virtual void Execute(Command* cmd, CPU8266* cpu);
private:
	Mode _mode;
	Register<int32_t>* _sr;
};

