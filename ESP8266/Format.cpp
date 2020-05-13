#include "Format.h"


Format::Format() {

}

Format::Format(int size) : Format() {
	_size = size;
}

Format::Format(int size, Operand* o1) : Format(size) {
	_operands.push_back(o1);
}

Format::Format(int size, Operand* o1, Operand* o2) : Format(size, o1) {
	_operands.push_back(o2);
}

Format::Format(int size, Operand* o1, Operand* o2, Operand* o3) : Format(size, o1, o2) {
	_operands.push_back(o3);
}

Format::Format(int size, Operand* o1, Operand* o2, Operand* o3, Operand* o4) : Format(size, o1, o2, o3) {
	_operands.push_back(o4);
}

int Format::GetSize() {
	return _size;
}
