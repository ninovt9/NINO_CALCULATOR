#include "stdafx.h"
#include "Scanner.h"

using std::string;
using std::vector;
using std::stringstream;

namespace calculator
{
	Scanner::Scanner(const string &expression) :state_(State::START), buffer_("")
	{
		expression_ = std::stringstream(expression);
		//currectChar_ = GetNextChar(expression);
		dict_ = Dictionary();
	}

	//char Scanner::GetNextChar()
	//{
	//	char ch;
	//	expression_ >> ch;
	//	currectChar_ = ch;
	//	return ch;
	//}

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



	void Scanner::HandleNumberState()
	{
		////首个字符
		//
		//buffer_.push_back(currectChar_);

		//GetNextChar();
		//while (!expression_.eof() && isdigit(currectChar_))
		//{
		//	buffer_ += currectChar_;
		//}

		////token of int

		////token_ = Token(TokenType::INT);
		//int value;
		//std::stringstream stream(buffer_);
		//stream >> value;

		//token_ = Token(TokenType::INT, value);

		////重置
		//state_ = State::START;
		//buffer_ = "";
	}

	void Scanner::HandleOperatorState()
	{
		//buffer_.push_back(currectChar_);

		//token_ = dict_.FindToken(buffer_);

		////重置
		//state_ = State::START;
		//buffer_ = "";
		//GetNextChar();
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
}






