#include <stdio.h>
#include <iomanip>
#include <cstdint>

#include <windows.h> 

#include "CPU8266.h"

namespace Color {
	enum Code {
		FG_RED		=	FOREGROUND_RED	 | FOREGROUND_INTENSITY,
		FG_GREEN	=	FOREGROUND_GREEN | FOREGROUND_INTENSITY,
		FG_BLUE		=	FOREGROUND_BLUE  | FG_GREEN,
		FG_YELLOW	=	FG_RED | FG_GREEN,
		FG_DEFAULT	=	FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		FG_GRAY		=	FOREGROUND_INTENSITY,
		BG_RED		=	BACKGROUND_RED,
		BG_GREEN	=	BACKGROUND_GREEN,
		BG_BLUE		=	BACKGROUND_BLUE,
		BG_DEFAULT	=	BACKGROUND_INTENSITY
	};
	class Modifier {
		Code code;
	public:
		Modifier(Code code) : code(code) {}
		friend std::ostream& operator<<(std::ostream& os, const Modifier& mod) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), mod.code);
			return os;
		}
	};
}

Color::Modifier red(Color::FG_RED);
Color::Modifier green(Color::FG_GREEN);
Color::Modifier yellow(Color::FG_YELLOW);
Color::Modifier blue(Color::FG_BLUE);
Color::Modifier gray(Color::FG_GRAY);
Color::Modifier white(Color::FG_DEFAULT);

vector<Intruction> short_instr;
vector<Intruction> long_instr;


CPU8266::CPU8266(MMU * mmu)
{
	this->mmu = mmu;

	int count = sizeof(INSRUCTIONS) / sizeof(*INSRUCTIONS);
	for (int index = 0; index < count; index++) {
		Intruction instruction = INSRUCTIONS[index];
		if (instruction._format->GetSize() == 3) {
			long_instr.push_back(instruction);
		}
		else
		{
			short_instr.push_back(instruction);
		}
	}
}

CPU8266::~CPU8266()
{
}

Command* decode_cmd(MMU* mmu, Register<uint32_t> &pc) {
	uint8_t code1 = mmu->Load8(pc++);
	uint8_t code2 = mmu->Load8(pc++);

	uint32_t op = code1 | code2 << 8;

	for (vector<Intruction>::iterator it = short_instr.begin(); it != short_instr.end(); ++it) {
		if ((*it).Match(op))
		{
			return new Command(pc - 2, op, &(*it));
		}
	}

	uint8_t code3 = mmu->Load8(pc++);
	op |= code3 << 16;

	for (vector<Intruction>::iterator it = long_instr.begin(); it != long_instr.end(); ++it) {
		if ((*it).Match(op))
		{
			return new Command(pc - 3, op, &(*it));
		}
	}

	cout << "Error op: " << hex << op << " - " << pc << endl;
	cin.get();

	return NULL;
}

bool CPU8266::Run(uint32_t entrypoint)
{
	pc = entrypoint;

	while (true) {
		Command* cmd = decode_cmd(mmu, pc);

		if (cmd)
		{
			cmd->Parse();
			
			cout << hex << gray << cmd->_address << ":  " << white
				<< hex << setfill(' ') << setw(6) << left << cmd->_op << "     ";

			switch (cmd->_inst->_type)
			{
				case CALL:
				case CALL_sh:
				case CALLX:
					if (cmd->_inst->_name == "call0" || cmd->_inst->_name == "callx0")
					{
						cout << blue;
						break;
					}
					else if (cmd->_inst->_name == "j" || cmd->_inst->_name == "jx")
					{
						cout << yellow;
						break;
					}

					cout << green;
					break;
				case RI6:
				case RRI8_b:
				case RRI8_bb:
				case BRI8_imm:
				case BRI12:
				case BRI8_immu:
					cout << yellow;
					break;
				case RRR_2imm:
				case RRRN:
					if (cmd->_inst->_name == "break" || cmd->_inst->_name == "break.n")
					{
						cout << red;
						break;
					}

					cout << green;
					break;
				case NONE:
				case NNONE:
					if (cmd->_inst->_name == "ret" || cmd->_inst->_name == "ret.n")
					{
						cout << red;
						break;
					}
					else if (cmd->_inst->_name == "nop" || cmd->_inst->_name == "nop.n")
					{
						cout << gray;
						break;
					}
				default:
					cout << green;
			}

			cout << cmd->_inst->_name << white << " ";

			if (cmd->_inst->_type != NONE)
			{
				unsigned int pos = 0;

				for (std::vector<std::pair<Operand*, OperandValue*>>::iterator it = cmd->_values.begin(); it != cmd->_values.end(); ++it) {
					char* end = ++pos < cmd->_values.size() ? ", " : "";

					switch (it->first->_type)
					{
					case REGISTER:
						cout << "a" << dec << it->second->reg << " - <" << hex << REGISTERS[it->second->reg] << ">" << white << end;
						break;
					case IMMEDIATE:
						cout << dec << it->second->value.dword << end;
						break;
					case UNSIGN_RELATIVE_PC:
					case RELATIVE_PC:
					case MEMORY:
						cout << hex << "0x" << it->second->address << end;
						break;
					case MEMORY_INDEX:
						cout << "a" << dec << it->second->reg << " - <" << hex << REGISTERS[it->second->reg] << ">, " << end;
						cout << hex << "0x" << it->second->address << end;
						break;
					case RELATIVE_SHIFT_PC:
						cout << hex << it->second->address << end;
						break;
					}
				}
			}
			cout << endl;

			cmd->Execute(this);
		}
		else {
			break;
		}
	}

	return false;
}



