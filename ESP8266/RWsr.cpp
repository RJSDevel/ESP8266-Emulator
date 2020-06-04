#include "RWsr.h"

#include "CPU8266.h"

RWsr::RWsr(Mode mode) : _mode(mode)
{
}

RWsr::RWsr(Register<int32_t>& sr, Mode mode) : _sr(&sr), _mode(mode)
{
}

void RWsr::Execute(Command * cmd, CPU8266 * cpu)
{
	Register<int32_t>& sr = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	switch (_mode)
	{
	case READ:
		sr = *_sr;
		break;
	case WRITE:
		(*_sr) = sr;
		break;
	}
}
