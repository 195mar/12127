#pragma once
#include "ArithmeticOperation.h"
class Multiplication : public ArithmeticOperation
{
public:
	Multiplication(int id){ this->id = id; T = 8; }
	virtual void execute();
	virtual void addOperand(Expression* operand, int position);
	double getOperandValue(Expression* op);
	virtual void printOp();
	virtual void forwardResult();
};

