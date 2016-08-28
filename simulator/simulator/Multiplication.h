#pragma once
#include "ArithmeticOperation.h"
class Multiplication : public ArithmeticOperation
{
private :
	int T = 8;
public:
	Multiplication(int id){ this->id = id; }
	double execute();
	void addOperand(Expression* operand, int position);
	double getOperandValue(Expression* op);
	void printOp();
};

