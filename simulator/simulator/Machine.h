#pragma once
#include <iostream>
#include "ArithmeticOperation.h"
#include "Assignment.h"
#include <list>
using namespace std;

class Machine
{
private:
	static Machine * machine;
	Machine() {}
	list<ArithmeticOperation*> allOperations;
	list<ArithmeticOperation*> forExecution;
	list<Assignment*> assignments;

	ArithmeticOperation* makeAssignmentOp(string left, string right, int opNum);
	ArithmeticOperation* makeOtherOp(string left, string right, int opNum, string op);
	bool isDigit(string op);
public:
	~Machine();
	static Machine* getMachine() {
		if (machine == nullptr)
			machine = new Machine();
		return machine;
	}
	void exec(string file);
	void printAllOperations();
};

