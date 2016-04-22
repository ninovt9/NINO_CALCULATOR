#include "stdafx.h"
#include "Scanner.h"

using std::string;

namespace calculator
{
	Scanner::Scanner(const string &expression):state_(State::START), buffer_("")
	{
		expression_ = std::stringstream(expression);
	}

	char Scanner::GetNextChar()
	{
		char ch;
		expression_ >> ch;
		return ch;
	}

	State Scanner::HandleStartState()
	{
		auto ch = GetNextChar();	//获取当前字符
		Dictionary dict = Dictionary();
		
		//整数:0-9					
		if (isdigit(ch))	
		{
			return State::NUMBER;
		}
		//字符
		//elif(dict.FindToken())
	}

	Token Scanner::GetNextToken()
	{
		//状态判断
		switch (state_)
		{
		case State::START:
			//首字母判断state
			break;
		case State::NUMBER:
			//数字处理
			break;
		case State::OPERATOR:
			//符号处理
			break;
		case State::END:
			//
			break;
		default:
			//
			break;
		}
	}
}




