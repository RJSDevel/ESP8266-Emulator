#include "CPU8266.h"


int main(int argc, char **argv)
{
	CPU8266 cpu;
	cpu.Load("firmware-combined.bin");
	cpu.Decode();
	cpu.Execute();

	return 0;
}