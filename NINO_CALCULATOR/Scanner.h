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
		Token GetNextToken(std::stringstream &expression);								
		std::vector<Token> GetTokenList(std::stringstream &expression);		
		std::vector<Token> GetTokenList()
		{
			return std::vector<Token>();
		}

	public:
		Token HandleNumberState(std::stringstream &expression, char currectChar);
		Token HandleOperatorState(std::stringstream &expression, char currectChar);
		
	private:
		Dictionary dict_;					//语法字典
		State state_;						//当前状态，用于状态机
	};

}




