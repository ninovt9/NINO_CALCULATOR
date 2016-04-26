#include "stdafx.h"
#include "Scanner.h"

using std::string;

namespace calculator
{
	Scanner::Scanner(const string &expression) :state_(State::START), buffer_("")
	{
		expression_ = std::stringstream(expression);
		currectChar_ = GetNextChar();
		dict_ = Dictionary();
	}

	char Scanner::GetNextChar()
	{
		char ch;
		expression_ >> ch;
		currectChar_ = ch;
		return ch;
	}

	void Scanner::HandleNumberState()
	{
		// ◊∏ˆ◊÷∑˚
		
		buffer_.push_back(currectChar_);

		while (isdigit(GetNextChar()))
		{
			buffer_ += currectChar_;
		}

		//token of int

		//token_ = Token(TokenType::INT);
		int value;
		std::stringstream stream(buffer_);
		stream >> value;

		token_ = Token(TokenType::INT, value);

		//÷ÿ÷√
		state_ = State::START;
		buffer_ = "";
	}

	void Scanner::HandleOperatorState()
	{
		buffer_.push_back(currectChar_);

		token_ = dict_.FindToken(buffer_);

		//÷ÿ÷√
		state_ = State::START;
		buffer_ = "";
		GetNextChar();
	}

	Token Scanner::GetNextToken()
	{
		//◊¥Ã¨≈–∂œ
		while (!expression_.eof())
		{
			switch (state_)
			{
			case State::START:
				break;

			case State::NUMBER:
				HandleNumberState();
				return token_;
				break;

			case State::OPERATOR:
				HandleOperatorState();
				return token_;
				break;

			default:
				break;
			}

			string currectStr;
			currectStr.push_back(currectChar_);

			//state«®“∆
			if (isdigit(currectChar_))
			{
				state_ = State::NUMBER;
			}
			else if (dict_.HasToken(currectStr))
			{
				state_ = State::OPERATOR;
			}
		}
		return Token(TokenType::INVALID);
	}
}






