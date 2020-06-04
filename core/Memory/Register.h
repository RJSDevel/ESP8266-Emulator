#pragma once

#include <iostream>
#include <cstring>

using namespace std;


template<typename T>
class Register
{
private:
	T _value = 0;
	string _name;

public:
	Register(int name): _name("a" + std::to_string(name))
	{
		
	}

	Register(string name) : _name(name)
	{

	}

	const Register<T>& operator = (int32_t other) {
		_value = other;
		return *this;
	}

	const Register<T>& operator = (Register<T>& other) {
		_value = other._value;
		return *this;
	}

	operator int() const
	{
		return _value;
	}
	
	const Register<T>& operator ++ () {
		_value++;
		return *this;
	}
	
	const int operator ++ (int) 
	{
		return _value++;
	}
	
	const Register<T>& operator -- () {
		_value--;
		return *this;
	}
	
	const Register<T>& operator -- (int) 
	{
		--_value;
		return *this;
	}
	
	const Register<T> & operator - (const Register<T> &other) 
	{
		_value -= other._value;
		return *this;
	}

	const uint32_t operator - (const int32_t other)
	{
		return _value - other;
	}

	const uint32_t operator |= (const int32_t other)
	{
		return _value |= other;
	}

	const uint32_t operator &= (const int32_t other)
	{
		return _value &= other;
	}
	
	friend ostream& operator << (ostream &s, const Register<T> &reg) 
	{
		int width = 8;
		if (reg._value <= 16)
		{
			width = 2;
		}
		else if (reg._value <= 65635)
		{
			width = 4;
		}
		return s << hex << "0x" << setfill('0') << setw(width) << right << reg._value;
	}
};