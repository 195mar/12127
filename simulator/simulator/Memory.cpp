#include "Memory.h"


Memory::Memory()
{
}


Memory::~Memory()
{
}

Memory* Memory::getMemory() {
	if (memory != nullptr)
		return memory;
	memory = new Memory();
	return memory;
}
