#include "stdafx.h"
#include "NExpression.h"

using std::string;


NExpression::NExpression()
{
}


NExpression::~NExpression()
{
}

float NExpression::Calculate(string expression)
{
	std::vector<std::string> tokenList = NGetTokenList(expression);
	return NEvaluateExpression(tokenList);
}
