#pragma once

#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <sstream>


/*
语法分析
*/

//检测该范围是否在括号内（开闭括号完整匹配）
extern bool NIsInBracket(std::vector<std::string>::iterator begin,
						 std::vector<std::string>::iterator end);

//是否可以通过该符号分割
extern bool NIsSplitBySymbol(std::vector<std::string> &expression,
					         std::string n_operator,
					         std::vector<std::string>::iterator &iterSplit);

//计算表达式
extern float NEvaluateExpression(std::vector<std::string> expression);
//各个级别计算函数
extern float NEvaluateExpressionForE(std::vector<std::string> expression);	//E:加减法
extern float NEvaluateExpressionForF(std::vector<std::string> expression);	//T:乘除法
extern float NEvaluateExpressionForT(std::vector<std::string> expression);	//F:括号
extern float NEvaluateExpressionForId(std::string number);					//id:终结符