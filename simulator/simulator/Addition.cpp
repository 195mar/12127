#include "Addition.h"
#include "Memory.h"

Addition::Addition()
{
}


Addition::~Addition()
{
}
void Addition::setLeft(string left) 
{
	this->operands[0] = Memory::getMemory()->get(left);
}
void Addition::setRight(string right)
{
	this->operands[1] = Memory::getMemory()->get(right);
}
void Addition::setLeft(double left)
{
	this->operands[0] = left;
}
void Addition::setRight(double right)
{
	this->operands[1] = right;
}