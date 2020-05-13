#pragma once
#include <cstdint>
#include <vector>

#include "Loader\FirmwareImage.h"
#include "Memory\Memory.h"

class MMU
{
public:
	MMU(FirmwareImage* image);
	~MMU();

	void Store8(uint32_t address, char value);
	void Store16(uint32_t address, short value);
	void Store32(uint32_t address, int value);

	char Load8(uint32_t address);
	short Load16(uint32_t address);
	int Load32(uint32_t address);

private:
	std::vector<Memory*> _memory;
};

