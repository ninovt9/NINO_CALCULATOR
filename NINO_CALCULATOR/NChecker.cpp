#include "stdafx.h"
#include "NChecker.h"

using std::smatch;
using std::regex;
using std::regex_search;
using std::string;
using std::vector;

void NCheckError(string expression)
{
	NCheckTokenError(expression);
	NCheckMatchError(expression);
	NCheckOperatorAdjacent(expression);
}

void NCheckTokenError(string expression)
{
	for (size_t i = 0; i != expression.size(); ++i)
	{
		string token;
		token.push_back(expression[i]);

		if (!NIsTokenMatchRegex(token))
		{
			throw std::invalid_argument("参数错误");
		}
	}
}

void NCheckMatchError(string expression)
{
	int count = 0;

	for (auto each : expression)
	{
		if (each == '(')
			count++;
		else if (each == ')' && count != 0)
			count--;
		else if(each == ')' && count == 0)
			throw std::invalid_argument("括号不匹配");
	}
	if (count != 0)
	{
		throw std::invalid_argument("括号不匹配");
	}
}

void NCheckOperatorAdjacent(string expression)
{
	const regex rule("[\\+\\-\\*\\/]{2}");
	smatch result;
	if (regex_search(expression, result, rule))
	{
		throw std::invalid_argument("运算符不能相邻");
	}
}
