#pragma once

#include <cstdint>
#include "./../Loader/FirmwareImage.h"

class Memory
{
public:
	Memory(Segment* segment);

	Memory(uint32_t offset, uint32_t size);

	~Memory();

	uint32_t _offset;
	uint32_t _size;
	char* _data;
};

