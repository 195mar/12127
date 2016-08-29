#include "Assignment.h"
#include "Memory.h"
#include <iostream>

using namespace std;

void Assignment::execute()
{
	string a = operands[LEFT]->getValue();
	double b = getOperandValue(operands[RIGHT]);
	Memory::getMemory()->set(a, b);

	for (Operation* leftDependant : leftRes)
	{
		leftDependant->addOperand(operands[LEFT], LEFT);
		leftDependant->setStartTime(startTime + T);
	}
	for (Operation* rightDependant : rightRes)
	{
		rightDependant->addOperand(operands[LEFT], RIGHT);
		rightDependant->setStartTime(startTime + T);
	}

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
		if (op->E_type() == CONSTANT) //get from expression, string to double
			oper = stod(op->getValue()); 
		else if (op->E_type() == VARIABLE) // get from memory
			oper = Memory::getMemory()->get(op->getValue()); 
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