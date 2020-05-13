#pragma once
#include "Method.h"

class CPU8266;


class Abs : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Add : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Addi : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Addmi : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Addin : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Addx2 : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Addx4 : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Addx8 : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class And : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Ball : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Bany: public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Bbc : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Bbs : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Bbci : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Bbsi : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Beq : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Beqi : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Beqz : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Bge : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Bgei : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Bgeu : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Bgeui : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Bgez : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Blt : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Blti : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Bltu : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Bltui : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Bltz : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Bnall : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Bnone : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Bne : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Bnei : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Bnez : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Break : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Breakn : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Call0 : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Callx0 : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Jmp : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Extui : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};


class Movi : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Or : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class L32i : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class L32r : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Moveqz : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};


class S32i : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Srli : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Slli : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Srl : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Ssa8l : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

class Sub : public Method
{
public:
	virtual void Execute(Command* cmd, CPU8266* cpu);
};

