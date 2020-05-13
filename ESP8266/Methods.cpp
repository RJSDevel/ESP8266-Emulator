#include "Methods.h"
#include "CPU8266.h"
#include <cmath>

using namespace std;


void Abs::Execute(Command* cmd, CPU8266* cpu)
{
	Register<uint32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<uint32_t>& at = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	ar = abs(at);
}

void Add::Execute(Command* cmd, CPU8266* cpu)
{
	Register<uint32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<uint32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	Register<uint32_t>& at = cpu->REGISTERS[cmd->_values.at(2).second->reg];
	ar = as + at;
}

void Addi::Execute(Command* cmd, CPU8266* cpu)
{
	Register<uint32_t>& at = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<uint32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	uint32_t imm = 0x000000FF & cmd->_values.at(2).second->value.byte;
	at = as + imm;
}

void Addin::Execute(Command* cmd, CPU8266* cpu)
{
	Register<uint32_t>& at = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<uint32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	uint32_t imm = cmd->_values.at(2).second->value.byte;
	at = as + imm;
}

void Addmi::Execute(Command* cmd, CPU8266* cpu)
{
	Register<uint32_t>& at = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<uint32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	at = as + cmd->_values.at(2).second->value.byte;
}

void Addx2::Execute(Command* cmd, CPU8266* cpu)
{
	Register<uint32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<uint32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	Register<uint32_t>& at = cpu->REGISTERS[cmd->_values.at(2).second->reg];
	ar = (as << 1) + at;
}

void Addx4::Execute(Command* cmd, CPU8266* cpu)
{
	Register<uint32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<uint32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	Register<uint32_t>& at = cpu->REGISTERS[cmd->_values.at(2).second->reg];
	ar = (as << 2) + at;
}

void Addx8::Execute(Command* cmd, CPU8266* cpu)
{
	Register<uint32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<uint32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	Register<uint32_t>& at = cpu->REGISTERS[cmd->_values.at(2).second->reg];
	ar = (as << 3) + at;
}

void And::Execute(Command* cmd, CPU8266* cpu)
{
	Register<uint32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<uint32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	Register<uint32_t>& at = cpu->REGISTERS[cmd->_values.at(2).second->reg];
	ar = as & at;
}

void Ball::Execute(Command* cmd, CPU8266* cpu)
{
	Register<uint32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<uint32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	int label = cmd->_values.at(2).second->address;

	if ((~ar & as) == 0)
	{
		uint32_t nextPC = cpu->pc + 4;
		cpu->pc = cpu->pc + label;
		cpu->REGISTERS[0] = nextPC;
	}
}

void Bany::Execute(Command* cmd, CPU8266* cpu)
{
	Register<uint32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<uint32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	int label = cmd->_values.at(2).second->address;

	if (ar & as)
	{
		uint32_t nextPC = cpu->pc + 4;
		cpu->pc = cpu->pc + label;
		cpu->REGISTERS[0] = nextPC;
	}
}

void Bbc::Execute(Command* cmd, CPU8266* cpu)
{
	cout << "NOT IMPLEMENTED " << "Bbc" << endl;

	Register<uint32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<uint32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	int label = cmd->_values.at(2).second->address;

	//if (ar & as)
	//{
	//	uint32_t nextPC = cpu->pc + 4;
	//	cpu->pc = cpu->pc + label;
	//	cpu->REGISTERS[0] = nextPC;
	//}
}

void Bbci::Execute(Command* cmd, CPU8266* cpu)
{
	cout << "NOT IMPLEMENTED " << "Bbci" << endl;

	Register<uint32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<uint32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	int label = cmd->_values.at(2).second->address;

	//if (ar & as)
	//{
	//	uint32_t nextPC = cpu->pc + 4;
	//	cpu->pc = cpu->pc + label;
	//	cpu->REGISTERS[0] = nextPC;
	//}
}

void Bbs::Execute(Command* cmd, CPU8266* cpu)
{
	cout << "NOT IMPLEMENTED " << "Bbs" << endl;

	Register<uint32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<uint32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	int label = cmd->_values.at(2).second->address;

	//if (ar & as)
	//{
	//	uint32_t nextPC = cpu->pc + 4;
	//	cpu->pc = cpu->pc + label;
	//	cpu->REGISTERS[0] = nextPC;
	//}
}

void Bbsi::Execute(Command* cmd, CPU8266* cpu)
{
	cout << "NOT IMPLEMENTED " << "Bbsi" << endl;

	Register<uint32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<uint32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	int label = cmd->_values.at(2).second->address;

	//if (ar & as)
	//{
	//	uint32_t nextPC = cpu->pc + 4;
	//	cpu->pc = cpu->pc + label;
	//	cpu->REGISTERS[0] = nextPC;
	//}
}


void Beq::Execute(Command * cmd, CPU8266 * cpu)
{
	Register<uint32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<uint32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];

	if (ar == as)
	{
		int label = cmd->_values.at(2).second->address;
		cpu->pc = label;
	}
}

void Beqi::Execute(Command * cmd, CPU8266 * cpu)
{
	cout << "NOT IMPLEMENTED " << "Beqi" << endl;
}

void Beqz::Execute(Command * cmd, CPU8266 * cpu)
{
	cout << "NOT IMPLEMENTED " << "Beqz" << endl;
}

void Bge::Execute(Command * cmd, CPU8266 * cpu)
{
	cout << "NOT IMPLEMENTED " << "Bge" << endl;
}

void Bgei::Execute(Command * cmd, CPU8266 * cpu)
{
	cout << "NOT IMPLEMENTED " << "Bgei" << endl;
}

void Bgeu::Execute(Command * cmd, CPU8266 * cpu)
{
	cout << "NOT IMPLEMENTED " << "Bgeu" << endl;
}

void Bgeui::Execute(Command * cmd, CPU8266 * cpu)
{
	cout << "NOT IMPLEMENTED " << "Bgeui" << endl;
}

void Bgez::Execute(Command * cmd, CPU8266 * cpu)
{
	cout << "NOT IMPLEMENTED " << "Bgez" << endl;
}

void Blt::Execute(Command * cmd, CPU8266 * cpu)
{
	cout << "NOT IMPLEMENTED " << "Blt" << endl;
}

void Blti::Execute(Command * cmd, CPU8266 * cpu)
{
	cout << "NOT IMPLEMENTED " << "Blti" << endl;
}

void Bltu::Execute(Command * cmd, CPU8266 * cpu)
{
	cout << "NOT IMPLEMENTED " << "Bltu" << endl;
}

void Bltui::Execute(Command * cmd, CPU8266 * cpu)
{
	cout << "NOT IMPLEMENTED " << "Bltui" << endl;
}

void Bltz::Execute(Command * cmd, CPU8266 * cpu)
{
	cout << "NOT IMPLEMENTED " << "Bltz" << endl;
}

void Bnall::Execute(Command * cmd, CPU8266 * cpu)
{
	cout << "NOT IMPLEMENTED " << "Bnall" << endl;
}

void Bnone::Execute(Command * cmd, CPU8266 * cpu)
{
	cout << "NOT IMPLEMENTED " << "Bnone" << endl;
}

void Bne::Execute(Command * cmd, CPU8266 * cpu)
{
	cout << "NOT IMPLEMENTED " << "Bne" << endl;
}

void Bnei::Execute(Command * cmd, CPU8266 * cpu)
{
	cout << "NOT IMPLEMENTED " << "Bnei" << endl;
}

void Bnez::Execute(Command * cmd, CPU8266 * cpu)
{
	Register<uint32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	if (ar != 0)
	{
		int offset = cmd->_values.at(0).second->value.dword;
		cpu->pc = cpu->pc + offset + 4;
	}
}

void Break::Execute(Command * cmd, CPU8266 * cpu)
{
	cout << "NOT IMPLEMENTED " << "Break" << endl;
}

void Breakn::Execute(Command * cmd, CPU8266 * cpu)
{
	cout << "NOT IMPLEMENTED " << "Breakn" << endl;
}

void Call0::Execute(Command* cmd, CPU8266* cpu)
{
	uint32_t nextPC = cpu->pc + 3;
	cpu->pc = cmd->_values.at(0).second->address;
	cpu->REGISTERS[0] = nextPC;

	cout << "CALL0 =  " << (int)cpu->pc << endl << endl;
}

void Callx0::Execute(Command* cmd, CPU8266* cpu)
{
	uint32_t nextPC = cpu->pc + 3;
	cpu->pc = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	cpu->REGISTERS[0] = nextPC;

	cout << endl << endl;
}

void Jmp::Execute(Command* cmd, CPU8266* cpu)
{
	cpu->pc = cmd->_values.at(0).second->address;

	cout << endl << endl;
}

void Extui::Execute(Command * cmd, CPU8266 * cpu)
{
	Register<uint32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<uint32_t>& at = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	int shiftimm = cmd->_values.at(2).second->value.byte;
	int maskimm = cmd->_values.at(3).second->value.byte;
	ar = (at >> shiftimm) & maskimm;
}

void Movi::Execute(Command* cmd, CPU8266* cpu)
{
	Register<uint32_t>& a = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	a = cmd->_values.at(1).second->value.dword;
}

void Or::Execute(Command* cmd, CPU8266* cpu)
{
	Register<uint32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<uint32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	Register<uint32_t>& at = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	ar = as | at;
}

void L32i::Execute(Command* cmd, CPU8266* cpu)
{
	Register<uint32_t>& at = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<uint32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	int offset = cmd->_values.at(1).second->value.dword;
	at = cpu->mmu->Load32(as + offset);
}

void L32r::Execute(Command* cmd, CPU8266* cpu)
{
	Register<uint32_t>& at = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	at = cpu->mmu->Load32(cmd->_values.at(1).second->address);
}

void Moveqz::Execute(Command* cmd, CPU8266* cpu)
{
	Register<uint32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<uint32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	Register<uint32_t>& at = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	if (at == 0)
	{
		ar = as;
	}
}

void S32i::Execute(Command* cmd, CPU8266* cpu)
{
	Register<uint32_t>& at = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<uint32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	uint32_t offset = cmd->_values.at(1).second->address;
	cpu->mmu->Store32(cpu->pc + as + offset, at);
}

void Srli::Execute(Command* cmd, CPU8266* cpu)
{
	Register<uint32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<uint32_t>& at = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	uint32_t sa = cmd->_values.at(2).second->value.dword;
	ar = at >> sa;
}

void Slli::Execute(Command* cmd, CPU8266* cpu)
{
	Register<uint32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<uint32_t>& at = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	uint32_t sa = cmd->_values.at(2).second->value.dword;
	ar = at << sa;
}

void Srl::Execute(Command * cmd, CPU8266 * cpu)
{
	Register<uint32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<uint32_t>& at = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	ar = at >> cpu->sr.sar;
}

void Ssa8l::Execute(Command * cmd, CPU8266 * cpu)
{
	Register<uint32_t>& as = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	cpu->sr.sar = (as & 0b00000011) << 3;
}

void Sub::Execute(Command* cmd, CPU8266* cpu)
{
	Register<uint32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<uint32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	Register<uint32_t>& at = cpu->REGISTERS[cmd->_values.at(2).second->reg];
	ar = as - at;
}

