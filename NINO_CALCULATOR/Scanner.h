#pragma once

#include "Token.h"
#include "Dictionary.h"

#include <sstream>
#include <string>

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
		Scanner() = default;
		Scanner(const std::string &expression);

	public:
		char GetNextChar();
		Token GetNextToken();	

	public:
		void HandleNumberState();
		void HandleOperatorState();
		
	private:
		char currectChar_;					//当前字符
		Dictionary dict_;					//语法字典
		State state_;						//当前状态，用于状态机
		std::stringstream expression_;		//表达式(流）

		std::string buffer_;				//临时缓存(相当于tempStr)

		Token token_;						//临时token
	};

}




