#pragma once

#include "Token.h"
#include "Dictionary.h"

#include <sstream>
#include <string>
#include <vector>

namespace calculator
{

	enum class State
	{
		START,
		NUMBER,
		OPERATOR,
	};

	class Scanner
	{
	public:
		Scanner();
		Scanner(const std::string &expression);

	public:
		char GetNextChar(std::stringstream &expression);	
		Token GetNextToken();								
		std::vector<Token> GetTokenList();					

	public:
		Token HandleNumberState(std::stringstream &expression, char currectChar);
		Token HandleOperatorState(std::stringstream &expression, char currectChar);
		
	private:
		char currectChar_;					//当前字符
		Dictionary dict_;					//语法字典
		State state_;						//当前状态，用于状态机
		std::stringstream expression_;		//表达式(流）
		std::string buffer_;				//临时缓存(相当于tempStr)
		Token token_;						//临时token
	};

}




