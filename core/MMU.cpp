#include "MMU.h"

#include <iostream>
#include <string>

using namespace std;

std::vector<Memory*> _memory;


MMU::MMU()
{
}

MMU::~MMU()
{
}

void MMU::AddRegion(Memory * memory)
{
	_memory.push_back(memory);
}


Memory * MMU::FindRegion(uint32_t address)
{
	for (std::vector<Memory*>::iterator it = _memory.begin(); it != _memory.end(); ++it) {
		if (address >= (*it)->GetAddress() && address <= (*it)->GetAddress() + (*it)->GetSize())
		{
			return *it;
		}
	}

	return 0;
}

void MMU::Store8(uint32_t address, char value) {
	Memory* region = FindRegion(address);

	if (region != 0)
	{
		cout << endl << hex << "store8( " << region->GetName() << ", address = " << address << ", value = " << value << " )" << endl << endl;
		region->Write8(address - region->GetAddress(), value);
		return;
	}

	cout << endl << "store8 ERROR!!! - " << address << endl << endl;
}

void MMU::Store16(uint32_t address, short value) {
	Memory* region = FindRegion(address);

	if (region != 0)
	{
		cout << endl << hex << "store16( " << region->GetName() << ", address = " << address << ", value = " << value << " )" << endl << endl;
		region->Write16(address - region->GetAddress(), value);
		return;
	}

	cout << endl << "store16 ERROR!!! - " << address << endl << endl;
}

void MMU::Store32(uint32_t address, int value) {
	Memory* region = FindRegion(address);

	if (region != 0)
	{
		cout << endl << hex << "store32( " << region->GetName() << ", address = " << address << ", value = " << value << " )" << endl << endl;
		region->Write32(address - region->GetAddress(), value);
		return;
	}

	cout << endl << "store32 ERROR!!! - " << address << endl << endl;
}

int8_t MMU::Load8(uint32_t address) {

	Memory* region = FindRegion(address);
	if (region != 0)
	{
		return region->Read8(address - region->GetAddress());
	}

	cout << endl << "load8 ERROR!!! - " << address << endl << endl;

	return 0xFF;
}

int16_t MMU::Load16(uint32_t address) {

	Memory* region = FindRegion(address);
	if (region != 0)
	{
		int16_t value = region->Read16(address - region->GetAddress());
		cout << endl << hex << "load16( " << region->GetName() << ", address = " << address << ", value = " << value << " )" << endl << endl;
		return value;
	}
	
	cout << endl << "load16 ERROR!!! - " << address << endl << endl;

	return 0xFFFF;
}

int32_t MMU::Load32(uint32_t address) {
	
	Memory* region = FindRegion(address);
	if (region != 0)
	{
		int32_t value = region->Read32(address - region->GetAddress());

		cout << endl << hex << "load32( " << region->GetName() << ", address = " << address << ", value = " << value << " )" << endl << endl;

		return value;
	}

	cout << endl << "load32 ERROR!!! - " << address << endl << endl;
	
	return 0xFFFFFFFF;
}
