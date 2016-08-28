#pragma once
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <list>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <stack>
#include "Expression.h"

using namespace std;
class Compiler
{
	static Compiler* compiler;
	Compiler() {}
	string printComplexExpression(Expression *merged);
	string printExpressionNum(Expression *);
	Expression* mergeOperandsWithOp(stack<Expression*> &operandsStack, stack<Expression*> &operatorsStack);
public:
	
	static Compiler* getCompiler() {
		if (compiler == nullptr)
			compiler = new Compiler();
		return compiler;
	} 
	~Compiler(){}

	vector<string> split(const string &s, char delim);

	bool makeInf(string filename);
	void printfromfile(string filename);
};

