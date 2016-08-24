#pragma once
#include <string>
#include <stdio.h>
using namespace std;
class Memory
{
private:
	static Memory * memory;
	Memory();

public:
	static Memory* getMemory();
	~Memory();

	double get(string varName);
	void set(string varName, double value);
};

