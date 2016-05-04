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
		std::vector<Token> GetTokenList();

	public:
		char GetNextChar(std::stringstream &expression);	
		Token GetNextToken(std::stringstream &expression);								
		std::vector<Token> GetNextTokenList(std::stringstream &expression);		

	public:
		Token HandleNumberState(std::stringstream &expression, char currectChar);
		Token HandleOperatorState(std::stringstream &expression, char currectChar);
		
	private:
		std::stringstream stream_;
		Dictionary dict_;					//语法字典
		State state_;						//当前状态，用于状态机
	};

	inline std::vector<Token> Scanner::GetTokenList()
	{
		return GetNextTokenList(stream_);
	}

}




