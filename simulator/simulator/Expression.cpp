#include "Expression.h"


Expression::Expression(string value, Expression* left, Expression* right, int type)
{
	this->value = value;
	this->left = left;
	this->right = right;
	this->type = type;
}

Expression::Expression(string value, int type)
{
	this->value = value;
	this->type = type;
}


Expression::~Expression()
{
}
