#pragma once
#include "ArithmeticOperation.h"
class Addition :public ArithmeticOperation
{
public:
	Addition(int id){ this->id = id; T = 5; }
	virtual void execute();
	virtual void addOperand(Expression* operand, int position);
	double getOperandValue(Expression* op);
	virtual void printOp();
};

