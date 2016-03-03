#include "stdafx.h"
#include "NLexicalAnalyzer.h"

using std::vector;
using std::string;
using std::regex_match;
using std::smatch;

vector<string> NLexicalAnalyzer(string line)
{

	vector<string> resultVector;
	string number;
	smatch token;

	for (auto each : line)
	{
		string temp;
		temp.push_back(each);

		//读入数字
		if(regex_match(temp, token, SINGLE_NUMBER_REGEX))
		{
			number.append(token.str());	//合并数字
		}
		//读入运算符->弹出数字
		else if(regex_match(temp, token, OPERATOR_REGEX))
		{
			resultVector.push_back(number);			//读入数字
			number = "";
			resultVector.push_back(token.str());	//读入运算符
		}
		else
		{
			;
		}
	}

	//读入末尾数字
	if (number != "")
	{
		resultVector.push_back(number);			//读入数字
	}

	return resultVector;
}
