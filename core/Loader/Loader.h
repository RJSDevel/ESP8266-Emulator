#pragma once

#include "FirmwareImage.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

template<class T>
class Loader
{
public:
	Loader(FirmwareImage *image, const string imagePath): mImage(reinterpret_cast<T*>(image))
	{
		ifstream ifs(imagePath, ios::binary|ios::ate);
		
		if (ifs.is_open()) {
			std::streamoff size = ifs.tellg();
			ifs.seekg(0, ios::beg);
			
			char* buffer = new char[size];
			
			ifs.read(buffer, size);		
			ifs.close();
			
			cout << "Image size: " << size << endl;
			
			mImage->Load(buffer, size);
		} else {
			cout << "Can't open file: " << imagePath << endl;
		}
	}
	
	~Loader() 
	{
		
	};
	
	T* GetImage(){ return mImage; }
	
private:
	T* mImage;
};

