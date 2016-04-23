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
		//Ê×¸ö×Ö·û
		buffer_.push_back(currectChar_);

		while (isdigit(GetNextChar()))
		{
			buffer_ += currectChar_;
		}

		//token of int
		token_ = Token(TokenType::INT);

		//ÖØÖÃ
		state_ = State::START;
		buffer_ = "";
	}

	void Scanner::HandleOperatorState()
	{
		buffer_.push_back(currectChar_);
		token_ = dict_.FindToken(buffer_);

		//ÖØÖÃ
		state_ = State::START;
		buffer_ = "";
		GetNextChar();
	}

	Token Scanner::GetNextToken()
	{
		//×´Ì¬ÅÐ¶Ï
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

			//stateÇ¨ÒÆ
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






