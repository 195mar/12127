#pragma once
#include <string>
#include <stdio.h>
#include <map>
using namespace std;
class Memory
{
private:
	static Memory * memory;
	Memory();
	map<string, double> memoryMap;
public:
	static Memory* getMemory(){
		if (memory == nullptr)
			memory = new Memory();
		return memory;
	}
	~Memory();

	double get(string varName);
	void set(string varName, double value);
};

