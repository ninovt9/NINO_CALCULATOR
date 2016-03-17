#include "stdafx.h"
#include "NParser.h"

using std::vector;
using std::string;
using std::find;

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

