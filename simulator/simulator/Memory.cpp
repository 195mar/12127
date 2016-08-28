#include "Memory.h"
Memory* Memory::memory = 0;

Memory::Memory()
{
}


Memory::~Memory()
{
}

double Memory::get(string varName)
{
	double result = memoryMap.find(varName)->second;
	return result;
}
void Memory::set(string varName, double value)
{
	memoryMap[varName] = value;
}