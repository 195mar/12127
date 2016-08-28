#pragma once
#include "ArithmeticOperation.h"
class Addition :public ArithmeticOperation
{
private :
	int T = 5;
public:
	Addition(int id){ this->id = id; }
	virtual double execute();
	virtual void addOperand(Expression* operand, int position);
	double getOperandValue(Expression* op);
	virtual void printOp();
};

