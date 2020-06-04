#include "Methods.h"
#include "CPU8266.h"
#include <cmath>

#include <intrin.h>

using namespace std;


void Abs::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	ar = abs(at);
}

void Add::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(2).second->reg];
	ar = as + at;
}

void Addi::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	int32_t imm = cmd->_values.at(2).second->value.dword;
	at = as + imm;
}

void Addin::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	int32_t imm = cmd->_values.at(2).second->value.dword;
	at = as + imm;
}

void Addmi::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	at = as + cmd->_values.at(2).second->value.dword;
}

void Addx2::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(2).second->reg];
	ar = (as << 1) + at;
}

void Addx4::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(2).second->reg];
	ar = (as << 2) + at;
}

void Addx8::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(2).second->reg];
	ar = (as << 3) + at;
}

void And::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(2).second->reg];
	ar = as & at;
}

void Ball::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];


	if ((~ar & as) == 0)
	{
		uint32_t nextPC = cpu->pc;
		int label = cmd->_values.at(2).second->address;
		cpu->pc = label;
		cpu->REGISTERS[0] = nextPC;

		cout << endl << endl;
	}
}

void Bany::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];

	if (ar & as)
	{
		uint32_t nextPC = cpu->pc;
		int label = cmd->_values.at(2).second->address;
		cpu->pc = label;
		cpu->REGISTERS[0] = nextPC;

		cout << endl << endl;
	}
}

void Bbc::Execute(Command* cmd, CPU8266* cpu)
{
	cout << "NOT IMPLEMENTED " << "Bbc" << endl;

	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	int label = cmd->_values.at(2).second->address;

	cout << endl << endl;
}

void Bbci::Execute(Command* cmd, CPU8266* cpu)
{
	cout << "NOT IMPLEMENTED " << "Bbci" << endl;

	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	int label = cmd->_values.at(2).second->address;

	cout << endl << endl;
}

void Bbs::Execute(Command* cmd, CPU8266* cpu)
{
	cout << "NOT IMPLEMENTED " << "Bbs" << endl;

	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	int label = cmd->_values.at(2).second->address;

	cout << endl << endl;
}

void Bbsi::Execute(Command* cmd, CPU8266* cpu)
{
	cout << "NOT IMPLEMENTED " << "Bbsi" << endl;

	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	int label = cmd->_values.at(2).second->address;

	cout << endl << endl;
}


void Beq::Execute(Command * cmd, CPU8266 * cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];

	if (ar == as)
	{
		int label = cmd->_values.at(2).second->address;
		cpu->pc = label;

		cout << endl << endl;
	}
}

void Beqi::Execute(Command * cmd, CPU8266 * cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	int32_t imm = cmd->_values.at(1).second->value.dword;

	if (ar == imm)
	{
		int label = cmd->_values.at(2).second->address;
		cpu->pc = label;

		cout << endl << endl;
	}
}

void Beqz::Execute(Command * cmd, CPU8266 * cpu)
{
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(0).second->reg];

	if (as == 0)
	{
		int label = cmd->_values.at(1).second->address;
		cpu->pc = label;

		cout << endl << endl;
	}
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
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(1).second->reg];

	if (ar >= at)
	{
		int label = cmd->_values.at(2).second->address;
		cpu->pc = label;

		cout << endl << endl;
	}
}

void Bgeui::Execute(Command * cmd, CPU8266 * cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	int8_t imm = cmd->_values.at(1).second->value.byte;

	if (ar >= imm)
	{
		int label = cmd->_values.at(2).second->address;
		cpu->pc = label;

		cout << endl << endl;
	}
}

void Bgez::Execute(Command * cmd, CPU8266 * cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];

	if (ar >= 0)
	{
		int label = cmd->_values.at(1).second->address;
		cpu->pc = label;

		cout << endl << endl;
	}
}

void Blt::Execute(Command * cmd, CPU8266 * cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(1).second->reg];

	if (ar < at)
	{
		int label = cmd->_values.at(2).second->address;
		cpu->pc = label;

		cout << endl << endl;
	}
}

void Blti::Execute(Command * cmd, CPU8266 * cpu)
{
	cout << "NOT IMPLEMENTED " << "Blti" << endl;
}

void Bltu::Execute(Command * cmd, CPU8266 * cpu)
{
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(1).second->reg];

	if (as < at)
	{
		int label = cmd->_values.at(2).second->address;
		cpu->pc = label;

		cout << endl << endl;
	}
}

void Bltui::Execute(Command * cmd, CPU8266 * cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	int32_t r = cmd->_values.at(1).second->value.byte;

	if (ar < r)
	{
		int label = cmd->_values.at(2).second->address;
		cpu->pc = label;

		cout << endl << endl;
	}
}

void Bltz::Execute(Command * cmd, CPU8266 * cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];

	if (ar < 0)
	{
		int label = cmd->_values.at(1).second->address;
		cpu->pc = label;

		cout << endl << endl;
	}
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
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	int32_t imm = cmd->_values.at(1).second->value.dword;

	if (ar != imm)
	{
		int label = cmd->_values.at(2).second->address;
		cpu->pc = label;

		cout << endl << endl;
	}
}

void Bnez::Execute(Command * cmd, CPU8266 * cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	if (ar != 0)
	{
		int offset = cmd->_values.at(0).second->value.dword;
		cpu->pc = cpu->pc + offset;

		cout << endl << endl;
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
	uint32_t nextPC = cpu->pc;
	cpu->pc = cmd->_values.at(0).second->address;
	cpu->REGISTERS[0] = nextPC;

	cout << endl << endl;
}

void Callx0::Execute(Command* cmd, CPU8266* cpu)
{
	uint32_t nextPC = cpu->pc;
	cpu->pc = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	cpu->REGISTERS[0] = nextPC;

	cout << endl << endl;
}

void Jmp::Execute(Command* cmd, CPU8266* cpu)
{
	cpu->pc = cmd->_values.at(0).second->address;

	cout << endl << endl;
}

void L8ui::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	int32_t offset = cmd->_values.at(1).second->value.dword;
	at = cpu->mmu->Load8(as + offset);
}

void L16si::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	int32_t offset = cmd->_values.at(1).second->value.dword;
	at = cpu->mmu->Load16(as + offset);
}

void L16ui::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	int32_t offset = cmd->_values.at(1).second->value.dword;
	at = cpu->mmu->Load16(as + offset);
}

void Extui::Execute(Command * cmd, CPU8266 * cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	uint8_t shift = cmd->_values.at(2).second->value.byte;

	uint8_t mask = 0xFFFFFFFF >> (32 - cmd->_values.at(3).second->value.byte);

	ar = (at >> shift) & mask;
}

void Mov::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	ar = as;
}

void Movi::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& a = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	a = cmd->_values.at(1).second->value.dword;
}

void Or::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(2).second->reg];
	ar = as | at;
}

void Ret::Execute(Command* cmd, CPU8266* cpu)
{
	cpu->pc = cpu->REGISTERS[0];

	cout << endl << endl;
}

void Rsil::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	at = cpu->sr.ps;
	cpu->sr.ps |= cmd->_values.at(1).second->value.byte;
}

void L32i::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	int32_t offset = cmd->_values.at(1).second->address;
	at = cpu->mmu->Load32(as + offset);
}

void L32r::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	at = cpu->mmu->Load32(cmd->_values.at(1).second->address);
}

void Moveqz::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(2).second->reg];
	if (at == 0)
	{
		ar = as;
	}
}

void Movnez::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(2).second->reg];
	if (at != 0)
	{
		ar = as;
	}
}

void Mul16s::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(2).second->reg];
	ar = as * at;
}

void Mul16u::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(2).second->reg];
	ar = as * at;
}

void Mull::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(2).second->reg];
	ar = as * at;
}

void Nsau::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];

	if (as == 0)
	{
		at = 32;
	}
	else
	{
		at = __lzcnt(as);
	}
}

void S8i::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	int32_t offset = cmd->_values.at(1).second->address;
	cpu->mmu->Store8(as + offset, at);
}

void S16i::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	int32_t offset = cmd->_values.at(1).second->address;
	cpu->mmu->Store16(as + offset, at);
}

void S32i::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	int32_t offset = cmd->_values.at(1).second->address;
	cpu->mmu->Store32(as + offset, at);
}

void Srli::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	int32_t sa = cmd->_values.at(2).second->value.dword;
	ar = at >> sa;
}

void Sll::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	ar = at << cpu->sr.sarbc();
}

void Slli::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	int32_t sa = cmd->_values.at(2).second->value.dword;
	ar = at << sa;
}

void Srl::Execute(Command * cmd, CPU8266 * cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	ar = at >> cpu->sr.sarbc();
}

void Ssa8l::Execute(Command * cmd, CPU8266 * cpu)
{
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	cpu->sr.sar = (as & 0b00000011) << 3;
}

void Ssl::Execute(Command * cmd, CPU8266 * cpu)
{
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	int8_t sa = as & 0x0F;
	cpu->sr.sar = 32 - sa;
}

void Ssr::Execute(Command * cmd, CPU8266 * cpu)
{
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	int8_t sa = as & 0x0F;
	cpu->sr.sar = sa;
}

void Sub::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(2).second->reg];
	ar = as - at;
}

void Waiti::Execute(Command* cmd, CPU8266* cpu)
{
	cout << "Waiti";
	cin.get();
}

void Xor::Execute(Command* cmd, CPU8266* cpu)
{
	Register<int32_t>& ar = cpu->REGISTERS[cmd->_values.at(0).second->reg];
	Register<int32_t>& as = cpu->REGISTERS[cmd->_values.at(1).second->reg];
	Register<int32_t>& at = cpu->REGISTERS[cmd->_values.at(2).second->reg];
	ar = as ^ at;
}
