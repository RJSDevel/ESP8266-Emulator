#pragma once

#include <cstdint>
#include <string>

using namespace std;


class Memory
{
protected:
	Memory();

	Memory* _impl;
public:
	Memory(const string name, uint32_t address, uint32_t size);

	Memory(const string name, uint32_t address, Memory* mapping, uint32_t offset);

	Memory(const string name, uint32_t address, char* data, uint32_t size);

	~Memory();

	virtual void Write8(uint32_t address, int8_t value);

	virtual void Write16(uint32_t address, int16_t value);

	virtual void Write32(uint32_t address, int32_t value);

	virtual int8_t Read8(uint32_t address);

	virtual int16_t Read16(uint32_t address);

	virtual int32_t Read32(uint32_t address);

	virtual string GetName() const;

	virtual uint32_t GetAddress() const;

	virtual uint32_t GetSize() const;
};

