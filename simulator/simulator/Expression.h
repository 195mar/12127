#pragma once
#include <string>
#include <stdio.h>
using namespace std;

#define ADD 0
#define MUL 1
#define POW 2

#define OPERAND 3
#define VARIABLE 4
class Expression
{
private:
	string value;
	Expression* left = NULL, *right=NULL;
	int type; //da li je slozeni izraz, konstanta izraz ili promenljiva 
	// treba napraviti nesto sto ce da odredjuje prioritet operacja
	int opNum=0;
public:
	
	Expression(string value, Expression* left, Expression* right, int type);
	//Expression(const Expression &e); //treba napraviti konstruktor kopije i premestajuci konstruktor
	~Expression();

	void setLeft(Expression* left) { this->left = left; }
	void setRight(Expression* right) { this->right = right; }
	Expression* getLeft() { return left; }
	Expression* getRight() { return right; }
	int E_type(){ return this->type; }
	void setOpNum(int x) { opNum = x; }
	int getOpNum(){ return opNum; }
	string getValue() { return value; }
};
