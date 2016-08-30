#include "Power.h"
#include "Memory.h"
#include <iostream>
#include <math.h>

using namespace std;

void Power::execute()
{
	double a = getOperandValue(operands[LEFT]);
	double b = getOperandValue(operands[RIGHT]);
	result = pow(a, b);
}
void Power::forwardResult()
{
	Expression *res = new Expression(to_string(result), CONSTANT);

	for (Operation* leftDependant : leftRes)
	{
		leftDependant->addOperand(res, LEFT);
		if (leftDependant->hasBothOperands()) //znaci da je cekala jos samo na ovu operaciju
			leftDependant->setStartTime(startTime + T);
	}
	for (Operation* rightDependant : rightRes)
	{
		rightDependant->addOperand(res, RIGHT);
		if (rightDependant->hasBothOperands()) //znaci da je cekala jos samo na ovu operaciju
			rightDependant->setStartTime(startTime + T);
	}
}
void Power::printOp()
{
	cout << "\n Power - id: " << id << "  ";
	if (operands[LEFT] != nullptr)
		cout << " left: " << operands[LEFT]->getValue() << "  ";
	else
		cout << " left: some res  ";

	if (operands[RIGHT] != nullptr)
		cout << " right: " << operands[RIGHT]->getValue();
	else
		cout << " right: some res ";
}

double Power::getOperandValue(Expression* op) {
	double oper;
	try
	{
		if (op->E_type() == CONSTANT)
			oper = stod(op->getValue()); //string to double
		else if (op->E_type() == VARIABLE)
			oper = Memory::getMemory()->get(op->getValue());
		else
			throw "Operand sabiranja mora biti var ili const";
	}
	catch (string e)
	{
		cout << e;
	}
	return oper;
}

void Power::addOperand(Expression* operand, int position)
{
	try {
		if ((position == LEFT) || (position == RIGHT))
			operands[position] = operand;
		else
			throw "Operacija sabiranje prima samo 2 operanda!\n";
	}
	catch (string e)
	{
		cout << e;
	}
}