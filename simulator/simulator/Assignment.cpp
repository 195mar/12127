#include "Assignment.h"
#include "Memory.h"
#include <iostream>

using namespace std;

double Assignment::execute()
{
	string a = operands[LEFT]->getValue();
	double b = getOperandValue(operands[RIGHT]);
	Memory::getMemory()->set(a, b);
	return b;
}


void Assignment::printOp()
{
	cout << "\n Assignment - id: " << id << "  ";
	if (operands[LEFT] != NULL)
		cout << "left: "<< operands[LEFT]->getValue() << "  ";
	if (operands[RIGHT] != NULL)
		cout << "right: " << operands[RIGHT]->getValue();
	else
		cout << "right: some res";
}

double Assignment::getOperandValue(Expression* op) {
	double oper;
	try
	{
		if (op->E_type() == CONSTANT)
			oper = stod(op->getValue()); //string to double
		else if (op->E_type() == VARIABLE)
			oper = 0; //uzimanje iz memorije
		else
			throw "Desni operand dodele vrednosti mora biti const ili var";
	}
	catch (string e)
	{
		cout << e;
	}
	return oper;
}

void Assignment::addOperand(Expression* operand, int position)
{
	try {
		if ((position == LEFT) || (position == RIGHT))
			operands[position] = operand;
		else
			throw "Dodela vrednosti mora imati samo 2 operanda!\n";
	}
	catch (string e)
	{
		cout << e;
	}
}