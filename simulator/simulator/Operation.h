#pragma once
#include <vector>
#include "Expression.h"
using namespace std;

#define LEFT 0
#define RIGHT 1

class Operation
{
protected:
	int id;
	int T;
	int startTime;
	int executingTime;
	double result;
	Expression **operands;
	vector <Operation*> leftRes;
	vector <Operation*> rightRes;

public:
	Operation(){}
	~Operation(){}

	virtual void addLeftRes(Operation* left) = 0;
	virtual void addRightRes(Operation* right) = 0;
	virtual void setId(int id) = 0;
	virtual int getId() = 0;
	virtual int getT() = 0;
	virtual void addOperand(Expression* operand, int position) = 0;
	virtual int getStartTime() = 0;
	virtual void setStartTime(int startTime) = 0;
	virtual bool hasBothOperands() = 0;
	virtual void incExecutingTime() = 0;
	virtual bool finishedExecuting() = 0;
	virtual void forwardResult() = 0;
};

