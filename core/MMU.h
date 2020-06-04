#pragma once
#include <cstdint>
#include <vector>

#include "Memory\Memory.h"

class MMU
{
public:
	MMU();
	~MMU();

	void AddRegion(Memory* memory);

	void Store8(uint32_t address, char value);

	void Store16(uint32_t address, short value);

	void Store32(uint32_t address, int value);

	int8_t Load8(uint32_t address);

	int16_t Load16(uint32_t address);

	int32_t Load32(uint32_t address);

private:
	Memory* FindRegion(uint32_t address);
};

