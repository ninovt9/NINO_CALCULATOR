#include "stdafx.h"
#include "Scanner.h"

using std::string;
using std::vector;
using std::stringstream;

namespace calculator
{
	Scanner::Scanner() : state_(State::START), buffer_("")
	{
		expression_ = std::stringstream("");
		dict_ = Dictionary();
	}

	Scanner::Scanner(const string &expression) :state_(State::START), buffer_("")
	{
		expression_ = std::stringstream(expression);
		//currectChar_ = GetNextChar(expression);
		dict_ = Dictionary();
	}

	char Scanner::GetNextChar(stringstream &expression)
	{
		return expression.get();
	}

	vector<Token> Scanner::GetTokenList()
	{
		vector<Token> result;
		while (!expression_.eof())
		{
			auto test = GetNextToken();
			result.push_back(test);
		}
		return result;

		//此处应有error
	}

	Token Scanner::GetNextToken()
	{
		////状态判断
		//while (!expression_.eof())
		//{
		//	switch (state_)
		//	{
		//	case State::START:
		//		break;

		//	case State::NUMBER:
		//		HandleNumberState();
		//		return token_;
		//		break;

		//	case State::OPERATOR:
		//		HandleOperatorState();
		//		return token_;
		//		break;

		//	default:
		//		break;
		//	}

		//	string currectStr;
		//	currectStr.push_back(currectChar_);

		//	//state迁移
		//	if (isdigit(currectChar_))
		//	{
		//		state_ = State::NUMBER;
		//	}
		//	else if (dict_.HasToken(currectStr))
		//	{
		//		state_ = State::OPERATOR;
		//	}
		//}
		return Token(TokenType::INVALID);
	}



	Token Scanner::HandleNumberState(stringstream &expression, char currectChar)
	{
		// first char
		string buffer;
		buffer.push_back(currectChar);

		// the rest of char
		currectChar = GetNextChar(expression);
		// 未达文件尾 and 元素为数字
		while (!expression.eof() && isdigit(currectChar))	
		{
			buffer += currectChar;
			currectChar = GetNextChar(expression);
		}

		// reset state
		state_ = State::START;

		// string to int
		int value;
		std::stringstream stream(buffer);
		stream >> value;

		return Token(TokenType::INT, value);
	}

	Token Scanner::HandleOperatorState(stringstream &expression, char currectChar)
	{
		// first char
		string buffer;
		buffer.push_back(currectChar);
		auto token = dict_.FindToken(buffer);

		//reset state
		state_ = State::START;
		GetNextChar(expression);

		return token;
	}


}






