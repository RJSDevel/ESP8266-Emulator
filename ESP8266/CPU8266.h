#pragma once

#include <algorithm> 
#include <cstring>

#include "CPU/CPU.h"
#include "Loader/Loader.h"

#include "Memory/Register.h"
#include "Intruction.h"
#include "Command.h"
#include "Format.h"
#include "Method.h"
#include "Methods.h"
#include "RWsr.h"
#include "MMU.h"


class CPU8266: public CPU {

private:
	Method* add = new Add();
	Method* addmi = new Addmi();
	Method* call0 = new Call0();
	Method* callx = new Callx0();
	Method* l32r = new L32r();
	Method* l32i = new L32i();
	Method* s32i = new S32i();
	Method* movi = new Movi();
	
	Method* beqz = new Beqz();
	Method* bnez = new Bnez();

	Method* ret = new Ret();

public:
	struct
	{
		Register<int32_t> EPC[7] = {
			Register<int32_t>("epc1"),
			Register<int32_t>("epc2"),
			Register<int32_t>("epc3"),
			Register<int32_t>("epc4"),
			Register<int32_t>("epc5"),
			Register<int32_t>("epc6"),
			Register<int32_t>("epc7")
		};

		Register<int32_t>& ps = Register<int32_t>("ps");

		Register<int32_t>& exccause = Register<int32_t>("exccause");
		Register<int32_t>& ccount = Register<int32_t>("ccount");
		Register<int32_t>& excvaddr = Register<int32_t>("excvaddr");
		Register<int32_t>& depc = Register<int32_t>("depc");
		Register<int32_t>& prid = Register<int32_t>("prid");
		Register<int32_t>& ccompare0 = Register<int32_t>("ccompare0");
		Register<int32_t>& interrupt = Register<int32_t>("interrupt");
		Register<int32_t>& intenable = Register<int32_t>("intenable");

		Register<int32_t>& litbase = Register<int32_t>("litbase");
		Register<int32_t>& vecbase = Register<int32_t>("vecbase");
		Register<int32_t>& intclear = Register<int32_t>("intclear");

		Register<int32_t>& sar = Register<int32_t>("sar");
		Register<int32_t>& ddr = Register<int32_t>("ddr");

		int8_t sarbc() { // SAR set bits 
			return sar - ((sar >> 1) & 0x55555555);
		}
	} sr;

	Intruction INSRUCTIONS[131] = {
		/*         name      opcode    mask      format          */
		Intruction("abs",	 0x600100, 0xff0f0f, RRR_2rr, new Abs),
		Intruction("add",    0x800000, 0xff000f, RRR, add),
		Intruction("addi",   0x00c002, 0x00f00f, RRI8, new Addi),
		Intruction("addmi",  0x00d002, 0x00f00f, RRI8_addmi, addmi),
		Intruction("addx2",  0x900000, 0xff000f, RRR, new Addx2),
		Intruction("addx4",  0xa00000, 0xff000f, RRR, new Addx4),
		Intruction("addx8",  0xb00000, 0xff000f, RRR, new Addx8),
		Intruction("and",    0x100000, 0xff000f, RRR, new And),
		Intruction("ball",   0x004007, 0x00f00f, RRI8_b, new Ball),
		Intruction("bany",   0x008007, 0x00f00f, RRI8_b, new Bany),
		Intruction("bbc",    0x005007, 0x00f00f, RRI8_b, new Bbc),
		Intruction("bbs",    0x00d007, 0x00f00f, RRI8_b, new Bbs),
		Intruction("bbci",   0x006007, 0x00e00f, RRI8_bb, new Bbci),
		Intruction("bbsi",   0x00e007, 0x00e00f, RRI8_bb, new Bbsi),
		Intruction("beq",    0x001007, 0x00f00f, RRI8_b, new Beq),
		Intruction("beqi",   0x000026, 0x0000ff, BRI8_imm, new Beqi),
		Intruction("beqz",   0x000016, 0x0000ff, BRI12, beqz),
		Intruction("bge",    0x00a007, 0x00f00f, RRI8_b, new Bge),
		Intruction("bgei",   0x0000e6, 0x0000ff, BRI8_imm, new Bgei),
		Intruction("bgeu",   0x00b007, 0x00f00f, RRI8_b, new Bgeu),
		Intruction("bgeui",  0x0000f6, 0x0000ff, BRI8_immu, new Bgeui),
		Intruction("bgez",   0x0000d6, 0x0000ff, BRI12, new Bgez),
		Intruction("blt",    0x002007, 0x00f00f, RRI8_b, new Blt),
		Intruction("blti",   0x0000a6, 0x0000ff, BRI8_imm, new Blti),
		Intruction("bltu",   0x003007, 0x00f00f, RRI8_b, new Bltu),
		Intruction("bltui",  0x0000b6, 0x0000ff, BRI8_immu, new Bltui),
		Intruction("bltz",   0x000096, 0x0000ff, BRI12, new Bltz),
		Intruction("bnall",  0x00c007, 0x00f00f, RRI8_b, new Bnall),
		Intruction("bnone",  0x000007, 0x00f00f, RRI8_b, new Bnone),
		Intruction("bne",    0x009007, 0x00f00f, RRI8_b, new Bne),
		Intruction("bnei",   0x000066, 0x0000ff, BRI8_imm, new Bnei),
		Intruction("bnez",   0x000056, 0x0000ff, BRI12, bnez),
		Intruction("break",  0x004000, 0xfff00f, RRR_2imm, new Break),

		Intruction("call0",  0x000005, 0x00003f, CALL_sh, call0),
		Intruction("callx0", 0x0000c0, 0xfff0ff, CALLX, callx),
		Intruction("dsync",  0x002030, 0xffffff, NONE),
		Intruction("esync",  0x002020, 0xffffff, NONE),
		Intruction("extui",  0x040000, 0x0e000f, RRR_extui, new Extui),
		Intruction("extw",   0x0020d0, 0xffffff, NONE),
		Intruction("isync",  0x002000, 0xffffff, NONE),
		Intruction("ill",    0x000000, 0xffffff, NONE),
		Intruction("j",      0x000006, 0x00003f, CALL, new Jmp),
		Intruction("jx",     0x0000a0, 0xfff0ff, CALLX, callx),

		Intruction("l8ui",   0x000002, 0x00f00f, RRI8_disp, new L8ui),
		Intruction("l16si",  0x009002, 0x00f00f, RRI8_disp16, new L16si),
		Intruction("l16ui",  0x001002, 0x00f00f, RRI8_disp16, new L16ui),
		Intruction("l32i",   0x002002, 0x00f00f, RRI8_disp32, l32i),
		Intruction("l32r",   0x000001, 0x00000f, RI16, l32r),
		Intruction("memw",   0x0020c0, 0xffffff, NONE),
		Intruction("moveqz", 0x830000, 0xff000f, RRR, new Moveqz),
		Intruction("movgez", 0xb30000, 0xff000f, RRR),
		Intruction("movi",   0x00a002, 0x00f00f, RRI8_i12, movi),
		Intruction("movltz", 0xa30000, 0xff000f, RRR),
		Intruction("movnez", 0x930000, 0xff000f, RRR, new Movnez),
		Intruction("mul16s", 0xd10000, 0xff000f, RRR, new Mul16s),
		Intruction("mul16u", 0xc10000, 0xff000f, RRR, new Mul16u),
		Intruction("mull",   0x820000, 0xff000f, RRR, new Mull),
		Intruction("neg",    0x600000, 0xff0f0f, RRR_2rr),
		Intruction("nsa",    0x40e000, 0xfff00f, RRR_2r),
		Intruction("nsau",   0x40f000, 0xfff00f, RRR_2r, new Nsau),
		Intruction("nop",    0x0020f0, 0xffffff, NONE),
		Intruction("or",     0x200000, 0xff000f, RRR, new Or),
		Intruction("ret",    0x000080, 0xffffff, NONE, ret),
		Intruction("rfe",    0x003000, 0xffffff, NONE),
		Intruction("rfi",    0x003010, 0xfff0ff, RRR_1imm),
		Intruction("rsil",   0x006000, 0xfff00f, RRR_immr, new Rsil),
		Intruction("rsr.epc1",      0x03b100, 0xffff0f, RSR_spec, new RWsr(sr.EPC[0], READ)),
		Intruction("rsr.epc2",      0x03b200, 0xffff0f, RSR_spec, new RWsr(sr.EPC[1], READ)),
		Intruction("rsr.epc3",      0x03b300, 0xffff0f, RSR_spec, new RWsr(sr.EPC[2], READ)),
		Intruction("rsr.epc4",      0x03b400, 0xffff0f, RSR_spec, new RWsr(sr.EPC[3], READ)),
		Intruction("rsr.epc5",      0x03b500, 0xffff0f, RSR_spec, new RWsr(sr.EPC[4], READ)),
		Intruction("rsr.epc6",      0x03b600, 0xffff0f, RSR_spec, new RWsr(sr.EPC[5], READ)),
		Intruction("rsr.epc7",      0x03b700, 0xffff0f, RSR_spec, new RWsr(sr.EPC[6], READ)),
		Intruction("rsr.ps",        0x03e600, 0xffff0f, RSR_spec, new RWsr(sr.ps, READ)),
		Intruction("rsr.exccause",  0x03e800, 0xffff0f, RSR_spec, new RWsr(sr.exccause, READ)),
		Intruction("rsr.ccount",    0x03e400, 0xffff0f, RSR_spec, new RWsr(sr.ccount, READ)),
		Intruction("rsr.excvaddr",  0x03ee00, 0xffff0f, RSR_spec, new RWsr(sr.excvaddr, READ)),
		Intruction("rsr.depc",      0x03c000, 0xffff0f, RSR_spec, new RWsr(sr.depc, READ)),
		Intruction("rsr.prid",      0x03eb00, 0xffff0f, RSR_spec, new RWsr(sr.prid, READ)),
		Intruction("rsr.ccompare0", 0x03f000, 0xffff0f, RSR_spec, new RWsr(sr.ccompare0, READ)),
		Intruction("rsr.interrupt", 0x03e200, 0xffff0f, RSR_spec, new RWsr(sr.interrupt, READ)),
		Intruction("rsr.intenable", 0x03e400, 0xffff0f, RSR_spec, new RWsr(sr.intenable, READ)),
		Intruction("rsr.sar",       0x030300, 0xffff0f, RSR_spec, new RWsr(sr.sar, READ)),
		Intruction("rsr.ddr",       0x036800, 0xffff0f, RSR_spec, new RWsr(sr.EPC[0], READ)),
		Intruction("rsr",    0x030000, 0xff000f, RSR, new RWsr(READ)),
		Intruction("rsync",  0x002010, 0xffffff, NONE),
		Intruction("s8i",    0x004002, 0x00f00f, RRI8_disp, new S8i),
		Intruction("s16i",   0x005002, 0x00f00f, RRI8_disp16, new S16i),
		Intruction("s32i",   0x006002, 0x00f00f, RRI8_disp32, s32i),

		Intruction("sll",    0xa10000, 0xff00ff, RRR_sll, new Sll),
		Intruction("slli",   0x010000, 0xef000f, RRR_slli, new Slli),
		Intruction("sra",    0xb10000, 0xff0f0f, RRR_2rr),
		Intruction("srai",   0x210000, 0xef000f, RRR_srai),
		Intruction("src",    0x810000, 0xff000f, RRR),
		Intruction("srl",    0x910000, 0xff0f0f, RRR_2rr, new Srl),
		Intruction("srli",   0x410000, 0xff000f, RRR_sh, new Srli),
		Intruction("ssa8b",  0x403000, 0xfff0ff, RRR_ssa),
		Intruction("ssa8l",  0x402000, 0xfff0ff, RRR_ssa, new Ssa8l),
		Intruction("ssai",   0x404000, 0xfff0ef, RRR_ssai),
		Intruction("ssl",    0x401000, 0xfff0ff, RRR_ssa, new Ssl),
		Intruction("ssr",    0x400000, 0xfff0ff, RRR_ssa, new Ssr),
		Intruction("sub",    0xc00000, 0xff000f, RRR, new Sub),
		Intruction("subx2",  0xd00000, 0xff000f, RRR),
		Intruction("subx4",  0xe00000, 0xff000f, RRR),
		Intruction("subx8",  0xf00000, 0xff000f, RRR),
		Intruction("waiti",  0x007000, 0xfff0ff, RRR_1imm, new Waiti),
		Intruction("wdtlb",  0x50e000, 0xfff00f, RRR_2r),
		Intruction("witlb",  0x506000, 0xfff00f, RRR_2r),
		Intruction("wsr.intenable", 0x13e400, 0xffff0f, RSR_spec, new RWsr(sr.intenable, WRITE)),
		Intruction("wsr.litbase",   0x130500, 0xffff0f, RSR_spec, new RWsr(sr.litbase, WRITE)),
		Intruction("wsr.vecbase",   0x13e700, 0xffff0f, RSR_spec, new RWsr(sr.vecbase, WRITE)),
		Intruction("wsr.ps",        0x13e600, 0xffff0f, RSR_spec, new RWsr(sr.ps, WRITE)),
		Intruction("wsr.epc1",      0x13b100, 0xffff0f, RSR_spec, new RWsr(sr.EPC[0], WRITE)),
		Intruction("wsr.ccompare0", 0x13f000, 0xffff0f, RSR_spec, new RWsr(sr.ccompare0, WRITE)),
		Intruction("wsr.intclear",  0x13e300, 0xffff0f, RSR_spec, new RWsr(sr.intclear, WRITE)),
		Intruction("wsr.sar",       0x130300, 0xffff0f, RSR_spec, new RWsr(sr.sar, WRITE)),
		Intruction("wsr",    0x130000, 0xff000f, RSR, new RWsr(WRITE)),
		Intruction("xor",    0x300000, 0xff000f, RRR, new Xor),
		Intruction("xsr",    0x610000, 0xff000f, RSR),
		Intruction("orb",	 0x220000, 0xff0000, RRR),

		Intruction("add.n",   0x000a, 0x000f, RRRN, add),
		Intruction("addi.n",  0x000b, 0x000f, RRRN_addi, new Addin),
		Intruction("beqz.n",  0x008c, 0x00cf, RI6, beqz),
		Intruction("bnez.n",  0x00cc, 0x00cf, RI6, bnez),
		Intruction("mov.n",   0x000d, 0xf00f, RRRN_2r, new Mov),
		Intruction("break.n", 0xf02d, 0xf0ff, RRRN, new Breakn),
		Intruction("ret.n",   0xf00d, 0xffff, NNONE, ret),
		Intruction("l32i.n",  0x0008, 0x000f, RRRN_disp, l32i),
		Intruction("movi.n",  0x000c, 0x008f, RI7, movi),
		Intruction("nop.n",   0xf03d, 0xffff, NNONE),
		Intruction("s32i.n",  0x0009, 0x000f, RRRN_disp, s32i),
	};

	Register<int32_t> REGISTERS[16] = {
		Register<int32_t>(0),
		Register<int32_t>(1),
		Register<int32_t>(2),
		Register<int32_t>(3),
		Register<int32_t>(4),
		Register<int32_t>(5),
		Register<int32_t>(6),
		Register<int32_t>(7),
		Register<int32_t>(8),
	    Register<int32_t>(9),
		Register<int32_t>(10),
		Register<int32_t>(11),
		Register<int32_t>(12),
		Register<int32_t>(13),
		Register<int32_t>(14),
		Register<int32_t>(15),
	};

	Register<uint32_t>& pc = Register<uint32_t>("pc");

	MMU* mmu;

public:
	CPU8266(MMU* mmu);
	~CPU8266();

	bool Run(uint32_t entrypoint);
};

