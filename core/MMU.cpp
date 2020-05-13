#include "MMU.h"

#include <iostream>


MMU::MMU(FirmwareImage* image)
{
	std::vector<shared_ptr<Segment>> segments = image->GetSegments();

	for (std::vector<shared_ptr<Segment>>::iterator it = segments.begin(); it != segments.end(); ++it) {
		_memory.push_back(new Memory((*it).get()));
	}

	_memory.push_back(new Memory(0x3FFE8000, 0x4000)); // dram0
	_memory.push_back(new Memory(0x3FFC0000, 0x20000)); // uint32 mapping to the address it is located at. What is this?
	_memory.push_back(new Memory(0x40200000, 0x100000)); // SPI Flash is mapped here.
}

MMU::~MMU()
{
}

void MMU::Store8(uint32_t address, char value) {

	cout << hex << "store8( address = " << address << ", value = " << value << " )" << endl;

	for (std::vector<Memory*>::iterator it = _memory.begin(); it != _memory.end(); ++it) {
		if ((*it)->_offset <= address && (*it)->_offset + (*it)->_size >= address)
		{
			memcpy((*it)->_data + (address - (*it)->_offset), &value, sizeof(value));
			return;
		}
	}

	cout << "store ERROR!!! - " << address << endl;
}

void MMU::Store16(uint32_t address, short value) {

	cout << hex << "store16( address = " << address << ", value = " << value << " )" << endl;

	for (std::vector<Memory*>::iterator it = _memory.begin(); it != _memory.end(); ++it) {
		if ((*it)->_offset <= address && (*it)->_offset + (*it)->_size >= address)
		{
			memcpy((*it)->_data + (address - (*it)->_offset), &value, sizeof(value));
			return;
		}
	}

	cout << "store ERROR!!! - " << address << endl;
}

void MMU::Store32(uint32_t address, int value) {

	cout << hex << "store32( address = " << address << ", value = " << value << " )" << endl;

	for (std::vector<Memory*>::iterator it = _memory.begin(); it != _memory.end(); ++it) {
		if ((*it)->_offset <= address && (*it)->_offset + (*it)->_size >= address)
		{
			memcpy((*it)->_data + (address - (*it)->_offset), &value, sizeof(value));
			return;
		}
	}

	cout << "store ERROR!!! - " << address << endl;
}

char MMU::Load8(uint32_t address) {
	char value;

	for (std::vector<Memory*>::iterator it = _memory.begin(); it != _memory.end(); ++it) {
		if ((*it)->_offset <= address && (*it)->_offset + (*it)->_size >= address)
		{
			memcpy(&value, (*it)->_data + (address - (*it)->_offset), sizeof(value));
			return value;
		}
	}

	cout << "load8 ERROR!!! - " << address << endl;

	return 0xDE;
}

short MMU::Load16(uint32_t address) {
	short value;

	for (std::vector<Memory*>::iterator it = _memory.begin(); it != _memory.end(); ++it) {
		if ((*it)->_offset <= address && (*it)->_offset + (*it)->_size >= address)
		{
			memcpy(&value, (*it)->_data + (address - (*it)->_offset), sizeof(value));
			cout << hex << "load16( address = " << address << ", value = " << value << " )" << endl;
			return value;
		}
	}

	cout << "load16 ERROR!!! - " << address << endl;

	return 0xDEAD;
}

int MMU::Load32(uint32_t address) {
	int value;

	for (std::vector<Memory*>::iterator it = _memory.begin(); it != _memory.end(); ++it) {
		if ((*it)->_offset <= address && (*it)->_offset + (*it)->_size >= address)
		{
			memcpy(&value, (*it)->_data + (address - (*it)->_offset), sizeof(value));
			//cout << hex << "load32( address = " << address << ", value = " << value << " )" << endl;
			return value;
		}
	}

	cout << "load32 ERROR!!! - " << address << endl;
	
	return 0xDEADDEAD;
}
