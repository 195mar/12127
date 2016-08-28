#include "Compiler.h"
#include "Machine.h"

void main() {
	string s = "program.txt";

	Compiler* comp = Compiler::getCompiler();
	bool svekul = comp->makeInf(s);
	
	if (svekul) {
		Machine *machine = Machine::getMachine();
		machine->exec("outputs.txt"); //zadati kao arg promenljivu
		int a = 4;
	}
}
