#include "Compiler.h"
#include "Expression.h"

Compiler* Compiler::compiler = 0;

// zasto nismo napravili split kao staticku f-ju?
vector<string> Compiler::split(const string &s, char delim) { // deli string(u ovom slucaju jednu liniju tekstualnog fajla
	//tj. programa) na vektor stringova, gde su elementi vektora stringovi odvojeni razmakom

	stringstream ss(s);
	string item;
	vector<string> elems;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;

}

bool Compiler::makeInf(string filename) {
	ifstream inputFile(filename);
	ofstream outputFile("outputs.txt");
	string str;
	int opNum = 1;//operation number, broj operacije koja se izvrsava

	while (getline(inputFile, str))
	{
		vector<string> ss = split(str, ' ');
		string variable = ss.at(0);

		if (ss.size() == 3) // ako vektor ima 3 elementa u sebi, znaci da je sa desne strane jednakosti konstanta
		{
			string constant = ss.at(2);
			outputFile << "(" << opNum++ << ") = ";
			outputFile << variable << " " << constant << "\n";
		}
		else
		{
			stack<Expression*> operandsStack;
			stack<Expression*> operatorsStack;
			string currentS;
			for (int i = 2; i < ss.size(); i++)
			{
				currentS = ss.at(i);
				if (i % 2 == 0)//konstante
				{
					Expression* e = new Expression(currentS, NULL, NULL, CONSTANT);
					operandsStack.push(e);
				}
				else//operatori
				{
					vector<Expression> operations;
					int opType;
					if (!currentS.compare("+"))
						opType = ADD;
					else if (!currentS.compare("*"))
						opType = MUL;
					else if (!currentS.compare("^"))
						opType = POW;
					Expression* e = new Expression(currentS, NULL, NULL, opType);
					if (operatorsStack.empty()) //mozda mogu da mrdzujem kad je prioritet i veci i ovaj if sa ||
					{
						operatorsStack.push(e);
					}
					else
					{
						while ((!operatorsStack.empty()) && (e->E_type() <= (operatorsStack.top())->E_type()))
						{
							Expression *merged = mergeOperandsWithOp(operandsStack, operatorsStack);
							merged->setOpNum(opNum++);
							outputFile << printComplexExpression(merged);
						}
						operatorsStack.push(e);
					}
				}
			}
			while (!operatorsStack.empty()) 
			{
				Expression *merged = mergeOperandsWithOp(operandsStack, operatorsStack);
				merged->setOpNum(opNum++);
				outputFile << printComplexExpression(merged);
			}
			outputFile << "(" << opNum << ") = ";
			outputFile << variable << " (" << opNum++ - 1 << ") \n";
		}
	}
	return true;
}

Expression* Compiler::mergeOperandsWithOp(stack<Expression*> &operandsStack, stack<Expression*> &operatorsStack) {
	Expression *right = operandsStack.top(); //treba napraviti novi izraz i stavti ga nazad
	operandsStack.pop(); // na stek kao i ubaciti u vektor izraza
	Expression *left = operandsStack.top();
	operandsStack.pop();
	Expression *merged = operatorsStack.top();
	operatorsStack.pop();
	merged->setLeft(left);
	merged->setRight(right);
	operandsStack.push(merged);
	return merged;
}

string Compiler::printComplexExpression(Expression *merged)
{
	string output;
	Expression* left = merged->getLeft();
	Expression* right = merged->getRight();
	output.append(printExpressionNum(merged));

	string oper;
	if (merged->E_type() == ADD)
		oper = "+";
	if (merged->E_type() == MUL)
		oper = "*";
	if (merged->E_type() == POW)
		oper = "^";
	output.append(oper + " ");

	if (left->getOpNum() == 0)
		output.append(left->getValue() + " ");
	else
		output.append(printExpressionNum(left));

	if (right->getOpNum() == 0)
		output.append(right->getValue() + " ");
	else
		output.append(printExpressionNum(right));

	output.append("\n");

	return output;
}

string Compiler::printExpressionNum(Expression * ex)
{
	string output;
	output.append("(");
	output.append(to_string(ex->getOpNum()));
	output.append(") ");
	return output;
}
