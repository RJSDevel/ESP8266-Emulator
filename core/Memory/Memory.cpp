#include "Memory.h"

#include <iostream>

using namespace std;


class MemoryImpl : public Memory {
private:
	string _name;
	uint32_t _address;
	uint32_t _size;
	char* _data;
	Memory* _mapping;
	uint32_t _offset;
public:
	MemoryImpl::MemoryImpl(const string name, uint32_t address, uint32_t size) : Memory() {
		_name = name;
		_address = address;
		_size = size;
		_data = new char[size];
		memset(_data, 0, size);
	}

	MemoryImpl(const string name, uint32_t address, Memory* mapping, uint32_t offset) : Memory() {
		_name = name;
		_address = address;
		_mapping = mapping;
		_offset = offset;
	}

	MemoryImpl(const string name, uint32_t address, char* data, uint32_t size) : Memory() {
		_name = name;
		_address = address;
		_size = size;
		_data = new char[_size];
		memcpy_s(_data, _size, data, size);
	}

	~MemoryImpl() {
		delete[] _data;
	}

	virtual void Write8(uint32_t address, int8_t value) {
		memcpy(_data + address, &value, sizeof(value));
	}

	virtual void Writ16(uint32_t address, int16_t value) {
		memcpy(_data + address, &value, sizeof(value));
	}

	virtual void Write32(uint32_t address, int32_t value) {
		memcpy(_data + address, &value, sizeof(value));
	}

	virtual int8_t Read8(uint32_t address) {
		int8_t value;
		memcpy(&value, _data + address, sizeof(value));
		return value;
	}

	virtual int16_t Read16(uint32_t address) {
		int16_t value;
		memcpy(&value, _data + address, sizeof(value));
		return value;
	}

	virtual int32_t Read32(uint32_t address) {
		int32_t value;
		memcpy(&value, _data + address, sizeof(value));
		return value;
	}

	virtual string GetName() const
	{
		return _name;
	}

	virtual uint32_t GetAddress() const
	{
		return _address;
	}

	virtual uint32_t GetSize() const
	{
		return _size;
	}
};


Memory::Memory() {
	_impl = this;
}


Memory::Memory(const string name, uint32_t address, uint32_t size)
{
	_impl = new MemoryImpl(name, address, size);
}

Memory::Memory(const string name, uint32_t address, Memory* mapping, uint32_t offset)
{
	_impl = new MemoryImpl(name, address, mapping, offset);
}

Memory::Memory(const string name, uint32_t address, char* data, uint32_t size)
{
	_impl = new MemoryImpl(name, address, data, size);
}

Memory::~Memory()
{
	delete _impl;
}

void Memory::Write8(uint32_t address, int8_t value)
{
	if (_impl != NULL && _impl != this)
	{
		_impl->Write8(address, value);
	}
}

void Memory::Write16(uint32_t address, int16_t value)
{
	if (_impl != NULL && _impl != this)
	{
		_impl->Write16(address, value);
	}
}

void Memory::Write32(uint32_t address, int32_t value)
{
	if (_impl != NULL && _impl != this)
	{
		_impl->Write32(address, value);
	}
}

int8_t Memory::Read8(uint32_t address)
{
	if (_impl != NULL && _impl != this)
	{
		return _impl->Read8(address);
	}

	return -1;
}

int16_t Memory::Read16(uint32_t address)
{
	if (_impl != NULL && _impl != this)
	{
		return _impl->Read16(address);
	}

	return -1;
}

int32_t Memory::Read32(uint32_t address)
{
	if (_impl != NULL && _impl != this)
	{
		return _impl->Read32(address);
	}

	return -1;
}

string Memory::GetName() const
{
	if (_impl != NULL && _impl != this)
	{
		return _impl->GetName();
	}

	return "Wrong";
}

uint32_t Memory::GetAddress() const
{
	if (_impl != NULL && _impl != this)
	{
		return _impl->GetAddress();
	}

	return -1;
}

uint32_t Memory::GetSize() const
{
	if (_impl != NULL && _impl != this)
	{
		return _impl->GetSize();
	}

	return -1;
}