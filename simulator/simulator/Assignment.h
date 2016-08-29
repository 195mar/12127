#pragma once
#include "ArithmeticOperation.h"
class Assignment : public ArithmeticOperation
{
public:
	Assignment(int id){ this->id = id; T = 3; }
	virtual void execute();
	virtual void addOperand(Expression* operand, int position);
	double getOperandValue(Expression* op);
	virtual void printOp();
	string getVarName() {
		if (operands[0] != NULL)
			return operands[0]->getValue();
	}
};

