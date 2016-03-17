#pragma once

//词法分析
//目的：将表达式分解为token

#include <string>
#include <vector>
#include <regex>

//主函数
extern std::vector<std::string> NGetTokenList(std::string line);

//正则表达式规则
const std::regex MULT_NUMBER_REGEX("[1-9][0-9]*|0|[0-9]+\\.[0-9]+"); //用于判断多位数字(整数、0、小数）
const std::regex SINGLE_NUMBER_REGEX("[0-9]|\\."); //用于判断单位数字(0-9、小数点）
//空格
const std::regex SPACE_REGEX("\\s+");
//四则运算
const std::regex OPERATOR_REGEX("\\+|\\-|\\*|\\/");	//加减乘除（暂定）
const std::regex ADD_REGEX("\\+");
const std::regex SUB_REGEX("\\-");
const std::regex MUL_REGEX("\\*");
const std::regex DIV_REGEX("\\/");