#pragma once
#include <vector>
using namespace std;
class Operation
{
protected:
	int id;
	int T;
	vector <double> operands;
	vector <Operation*> leftRes;
	vector <Operation*> rightRes;


public:
	Operation();
	~Operation();

	virtual int execute() = 0;
	virtual void setLeft(string left) = 0;
	virtual void setRight(string right) = 0;
	virtual void setLeft(double left) = 0;
	virtual void setRight(double right) = 0;

};

