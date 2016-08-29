#pragma once
#include "Operation.h"
#include "Expression.h"
class ArithmeticOperation : public Operation
{
public:
	ArithmeticOperation() {
		startTime = -1;
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
	void setStartTime(int startTime) { this->startTime = startTime; }
	bool hasBothOperands() { return (operands[0] != NULL && operands[1] != NULL); }
	string outputForLog() 
	{ 
		string s; 
		s.append("(" + to_string(id));
		s.append(")\t");
		s.append(to_string(startTime)+"ns/");
		s.append(to_string(startTime + T) + "ns\n");
		return s;
	}

	virtual void execute(){}
	virtual void addOperand(Expression* operand, int position){}
	virtual void printOp(){}
	
};

