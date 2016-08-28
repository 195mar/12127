#include "Addition.h"
#include "Memory.h"
#include <iostream>

using namespace std;

double Addition::execute()
{
	double a = getOperandValue(operands[LEFT]);
	double b = getOperandValue(operands[RIGHT]);
	return a + b;
}
void Addition::printOp()
{
	cout << "\n Addition - id: " << id << "  ";
	if (operands[LEFT] != nullptr)
		cout << " left: " << operands[LEFT]->getValue() << "  ";
	else
		cout << " left: some res  ";

	if (operands[RIGHT] != nullptr)
		cout << " right: " << operands[RIGHT]->getValue();
	else
		cout << " right: some res ";
}

double Addition::getOperandValue(Expression* op) {
	double oper;
	try
	{
		if (op->E_type() == CONSTANT)
			oper = stod(op->getValue()); //string to double
		else if (op->E_type() == VARIABLE)
			oper = 0; //uzimanje iz memorije
		else
			throw "Operand sabiranja mora biti var ili const";
	}
	catch (string e)
	{
		cout << e;
	}
	return oper;
}

void Addition::addOperand(Expression* operand, int position)
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