#include "Machine.h"
#include "Compiler.h"
#include "Addition.h"
#include "Multiplication.h"
#include "Power.h"
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

	
	//printAllOperations();

	int currentNanoSec = 0;
	while ((!allOperations.empty()) || (!forExecution.empty()))
	{

		//prolazi kroz sve operacije,
		//vidi da li je neka spremna za izvrsavanje,
		//ubaci u vektor spremnih
		list<ArithmeticOperation*>::iterator currOperIterator = allOperations.begin();
		while (currOperIterator != allOperations.end())
		{
			if ((*currOperIterator)->hasBothOperands() && ((*currOperIterator)->getStartTime() != -1) && ((*currOperIterator)->getStartTime() <= currentNanoSec))
			{
				forExecution.push_back((*currOperIterator));
				allOperations.erase(currOperIterator++);
			}
			else
			{
				++currOperIterator;
			}
		}
		
		list<ArithmeticOperation*>::iterator executeOpIterator = forExecution.begin();
		while (executeOpIterator != forExecution.end())
		{
			if (((*executeOpIterator)->getStartTime() + (*executeOpIterator)->getT())  <= currentNanoSec)
			{
				(*executeOpIterator)->execute();
				cout << (*executeOpIterator)->outputForLog();
				forExecution.erase(executeOpIterator++);
			}
			else
			{
				++executeOpIterator;
			}
		}
		

		currentNanoSec++;
	}
	

}

ArithmeticOperation* Machine::makeAssignmentOp(string left, string right,int opNum) {
	Assignment* newOperation = new Assignment(opNum);
	newOperation->addOperand(new Expression(left, VARIABLE), LEFT);

	
	if (right.at(0) == '(') {
		ArithmeticOperation *opRes = nullptr;
		string num = right.substr(1, right.length() - 2);
		int id = stoi(num);
		for (ArithmeticOperation* op: allOperations) {
			if (op->getId() == id) {
				opRes = op;
				break;
			}
		}
		if (opRes != nullptr)
			opRes->addRightRes(newOperation);
		
	}
	else {

		if (isDigit(right))
		{
			newOperation->addOperand(new Expression(right, CONSTANT), RIGHT);
			newOperation->setStartTime(0); //SPREMNA ZA IZVRSAVANJE ODMAH PO STARTU PROGRAMA
		}
		else
			newOperation->addOperand(new Expression(right, VARIABLE), RIGHT);
		
	}
	assignments.push_back(newOperation);
	return newOperation;
}

ArithmeticOperation* Machine::makeOtherOp(string left, string right, int opNum, string op) {
	
	ArithmeticOperation* newOperation = nullptr;
	if (!op.compare("+"))
		newOperation = new Addition(opNum);
	else if (!op.compare("*"))
		newOperation = new Multiplication(opNum);
	else if (!op.compare("^"))
		newOperation = new Power(opNum);

	try {
		bool leftConst = false;
		bool rightConst = false;

		//left operand
		if (left.at(0) == '(') {
			ArithmeticOperation *opRes = nullptr;
			string num = left.substr(1, left.length() - 2);
			int id = stoi(num);
			for (ArithmeticOperation* op : allOperations) {
				if (op->getId() == id) {
					opRes = op;
					break;
				}
			}
			if (opRes != nullptr)
				opRes->addLeftRes(newOperation);
			else
				throw "makeOtherOp - left opRes not found";
		}
		else {
			if (isDigit(left))
			{
				newOperation->addOperand(new Expression(left, CONSTANT), LEFT);
				leftConst = true; //u slucaju da je i desni const, spreman za exec po startu programa
			}
			else
			{
				Assignment *opRes = nullptr;
				for (Assignment* op : assignments) {
					if (!op->getVarName().compare(left)) {
						opRes = op;
						break;
					}
				}
				if (opRes != nullptr)
					opRes->addLeftRes(newOperation);
				else
					throw "makeOtherOp - left opRes not found";
			}
				
		}

		//right operand
		if (right.at(0) == '(') {
			ArithmeticOperation *opRes = nullptr;
			string num = right.substr(1, right.length() - 2);
			int id = stoi(num);
			for (ArithmeticOperation* op : allOperations) {
				if (op->getId() == id) {
					opRes = op;
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
			{
				newOperation->addOperand(new Expression(right, CONSTANT), RIGHT);
				rightConst = true; //u slucaju da je i levi const, spreman za exec po startu programa
			}
			else
			{
				Assignment *opRes = nullptr;
				for (Assignment* op : assignments) {
					if (!op->getVarName().compare(right)) {
						opRes = op;
						break;
					}
				}
				if (opRes != nullptr)
					opRes->addRightRes(newOperation);
				else
					throw "makeOtherOp - right opRes not found";
			}
				
		}

		if (leftConst && rightConst)
			newOperation->setStartTime(0);

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
	for (ArithmeticOperation* op : allOperations) {
		op->printOp();
	}
}