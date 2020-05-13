#include <stdio.h>
#include <iomanip>
#include <cstdint>

#include "CPU8266.h"


vector<Intruction> short_instr;
vector<Intruction> long_instr;

CPU8266::CPU8266()
{
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

bool CPU8266::Load(std::string imagefile)
{
	Loader<ESP8266Image>* loader = new Loader<ESP8266Image>(new ESP8266Image(), imagefile);

	mmu = new MMU(loader->GetImage());

	int entrypoint = loader->GetImage()->GetEntryPoint();
	pc = entrypoint;

	cout << "Entry point: " << hex << entrypoint << endl;

	return true;
}

Command* decode_cmd(MMU* mmu, Register<uint32_t> &pc) {
	unsigned char code1 = mmu->Load8(pc++);
	unsigned char code2 = mmu->Load8(pc++);

	int op = code1 | code2 << 8;

	for (vector<Intruction>::iterator it = short_instr.begin(); it != short_instr.end(); ++it) {
		if ((*it).Match(op))
		{
			return new Command(pc - 2, op, &(*it));
		}
	}

	unsigned char code3 = mmu->Load8(pc++);
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


bool CPU8266::Decode()
{
	while (true) {
		Command* cmd = decode_cmd(mmu, pc);

		if (cmd)
		{
			cmd->Parse();
			
			cout << hex << cmd->_address <<
				":  " << hex << setw(6) << left << cmd->_op <<
				"     " << cmd->_inst->_name << " ";

			if (cmd->_inst->_type != NONE)
			{
				unsigned int pos = 0;

				for (std::vector<std::pair<Operand*, OperandValue*>>::iterator it = cmd->_values.begin(); it != cmd->_values.end(); ++it) {
					char* end = ++pos < cmd->_values.size() ? ", " : "";

					switch (it->first->_type)
					{
					case REGISTER:
						cout << "a" << dec << it->second->reg << " - <" << hex << REGISTERS[it->second->reg] << ">" << end;
						break;
					case IMMEDIATE:
						cout << hex << "0x" << it->second->value.dword << end;
						break;
					case NO_SIGNEXT_RELATIVE_PC:
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

void CPU8266::Execute()
{

}



