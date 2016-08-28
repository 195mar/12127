#pragma once
#include "ArithmeticOperation.h"
class Assignment : public ArithmeticOperation
{
private:
	int T = 3;
public:
	Assignment(int id){ this->id = id; }
	virtual double execute();
	virtual void addOperand(Expression* operand, int position);
	double getOperandValue(Expression* op);
	virtual void printOp();
};

