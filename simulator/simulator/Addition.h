#pragma once
#include "Operation.h"
class Addition :public Operation
{
public:
	Addition();
	~Addition();

	int execute();
	void setLeft(string left);
	void setRight(string right);
	void setLeft(double left);
	void setRight(double right);
};

