#include "Machine.h"
#include "Compiler.h"
#include "Addition.h"
#include "Assignment.h"
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

Machine* Machine::machine = 0;
Machine::~Machine()
{
}

void Machine::exec(string file)
{
	//citaj fajl i napravi graf
	//sve operacije se cuvaju u vektoru svih operacija
	ifstream inputFile(file);
	ofstream outputFile("log.txt");
	string str;
	int opNum = 1;//operation number, broj operacije koja se parsira

	while (getline(inputFile, str))
	{
		vector<string> ss = Compiler::getCompiler()->split(str, ' ');
		string op = ss.at(1);
		string left = ss.at(2);
		string right = ss.at(3);

		ArithmeticOperation *newOperation;
		if (!op.compare("="))
			newOperation = makeAssignmentOp(left, right, opNum++);
		else
			newOperation = makeOtherOp(left, right, opNum++, op);

		allOperations.push_back(newOperation);

	}

	//prolazi kroz sve operacije i vidi da li je neka spremna za izvrsavanje
	printAllOperations();
}

ArithmeticOperation* Machine::makeAssignmentOp(string left, string right,int opNum) {
	Assignment* newOperation = new Assignment(opNum);
	newOperation->addOperand(new Expression(left, VARIABLE), LEFT);

	Expression *rightEx;
	if (right.at(0) == '(') {
		ArithmeticOperation *opRes = nullptr;
		string num = right.substr(1, right.length() - 2);
		int id = stoi(num);
		for (int i = 0; i < allOperations.size(); i++) {
			if (allOperations.at(i)->getId() == id) {
				opRes = allOperations.at(i);
				break;
			}
		}
		if (opRes != nullptr)
			opRes->addRightRes(newOperation);
		
	}
	else {

		if (isDigit(right))
			rightEx = new Expression(right, CONSTANT);
		else
			rightEx = new Expression(right, VARIABLE);

		newOperation->addOperand(rightEx, RIGHT);
	}
	return newOperation;
}

ArithmeticOperation* Machine::makeOtherOp(string left, string right, int opNum, string op) {
	
	ArithmeticOperation* newOperation = nullptr;
	if (!op.compare("+"))
		newOperation = new Addition(opNum);
	else if (!op.compare("*"))
		newOperation = new Addition(opNum);

	try {

		//left operand
		if (left.at(0) == '(') {
			ArithmeticOperation *opRes = nullptr;
			string num = left.substr(1, left.length() - 2);
			int id = stoi(num);
			for (int i = 0; i < allOperations.size(); i++) {
				if (allOperations.at(i)->getId() == id) {
					opRes = allOperations.at(i);
					break;
				}
			}
			if (opRes != nullptr)
				opRes->addLeftRes(newOperation);
			else
				throw "makeOtherOp - left opRes not found";
		}
		else {
			Expression *leftEx;
			if (isDigit(left))
				leftEx = new Expression(left, CONSTANT);
			else
				leftEx = new Expression(left, VARIABLE);

			newOperation->addOperand(leftEx, LEFT);
		}

		//right operand
		Expression *rightEx;
		if (right.at(0) == '(') {
			ArithmeticOperation *opRes = nullptr;
			string num = right.substr(1, right.length() - 2);
			int id = stoi(num);
			for (int i = 0; i < allOperations.size(); i++) {
				if (allOperations.at(i)->getId() == id) {
					opRes = allOperations.at(i);
					break;
				}
			}
			if (opRes != nullptr)
				opRes->addRightRes(newOperation);
			else
				throw "makeOtherOp - right opRes not found";
			
		}
		else {

			if (isDigit(right))
				rightEx = new Expression(right, CONSTANT);
			else
				rightEx = new Expression(right, VARIABLE);

			newOperation->addOperand(rightEx, RIGHT);
		}
	}
	catch (string e)
	{
		cout << e;
	}
	

	return newOperation;
}

bool Machine::isDigit(string op) {
	for (char o : op) {
		if ((o > 57) || (o < 48))
			return false;
	}
	return true;
}

void Machine::printAllOperations()
{
	for (int i = 0; i < allOperations.size(); i++)
	{
		ArithmeticOperation * currOp = allOperations.at(i);
		currOp->printOp();
	}
}