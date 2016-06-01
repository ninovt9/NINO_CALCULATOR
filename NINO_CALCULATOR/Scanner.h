#pragma once

#include "Token.h"
#include "Dictionary.h"
#include "Error.h"

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
		VARIABLE,
		ERROR
	};

	class Scanner
	{
	public:
		Scanner();
		Scanner(const std::string &expression);

	public:
		std::vector<Token>			GetTokenList();
		std::vector<std::string>	GetErrorReport();

	public:
		char						PeekChar(std::stringstream &expression);
		char						GetNextChar(std::stringstream &expression);	
		Token						GetNextToken(std::stringstream &expression);								
		std::vector<Token>			GetNextTokenList(std::stringstream &expression);		

	public:
		Token						HandleNumberState(std::stringstream &expression, char currectChar);
		Token						HandleOperatorState(std::stringstream &expression, char currectChar);
		Token						HandleVariableState(std::stringstream &expression, char currectChar);
		
	private:
		std::stringstream			stream_;
		Dictionary					dict_;								
		State						state_;									
		std::vector<std::string>	errorReport_;			
	};

	inline std::vector<Token> Scanner::GetTokenList()
	{
		return GetNextTokenList(stream_);
	}

	inline std::vector<std::string> Scanner::GetErrorReport()
	{
		return errorReport_;
	}

}




