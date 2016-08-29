#pragma once
#include "ArithmeticOperation.h"
class Power :public ArithmeticOperation
{
public:
	Power(int id){ this->id = id; T = 10; }
	virtual void execute();
	virtual void addOperand(Expression* operand, int position);
	double getOperandValue(Expression* op);
	virtual void printOp();
};

