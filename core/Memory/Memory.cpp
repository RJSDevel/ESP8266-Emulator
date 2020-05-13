#include "Memory.h"

Memory::Memory(Segment* segment)
{
	_offset = segment->GetOffset();
	_size = segment->GetSize();
	_data = new char[_size];
	memcpy_s(_data, _size, segment->_pointer, _size);
}

Memory::Memory(uint32_t offset, uint32_t size)
{
	_offset = offset;
	_size = size;
	_data = new char[size];
	memset(_data, 0, size);
}

Memory::~Memory()
{
}

