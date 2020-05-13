#include "ESP8266Image.h"

#include <iostream>
#include <string>

#include <stdio.h>
#include <iomanip>

#include "Exception\Exception.h"

using namespace std;


ESP8266Image::ESP8266Image()
{
}

ESP8266Image::~ESP8266Image()
{
	delete _image;
}


ESP8266Image::ESP8266Segment* ESP8266Image::GetSegment(unsigned char* image, ESP8266Header* header, int segment)
{
	if (segment > header->segments || segment < 0) {
		throw Exception();
	}

	if (segment == 0) {
		return reinterpret_cast<ESP8266Segment*>(image + sizeof(ESP8266Header));
	}

	int address = sizeof(ESP8266Header);
	for (int i = segment; i > 0; i--) {
		address += GetSegment(image, header, i - 1)->segment_size + sizeof(ESP8266Segment);
	}

	return reinterpret_cast<ESP8266Segment*>(image + address);
}


void ESP8266Image::Load(char* bin, uint32_t size)
{
	_image = new unsigned char[size];
	memcpy(_image, bin, size);

	_header = reinterpret_cast<ESP8266Header*>(_image);
	
	uint32_t user_rom_offset = 0;

	if (_header->magic == IMAGE_MAGIC) {
		char calculatedCrc = CHECKSUM_MAGIC;
		
		for (int index = 0; index < _header->segments; index++)
		{
			ESP8266Segment *segment = GetSegment(_image, _header, index);

			cout << "Segment: address - " << hex << segment->memory_offset << " size - " << segment->segment_size << endl;

			for (unsigned position = 0; position < segment->segment_size; position++)
			{
				calculatedCrc ^= *(reinterpret_cast<char*>(segment) + sizeof(ESP8266Segment) + position);
			}

			user_rom_offset += segment->segment_size;

			_segments.push_back(shared_ptr<Segment>(new Segment(
				segment->memory_offset, 
				segment->segment_size, 
				reinterpret_cast<char*>(segment) + sizeof(ESP8266Segment))));
		}
		
		char imageCrc = *reinterpret_cast<char*>(_image + size - 1);
		if (imageCrc != calculatedCrc) {
			//cout << "CRC is wrong" << endl;
			//delete _image;
			//throw Exception();
		}
	} else {
		cout << "Magic is wrong" << endl;
		throw Exception();
	}

	user_rom_offset += _header->segments * sizeof(ESP8266Segment) - 4;
	ESP8266Header* user_rom_header = reinterpret_cast<ESP8266Header*>(_image + user_rom_offset);

	ESP8266Segment *segment = GetSegment(_image + user_rom_offset, user_rom_header, 0);
	segment->segment_size = size - user_rom_offset;
	cout << "Segment: address - " << hex << segment->memory_offset << " size - " << segment->segment_size << endl;
	_segments.push_back(shared_ptr<Segment>(new Segment(
			segment->memory_offset,
			segment->segment_size,
			reinterpret_cast<char*>(segment) + sizeof(ESP8266Segment))));
	
}

Entrypoint ESP8266Image::GetEntryPoint()
{
	return _header->entry_point;
}

shared_ptr<Segment> ESP8266Image::GetSegment(int segment) {
	return _segments.at(segment);
}