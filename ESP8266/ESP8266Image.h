#pragma once

#include <cstdint>

#include <Loader/FirmwareImage.h>


#ifdef _MSC_VER
#define IMAGE_MAGIC ((unsigned char) 0xE9)
#else
#define IMAGE_MAGIC 0xE9
#endif

#define CHECKSUM_MAGIC 0xEF


class ESP8266Image: public FirmwareImage {
public:
	struct ESP8266Header {
		uint8_t magic;
		uint8_t segments;
		uint8_t flash_mode;
		uint8_t flash_size_freq;
		uint32_t entry_point;
	};

	struct ESP8266Segment {
		uint32_t memory_offset;
		uint32_t segment_size;
	};

	ESP8266Image();
	~ESP8266Image();
	
	virtual void Load(char* bin, uint32_t size);

	virtual Entrypoint GetEntryPoint();

	shared_ptr<Segment> GetSegment(int segment);

private:
	ESP8266Segment* GetSegment(unsigned char* image, ESP8266Image::ESP8266Header* header, int segment);

	ESP8266Header* _header;
	unsigned char* _image;
};