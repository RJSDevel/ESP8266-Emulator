#pragma once

#include <vector>
#include <memory>
#include <cstdint>

using namespace std;

typedef unsigned int Entrypoint;

class Segment
{
public:
	Segment(uint32_t offset, uint32_t size, char* pointer):
		_offset(offset), 
		_size(size),
		_pointer(pointer){}

	virtual int GetOffset() {
		return _offset;
	}

	virtual int GetSize() {
		return _size;
	}

	char* _pointer;

private:
	uint32_t _offset;
	uint32_t _size;
};


class FirmwareImage {
public:
	virtual ~FirmwareImage() {
		while (!_segments.empty()) {
			delete _segments.back().get();
			_segments.pop_back();
		}
	}

	virtual void Load(char *bin, uint32_t size) = 0;

	virtual Entrypoint GetEntryPoint() = 0;

	virtual vector<shared_ptr<Segment>> GetSegments() const {
		return _segments;
	}
protected:
	 vector<shared_ptr<Segment>> _segments;
};