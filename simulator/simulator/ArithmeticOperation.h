#pragma once
#include "Operation.h"
#include "Expression.h"
class ArithmeticOperation : public Operation
{
protected:
	int startTime = 0;
public:
	ArithmeticOperation() {
		operands = new Expression*[2];
		operands[0] = NULL;
		operands[1] = NULL;
	}
	~ArithmeticOperation(){}

	void addLeftRes(Operation* left) { leftRes.push_back(left); }
	void addRightRes(Operation* right) { rightRes.push_back(right); }
	void setId(int id) { this->id = id; }
	int getId() { return id; }
	int getT() { return T; }
	int getStartTime() { return startTime; }
	virtual double execute(){ return 4; }
	virtual void addOperand(Expression* operand, int position){}
	virtual void printOp(){}
};
