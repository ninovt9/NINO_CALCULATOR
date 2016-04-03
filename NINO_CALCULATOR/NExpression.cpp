#include "stdafx.h"
#include "NExpression.h"


using std::string;
using std::vector;


NExpression::NExpression()
{
}


NExpression::~NExpression()
{
}

float NExpression::Calculate(string expression)
{
	NCheckError(expression);	//´íÎó¼ì²é
	vector<string> tokenList = NGetTokenList(expression);
	return NEvaluateExpression(tokenList);
}
