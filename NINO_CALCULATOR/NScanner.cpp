#include "stdafx.h"
#include "NScanner.h"

using std::vector;
using std::string;
using std::regex_match;
using std::smatch;

//匹配函数
bool NIsTokenMatchRegex(string token)
{
	smatch result;
	if (regex_match(token, result, MULT_NUMBER_REGEX))			//数字
		return true;
	else if (regex_match(token, result, OPERATOR_REGEX))		//运算符
		return true;
	else if (regex_match(token, result, BRAKET_REGEX))			//括号
		return true;
	else
		return false;
}

//分解单词流
vector<string> NGetTokenList(string line)
{
	vector<string> tokenList;
	string token = "";

	for (auto iter = line.begin(); iter != line.end(); ++iter)
	{
		//排除空格
		if (*iter != ' ')
		{
			//匹配结束
			if (!NIsTokenMatchRegex(token + *iter))
			{
				tokenList.push_back(token);
				//重置
				token = *iter;

			}
			//继续匹配
			else
			{
				token.push_back(*iter);
			}
		}	
	}
	//清理余下单词
	if (token != "")
	{
		tokenList.push_back(token);
	}

	return tokenList;
}


//vector<string> NGetTokenList(string line)
//{
//
//	vector<string> resultVector;
//	string number;
//	smatch token;
//
//	for (auto each : line)
//	{
//		string temp;
//		temp.push_back(each);
//
//		//读入数字
//		if(regex_match(temp, token, SINGLE_NUMBER_REGEX))
//		{
//			number.append(token.str());	//合并数字
//		}
//		//读入运算符->弹出数字
//		else if(regex_match(temp, token, OPERATOR_REGEX))
//		{
//			resultVector.push_back(number);			//读入数字
//			number = "";
//			resultVector.push_back(token.str());	//读入运算符
//		}
//		else
//		{
//			;
//		}
//	}
//
//	//读入末尾数字
//	if (number != "")
//	{
//		resultVector.push_back(number);			//读入数字
//	}
//
//	return resultVector;
//}
