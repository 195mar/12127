#pragma once
#include <iostream>
#include "ArithmeticOperation.h"
using namespace std;

class Machine
{
private:
	static Machine * machine;
	Machine() {}
	vector<ArithmeticOperation*> allOperations;

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

