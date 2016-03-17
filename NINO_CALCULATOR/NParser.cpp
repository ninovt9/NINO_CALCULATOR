#include "stdafx.h"
#include "NParser.h"

using std::vector;
using std::string;
using std::find;
using std::stringstream;

//检测该范围是否在括号内（开闭括号完整匹配）
bool NIsInBracket(vector<string>::iterator begin,
	vector<string>::iterator end)
{
	int count = 0;
	for (; begin != end; ++begin)
	{
		//计算左右括号数量差
		if (*begin == "(")
			count++;
		else if(*begin == ")")
			count--;
	}
	if (count <= 0)
		return false;
	else
		return true;
}

//表达式是否可以通过该运算符分割、并得出运算符迭代器（引用）
bool NIsSplitBySymbol(vector<string> expression,
	string n_operator,
	vector<string>::iterator &iterSplit)
{
	for (iterSplit = expression.begin(); iterSplit != expression.end(); ++iterSplit)
	{
		if (*iterSplit == n_operator &&
			!NIsInBracket(expression.begin(), iterSplit))
			return true;
	}
	return false;
}

//E:加减法
float NEvaluateExpressionForE(vector<string> expression)
{
	auto iterSplit = expression.begin();
	//T+E
	if (NIsSplitBySymbol(expression, "+", iterSplit))
	{
		return NEvaluateExpressionForT(expression) + NEvaluateExpressionForE(expression);
	}
	//T-E
	else if (NIsSplitBySymbol(expression, "-", iterSplit))
	{
		return NEvaluateExpressionForT(expression) - NEvaluateExpressionForE(expression);
	}
	//降级->T
	else
	{
		return NEvaluateExpressionForT(expression);
	}
}
//T:乘除法
float NEvaluateExpressionForT(vector<string> expression)
{
	auto iterSplit = expression.begin();
	//F*T
	if (NIsSplitBySymbol(expression, "*", iterSplit))
	{
		return NEvaluateExpressionForF(expression) + NEvaluateExpressionForT(expression);
	}
	//F/T
	else if (NIsSplitBySymbol(expression, "/", iterSplit))
	{
		return NEvaluateExpressionForF(expression) - NEvaluateExpressionForT(expression);
	}
	//降级->F
	else
	{
		return NEvaluateExpressionForF(expression);
	}
}

//F:括号
float NEvaluateExpressionForT(vector<string> expression)
{
	auto begin = expression.begin();
	auto end = expression.end() - 1;
	//括号
	if (*begin == "(" && *end == ")")
	{
		//提取括号中间部分
		return NEvaluateExpressionForE(vector<string>(begin + 1, end - 1));
	}
	else
	{
		//这里应该有错误机制
		return NEvaluateExpressionForId(expression[0]);
	}
}

//id:终结符
float NEvaluateExpressionForId(string number)
{
	float result;
	stringstream stream(number);
	stream >> result;
	return result;
}
