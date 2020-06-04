#include "CPU8266.h"

#include "Loader\Loader.h"


class Gpio : public Memory
{

#define PIN_OUT			0x00
#define PIN_OUT_SET		0x04
#define PIN_OUT_CLEAR	0x08

#define PIN_DIR			0x0C
#define PIN_DIR_OUTPUT 	0x10
#define	PIN_DIR_INPUT	0x14

#define PIN_IN			0x18

#define PIN_0			0x28
#define PIN_2			0x30


public:
	virtual void Write32(uint32_t address, int32_t value) {
		switch (address)
		{
		case PIN_OUT:
			cout << "PIN_OUT" << endl;
			break;
		case PIN_OUT_SET:
			cout << "PIN_OUT_SET" << endl;
			break;
		case PIN_OUT_CLEAR:
			cout << "PIN_OUT_CLEAR" << endl;
			break;
		case PIN_DIR:
			cout << "PIN_DIR" << endl;
			break;
		case PIN_DIR_OUTPUT:
			cout << "PIN_DIR_OUTPUT" << endl;
			break;
		case PIN_DIR_INPUT:
			cout << "PIN_DIR_INPUT" << endl;
			break;
		case PIN_IN:
			cout << "PIN_IN" << endl;
			break;
		case PIN_0:
			cout << "PIN_0" << endl;
			break;
		case PIN_2:
			cout << "PIN_2" << endl;
			break;
		}
	}

	virtual int32_t Read32(uint32_t address) {
		switch (address)
		{
		case PIN_OUT:
			cout << "PIN_OUT" << endl;
			break;
		case PIN_OUT_SET:
			cout << "PIN_OUT_SET" << endl;
			break;
		case PIN_OUT_CLEAR:
			cout << "PIN_OUT_CLEAR" << endl;
			break;
		case PIN_DIR:
			cout << "PIN_DIR" << endl;
			break;
		case PIN_DIR_OUTPUT:
			cout << "PIN_DIR_OUTPUT" << endl;
			break;
		case PIN_DIR_INPUT:
			cout << "PIN_DIR_INPUT" << endl;
			break;
		case PIN_IN:
			cout << "PIN_IN" << endl;
			return 0;
		case PIN_0:
			cout << "PIN_0" << endl;
			break;
		case PIN_2:
			cout << "PIN_2" << endl;
			break;
		}

		return -1;
	}

	virtual string GetName() const {
		return "gpio";
	}

	virtual uint32_t GetAddress() const {
		return 0x60000300;
	}

	virtual uint32_t GetSize() const {
		return 0x74;
	}
};

class Uart0 : public Memory
{

#define UART0_BASE	0x60000000

#define IDX_UART_FIFO		0
#define IDX_UART_INT_RAW	1
#define IDX_UART_INT_ST		2
#define IDX_UART_INT_ENA	3
#define IDX_UART_INT_CLR	4
#define IDX_UART_CLKDIV		5
#define IDX_UART_AUTOBAUD	6
#define IDX_UART_STATUS		7
#define IDX_UART_CONF0		8
#define IDX_UART_CONF1		9
#define IDX_UART_LOWPULSE	10
#define IDX_UART_HIGHPULSE	11
#define IDX_UART_PULSE_NUM	12
#define IDX_UART_DATE		30
#define IDX_UART_ID			21

uint32_t uart0[64];

#define UART0_FIFO		uart0[IDX_UART_FIFO]
#define UART0_INT_RAW	uart0[IDX_UART_INT_RAW]
#define UART0_INT_ST	uart0[IDX_UART_INT_ST]
#define UART0_INT_ENA	uart0[IDX_UART_INT_ENA]
#define UART0_INT_CLR	uart0[IDX_UART_INT_CLR]
#define UART0_CLKDIV	uart0[IDX_UART_CLKDIV]
#define UART0_AUTOBAUD	uart0[IDX_UART_AUTOBAUD]
#define UART0_STATUS	uart0[IDX_UART_STATUS]
#define UART0_CONF0		uart0[IDX_UART_CONF0]
#define UART0_CONF1		uart0[IDX_UART_CONF1]
#define UART0_LOWPULSE	uart0[IDX_UART_LOWPULSE]
#define UART0_HIGHPULSE	uart0[IDX_UART_HIGHPULSE]
#define UART0_PULSE_NUM	uart0[IDX_UART_PULSE_NUM]
#define UART0_DATE		uart0[IDX_UART_DATE]
#define UART0_ID		uart0[IDX_UART_ID]

public:
	virtual void Write32(uint32_t address, int32_t value) {

		uart0[address / 4] = value;

		cout << "Write uart ";

		switch (address / 4)
		{
		case IDX_UART_FIFO:
			cout << "IDX_UART_FIFO = "  << value << endl;
			break;
		case IDX_UART_INT_RAW:
			cout << "IDX_UART_INT_RAW = "  << value << endl;
			break;
		case IDX_UART_INT_ST:
			cout << "IDX_UART_INT_ST = "  << value << endl;
			break;
		case IDX_UART_INT_ENA:
			cout << "IDX_UART_INT_ENA = "  << value << endl;
			break;
		case IDX_UART_INT_CLR:
			cout << "IDX_UART_INT_CLR = "  << value << endl;
			break;
		case IDX_UART_CLKDIV:
			cout << "IDX_UART_CLKDIV = "  << value << endl;
			break;
		case IDX_UART_AUTOBAUD:
			cout << "IDX_UART_AUTOBAUD = "  << value << endl;
			break;
		case IDX_UART_STATUS:
			cout << "IDX_UART_STATUS = "  << value << endl;
			break;
		case IDX_UART_CONF0:
			cout << "IDX_UART_CONF0 = "  << value << endl;
			break;
		case IDX_UART_CONF1:
			cout << "IDX_UART_CONF1 = "  << value << endl;
			break;
		case IDX_UART_LOWPULSE:
			cout << "IDX_UART_LOWPULSE = "  << value << endl;
			break;
		case IDX_UART_HIGHPULSE:
			cout << "IDX_UART_HIGHPULSE = "  << value << endl;
			break;
		case IDX_UART_PULSE_NUM:
			cout << "IDX_UART_PULSE_NUM = "  << value << endl;
			break;
		case IDX_UART_DATE:
			cout << "IDX_UART_DATE = "  << value << endl;
			break;
		case IDX_UART_ID:
			cout << "IDX_UART_ID = "  << value << endl;
			break;
		}

		cout << "";
	}

	virtual int32_t Read32(uint32_t address) {

		cout << "Read uart ";

		uint32_t value = uart0[address / 4];

		switch (address / 4)
		{
		case IDX_UART_FIFO:
			cout << "IDX_UART_FIFO = "  << value << endl;
			break;
		case IDX_UART_INT_RAW:
			cout << "IDX_UART_INT_RAW = "  << value << endl;
			break;
		case IDX_UART_INT_ST:
			cout << "IDX_UART_INT_ST = "  << value << endl;
			break;
		case IDX_UART_INT_ENA:
			cout << "IDX_UART_INT_ENA = "  << value << endl;
			break;
		case IDX_UART_INT_CLR:
			cout << "IDX_UART_INT_CLR = "  << value << endl;
			break;
		case IDX_UART_CLKDIV:
			cout << "IDX_UART_CLKDIV = "  << value << endl;
			break;
		case IDX_UART_AUTOBAUD:
			cout << "IDX_UART_AUTOBAUD = "  << value << endl;
			break;
		case IDX_UART_STATUS:
			cout << "IDX_UART_STATUS = "  << value << endl;
			break;
		case IDX_UART_CONF0:
			cout << "IDX_UART_CONF0 = "  << value << endl;
			break;
		case IDX_UART_CONF1:
			cout << "IDX_UART_CONF1 = "  << value << endl;
			break;
		case IDX_UART_LOWPULSE:
			cout << "IDX_UART_LOWPULSE = "  << value << endl;
			break;
		case IDX_UART_HIGHPULSE:
			cout << "IDX_UART_HIGHPULSE = "  << value << endl;
			break;
		case IDX_UART_PULSE_NUM:
			cout << "IDX_UART_PULSE_NUM = "  << value << endl;
			break;
		case IDX_UART_DATE:
			cout << "IDX_UART_DATE = "  << value << endl;
			break;
		case IDX_UART_ID:
			cout << "IDX_UART_ID = "  << value << endl;
			break;
		}

		return value;
	}

	virtual string GetName() const {
		return "uart0";
	}

	virtual uint32_t GetAddress() const {
		return UART0_BASE;
	}

	virtual uint32_t GetSize() const {
		return 0x80;
	}
};

class Uart1 : public Memory
{


public:
	virtual void Write32(uint32_t address, int32_t value) {
		switch (address)
		{

		}
	}

	virtual int32_t Read32(uint32_t address) {
		switch (address)
		{

		}

		return -1;
	}

	virtual string GetName() const {
		return "uart1";
	}

	virtual uint32_t GetAddress() const {
		return 0x60000f00;
	}

	virtual uint32_t GetSize() const {
		return 0x80;
	}
};



int main(int argc, char **argv)
{
	MMU* mmu = new MMU();

	Loader::load(mmu, "iram0", "iram0.bin", 0x40000000);
	//Memory* flash = Loader::load(mmu, "irom0", "firmware-combined.bin", 0x40200000);

	mmu->AddRegion(new Memory("dram0", 0x3FFE8000, 0x14000));
	mmu->AddRegion(new Memory("iram1", 0x40100000, 0x8000));

	mmu->AddRegion(new Memory("ets",	0x3fffc000, 0x20000));

	mmu->AddRegion(new Memory("dport0", 0x3ff00000, 0x1000));

	mmu->AddRegion(new Uart0);
	mmu->AddRegion(new Memory("spi1",	0x60000100, 0x100));
	mmu->AddRegion(new Memory("spi0",	0x60000200, 0x100));

	mmu->AddRegion(new Gpio());

	mmu->AddRegion(new Memory("wifi",	0x60000500, 0x100));

	mmu->AddRegion(new Memory("timer",	0x60000600, 0x34));
	mmu->AddRegion(new Memory("rtc",	0x60000700, 0xB8));
	mmu->AddRegion(new Memory("iomux",	0x60000800, 0x44));
	mmu->AddRegion(new Memory("wtd",	0x60000900, 0x18));
	mmu->AddRegion(new Memory("sdio",	0x60000a00, 0x08)); 
	mmu->AddRegion(new Memory("slc",	0x60000b00, 0xC0)); // DMA
	mmu->AddRegion(new Memory("sar",	0x60000d00, 0x5C));
	mmu->AddRegion(new Memory("i2c",	0x60000e00, 0x30)); 
	mmu->AddRegion(new Uart1);

	mmu->AddRegion(new Memory("rtcb",	0x60001000, 0x100));
	mmu->AddRegion(new Memory("rtcs",	0x60001100, 0x100));
	mmu->AddRegion(new Memory("rtcu",	0x60001200, 0x200));


	CPU8266 cpu(mmu);
	cpu.Run(0x40000080);

	return 0;
}