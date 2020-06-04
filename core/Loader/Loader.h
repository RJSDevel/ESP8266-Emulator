#pragma once

#include "MMU.h"

#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;


class Loader
{
public:
	static Memory* load(MMU* mmu, const string name,  const string file, uint32_t address)
	{
		ifstream ifs(file, ios::binary|ios::ate);
		
		if (ifs.is_open()) {
			std::streamoff size = ifs.tellg();
			ifs.seekg(0, ios::beg);
			
			char* buffer = new char[size];
			
			ifs.read(buffer, size);		
			ifs.close();
			
			Memory* memory = new Memory(name, address, buffer, size);
			mmu->AddRegion(memory);

			delete buffer;

			return memory;
		} else {
			cout << "Can't open file: " << file << endl;
		}
	}
};

